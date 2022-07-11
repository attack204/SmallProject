//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lock_manager.cpp
//
// Identification: src/concurrency/lock_manager.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <utility>
#include <vector>

#include "concurrency/lock_manager.h"
#include "concurrency/transaction_manager.h"

namespace bustub {

bool LockManager::LockShared(Transaction *txn, const RID &rid) {
  if (CheckAbort(txn)) {
    return false;
  }

  if (txn->GetIsolationLevel() == IsolationLevel::READ_UNCOMMITTED) {
    // read uncommitted don't need LockShared.
    txn->SetState(TransactionState::ABORTED);
    return false;
  }

  if (txn->GetState() != TransactionState::GROWING) {
    txn->SetState(TransactionState::ABORTED);
    throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
  }

  if (txn->IsSharedLocked(rid)) {
    return true;
  }

  std::unique_lock<std::mutex> guard(latch_);
  LockRequestQueue *lock_queue = &lock_table_[rid];
  LockRequest lock_request = LockRequest(txn->GetTransactionId(), LockMode::SHARED);
  lock_queue->request_queue_.emplace_back(lock_request);
  txn->GetSharedLockSet()->emplace(rid);

  while (NeedWait(txn, lock_queue)) {
    lock_queue->cv_.wait(guard);
    LOG_DEBUG("%d: Awake and check itself.", txn->GetTransactionId());
    if (CheckAbort(txn)) {
      return false;
    }
  }

  for (auto &iter : lock_queue->request_queue_) {
    if (iter.txn_id_ == txn->GetTransactionId()) {
      iter.granted_ = true;
    }
  }
  txn->SetState(TransactionState::GROWING);
  return true;
}

bool LockManager::LockExclusive(Transaction *txn, const RID &rid) {
  if (CheckAbort(txn)) {
    return false;
  }

  if (txn->GetState() != TransactionState::GROWING) {
    txn->SetState(TransactionState::ABORTED);
    throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
  }

  if (txn->IsExclusiveLocked(rid)) {
    return true;
  }

  std::unique_lock<std::mutex> guard(latch_);
  LockRequestQueue *lock_queue = &lock_table_[rid];
  LockRequest lock_request = LockRequest(txn->GetTransactionId(), LockMode::EXCLUSIVE);
  lock_queue->request_queue_.emplace_back(lock_request);
  txn->GetExclusiveLockSet()->emplace(rid);

  while (NeedWait(txn, lock_queue)) {
    LOG_DEBUG("%d: Wait for exclusive lock", txn->GetTransactionId());
    lock_queue->cv_.wait(guard);
    LOG_DEBUG("%d: Awake and check itself.", txn->GetTransactionId());
    if (CheckAbort(txn)) {
      return false;
    }
  }

  LOG_DEBUG("%d: Get exclusive lock", txn->GetTransactionId());
  for (auto &iter : lock_queue->request_queue_) {
    if (iter.txn_id_ == txn->GetTransactionId()) {
      iter.granted_ = true;
    }
  }
  txn->SetState(TransactionState::GROWING);
  return true;
}

bool LockManager::LockUpgrade(Transaction *txn, const RID &rid) {
  if (CheckAbort(txn)) {
    return false;
  }

  if (txn->GetState() != TransactionState::GROWING) {
    txn->SetState(TransactionState::ABORTED);
    throw TransactionAbortException(txn->GetTransactionId(), AbortReason::UPGRADE_CONFLICT);
  }

  if (txn->IsExclusiveLocked(rid)) {
    return true;
  }

  std::unique_lock<std::mutex> guard(latch_);

  LockRequestQueue *lock_queue = &lock_table_[rid];

  while (NeedWaitUpdate(txn, lock_queue)) {
    lock_queue->cv_.wait(guard);
    if (CheckAbort(txn)) {
      return false;
    }
  }

  for (auto iter : lock_queue->request_queue_) {
    if (iter.txn_id_ == txn->GetTransactionId()) {
      iter.granted_ = true;
      iter.lock_mode_ = LockMode::EXCLUSIVE;
      txn->SetState(TransactionState::GROWING);
      txn->GetSharedLockSet()->erase(rid);
      txn->GetExclusiveLockSet()->emplace(rid);
      break;
    }
  }
  return true;
}

bool LockManager::Unlock(Transaction *txn, const RID &rid) {
  LOG_DEBUG("%d: Unlock", txn->GetTransactionId());
  if (!txn->IsSharedLocked(rid) && !txn->IsExclusiveLocked(rid)) {
    return false;
  }

  std::unique_lock<std::mutex> guard(latch_);
  LockRequestQueue &lock_queue = lock_table_[rid];
  if (lock_queue.upgrading_ == txn->GetTransactionId()) {
    lock_queue.upgrading_ = INVALID_TXN_ID;
  }
  bool found = false;
  for (auto iter = lock_queue.request_queue_.begin(); iter != lock_queue.request_queue_.end(); iter++) {
    if (iter->txn_id_ == txn->GetTransactionId()) {
      found = true;
      lock_queue.request_queue_.erase(iter);

      lock_queue.cv_.notify_all();
      break;
    }
  }

  if (!found) {
    return false;
  }

  if (txn->GetState() == TransactionState::GROWING && txn->GetIsolationLevel() == IsolationLevel::REPEATABLE_READ) {
    txn->SetState(TransactionState::SHRINKING);
  }
  txn->GetSharedLockSet()->erase(rid);
  txn->GetExclusiveLockSet()->erase(rid);
  return true;
}

bool LockManager::NeedWait(Transaction *txn, LockRequestQueue *lock_queue) {
  auto self = lock_queue->request_queue_.back();

  auto first_iter = lock_queue->request_queue_.begin();
  if (self.lock_mode_ == LockMode::SHARED) {
    if (first_iter->txn_id_ == txn->GetTransactionId() || first_iter->lock_mode_ == LockMode::SHARED) {
      return false;
    }
  } else {
    if (first_iter->txn_id_ == txn->GetTransactionId()) {
      return false;
    }
  }

  // need wait, try to prevent it.
  bool need_wait = false;
  bool has_aborted = false;

  for (auto iter = first_iter; iter->txn_id_ != txn->GetTransactionId(); iter++) {
    if (iter->txn_id_ > txn->GetTransactionId()) {
      bool situation1 = self.lock_mode_ == LockMode::SHARED && iter->lock_mode_ == LockMode::EXCLUSIVE;
      bool situation2 = self.lock_mode_ == LockMode::EXCLUSIVE;
      if (situation1 || situation2) {
        // abort younger
        Transaction *younger_txn = TransactionManager::GetTransaction(iter->txn_id_);
        if (younger_txn->GetState() != TransactionState::ABORTED) {
          LOG_DEBUG("%d: Abort %d", txn->GetTransactionId(), iter->txn_id_);
          younger_txn->SetState(TransactionState::ABORTED);
          has_aborted = true;
        }
      }
      continue;
    }

    if (self.lock_mode_ == LockMode::EXCLUSIVE) {
      need_wait = true;
    }

    if (iter->lock_mode_ == LockMode::EXCLUSIVE) {
      need_wait = true;
    }
  }

  if (has_aborted) {
    lock_queue->cv_.notify_all();
  }

  return need_wait;
}

bool LockManager::NeedWaitUpdate(Transaction *txn, LockRequestQueue *lock_queue) {
  bool need_wait = false;
  bool has_aborted = false;

  for (auto iter = lock_queue->request_queue_.begin(); iter->txn_id_ != txn->GetTransactionId(); iter++) {
    if (iter->txn_id_ > txn->GetTransactionId()) {
      LOG_DEBUG("%d: Abort %d", txn->GetTransactionId(), iter->txn_id_);
      Transaction *younger_txn = TransactionManager::GetTransaction(iter->txn_id_);
      if (younger_txn->GetState() != TransactionState::ABORTED) {
        younger_txn->SetState(TransactionState::ABORTED);
        has_aborted = true;
      }
      continue;
    }

    need_wait = true;
  }

  if (has_aborted) {
    lock_queue->cv_.notify_all();
  }

  return need_wait;
}

bool LockManager::CheckAbort(Transaction *txn) { return txn->GetState() == TransactionState::ABORTED; }

}  // namespace bustub
