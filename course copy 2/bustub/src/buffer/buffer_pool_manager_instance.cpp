//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// buffer_pool_manager_instance.cpp
//
// Identification: src/buffer/buffer_pool_manager.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/buffer_pool_manager_instance.h"

#include "common/logger.h"
#include "common/macros.h"
namespace bustub {

BufferPoolManagerInstance::BufferPoolManagerInstance(size_t pool_size, DiskManager *disk_manager,
                                                     LogManager *log_manager)
    : BufferPoolManagerInstance(pool_size, 1, 0, disk_manager, log_manager) {}

BufferPoolManagerInstance::BufferPoolManagerInstance(size_t pool_size, uint32_t num_instances, uint32_t instance_index,
                                                     DiskManager *disk_manager, LogManager *log_manager)
    : pool_size_(pool_size),
      num_instances_(num_instances),
      instance_index_(instance_index),
      next_page_id_(instance_index),
      disk_manager_(disk_manager),
      log_manager_(log_manager) {
  BUSTUB_ASSERT(num_instances > 0, "If BPI is not part of a pool, then the pool size should just be 1");
  BUSTUB_ASSERT(
      instance_index < num_instances,
      "BPI index cannot be greater than the number of BPIs in the pool. In non-parallel case, index should just be 1.");
  // We allocate a consecutive memory space for the buffer pool.
  pages_ = new Page[pool_size_];
  replacer_ = new LRUReplacer(pool_size);

  // Initially, every page is in the free list.
  for (size_t i = 0; i < pool_size_; ++i) {
    free_list_.emplace_back(static_cast<int>(i));
  }
}

BufferPoolManagerInstance::~BufferPoolManagerInstance() {
  delete[] pages_;
  delete replacer_;
}

bool BufferPoolManagerInstance::FlushPgImp(page_id_t page_id) {
  // Make sure you call DiskManager::WritePage!
  std::lock_guard<std::mutex> lock{latch_};
  if (page_table_.find(page_id) == page_table_.end()) {
    return false;
  }
  auto tmp_frame_id = page_table_[page_id];
  disk_manager_->WritePage(page_id, pages_[tmp_frame_id].GetData());
  pages_[tmp_frame_id].is_dirty_ = false;
  // page_table_.erase(page_id); //注意：写到磁盘后要从内存中删掉
  return true;
}

void BufferPoolManagerInstance::FlushAllPgsImp() {
  std::lock_guard<std::mutex> lock{latch_};
  for (auto &x : page_table_) {
    disk_manager_->WritePage(x.first, pages_[x.second].GetData());
    pages_[x.second].is_dirty_ = false;
    // page_table_.erase(pages_[i].GetPageId());
  }
}

Page *BufferPoolManagerInstance::NewPgImp(page_id_t *page_id) {
  // 0.   Make sure you call AllocatePage!
  // 1.   If all the pages in the buffer pool are pinned, return nullptr.
  // 2.   Pick a victim page P from either the free list or the replacer. Always pick from the free list first.
  // 3.   Update P's metadata, zero out memory and add P to the page table.
  // 4.   Set the page ID output parameter. Return a pointer to P.
  std::lock_guard<std::mutex> lock{latch_};
  int tmpFrameId = -1;
  if (free_list_.size() != 0) {
    tmpFrameId = free_list_.front();
    free_list_.pop_front();
  } else {  // free_list is empty
    int value;
    if (replacer_->Victim(&value)) {
      tmpFrameId = value;
      if (pages_[value].IsDirty()) {
        disk_manager_->WritePage(pages_[value].GetPageId(), pages_[value].GetData());
      }
      // LOG_DEBUG("now page id %d %d", *page_id, pages_[value].GetPageId());
      page_table_.erase(pages_[value].GetPageId());
    }
  }
  if (tmpFrameId == -1) return nullptr;
  page_id_t newPageId = AllocatePage();
  // LOG_DEBUG("now page id %d %s", newPageId, pages_[page_table_[0]].GetData());
  *page_id = newPageId;
  page_table_[newPageId] = tmpFrameId;
  pages_[tmpFrameId].ResetMemory();
  pages_[tmpFrameId].pin_count_ = 1;
  pages_[tmpFrameId].is_dirty_ = false;
  pages_[tmpFrameId].page_id_ = newPageId;
  replacer_->Pin(tmpFrameId);
  return &pages_[tmpFrameId];
}

Page *BufferPoolManagerInstance::FetchPgImp(page_id_t page_id) {
  // 1.     Search the page table for the requested page (P).
  // 1.1    If P exists, pin it and return it immediately.
  // 1.2    If P does not exist, find a replacement page (R) from either the free list or the replacer.
  //        Note that pages are always found from the free list first.
  // 2.     If R is dirty, write it back to the disk.
  // 3.     Delete R from the page table and insert P.
  // 4.     Update P's metadata, read in the page content from disk, and then return a pointer to P.
  std::lock_guard<std::mutex> lock{latch_};
  // LOG_DEBUG("FetchPgImp %d", page_id);
  if (page_table_.find(page_id) != page_table_.end()) {
    Page *tmpPage = &pages_[page_table_[page_id]];
    replacer_->Pin(page_table_[page_id]);
    tmpPage->pin_count_++;
    return tmpPage;
  }
  frame_id_t tmp_frame_id = -1;
  if (free_list_.size() != 0) {
    tmp_frame_id = free_list_.front();
    free_list_.pop_front();
  } else {
    int value;
    if (replacer_->Victim(&value) == true) {
      tmp_frame_id = value;
      if (pages_[value].IsDirty()) {
        disk_manager_->WritePage(pages_[value].GetPageId(), pages_[value].GetData());
      }
      page_table_.erase(pages_[value].GetPageId());
    }
  }
  if (tmp_frame_id == -1) return nullptr;
  Page *tmp_page = &pages_[tmp_frame_id];
  tmp_page->page_id_ = page_id;
  tmp_page->is_dirty_ = false;
  tmp_page->pin_count_ = 1;
  disk_manager_->ReadPage(tmp_page->GetPageId(), tmp_page->data_);
  replacer_->Pin(tmp_frame_id);
  page_table_[page_id] = tmp_frame_id;
  return tmp_page;
}

bool BufferPoolManagerInstance::DeletePgImp(page_id_t page_id) {
  // 0.   Make sure you call DeallocatePage!
  // 1.   Search the page table for the requested page (P).
  // 1.   If P does not exist, return true.
  // 2.   If P exists, but has a non-zero pin-count, return false. Someone is using the page.
  // 3.   Otherwise, P can be deleted. Remove P from the page table, reset its metadata and return it to the free list.
  std::lock_guard<std::mutex> lock{latch_};
  DeallocatePage(page_id);
  if (page_table_.find(page_id) == page_table_.end()) {
    return true;
  }
  if (pages_[page_id].GetPinCount() > 0) {
    return false;
  }
  Page *tmp_page = &pages_[page_id];
  // 1. 写磁盘
  if (tmp_page->IsDirty()) {
    disk_manager_->WritePage(tmp_page->GetPageId(), tmp_page->GetData());
  }
  // 2. 更新page信息
  tmp_page->ResetMemory();
  tmp_page->pin_count_ = 0;
  tmp_page->is_dirty_ = false;
  tmp_page->page_id_ = INVALID_PAGE_ID;

  // 3. 更新LRU和Free List的信息
  free_list_.emplace_back(page_table_[page_id]);
  replacer_->Pin(page_table_[page_id]);

  // 4. 更新page table信息
  page_table_.erase(page_id);

  return true;
}

bool BufferPoolManagerInstance::UnpinPgImp(page_id_t page_id, bool is_dirty) {
  std::lock_guard<std::mutex> lock{latch_};
  if (page_table_.find(page_id) == page_table_.end()) {
    return false;
  }
  Page *tmp_page = &pages_[page_table_[page_id]];
  // if (tmp_page->GetPinCount() != 0) return false;

  // if (is_dirty) FlushPage(page_id);
  if (tmp_page->pin_count_ <= 0) {
    return false;
  }
  tmp_page->pin_count_--;
  if (tmp_page->pin_count_ <= 0) {
    replacer_->Unpin(page_table_[page_id]);
  }
  if (is_dirty) {
    tmp_page->is_dirty_ = true;
  }
  return true;
}

page_id_t BufferPoolManagerInstance::AllocatePage() {
  const page_id_t next_page_id = next_page_id_;
  next_page_id_ += num_instances_;
  ValidatePageId(next_page_id);
  return next_page_id;
}

void BufferPoolManagerInstance::ValidatePageId(const page_id_t page_id) const {
  assert(page_id % num_instances_ == instance_index_);  // allocated pages mod back to this BPI
}

}  // namespace bustub
