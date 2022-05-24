//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"
#include <iostream>

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {}

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(frame_id_t *frame_id) {
  std::lock_guard<std::mutex> guard(lru_latch_);
  if (lru_list_.empty()) {
    return false;
  }
  *frame_id = lru_list_.front();
  lru_map_.erase(*frame_id);
  lru_list_.pop_front();
  return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
  std::lock_guard<std::mutex> guard(lru_latch_);
  auto iter = lru_map_.find(frame_id);
  if (iter == lru_map_.end()) {
    return;
  }

  lru_list_.erase(iter->second);
  lru_map_.erase(iter);
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
  std::lock_guard<std::mutex> guard(lru_latch_);
  if (lru_map_.find(frame_id) != lru_map_.end()) {
    return;
  }
  lru_list_.push_back(frame_id);
  auto p = lru_list_.end();
  lru_map_[frame_id] = --p;
}

size_t LRUReplacer::Size() {
  std::lock_guard<std::mutex> guard(lru_latch_);
  return lru_list_.size();
}

}  // namespace bustub
