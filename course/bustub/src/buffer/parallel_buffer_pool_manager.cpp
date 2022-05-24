//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// parallel_buffer_pool_manager.cpp
//
// Identification: src/buffer/buffer_pool_manager.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/parallel_buffer_pool_manager.h"
#include "common/logger.h"
namespace bustub {

ParallelBufferPoolManager::ParallelBufferPoolManager(size_t num_instances, size_t pool_size, DiskManager *disk_manager,
                                                     LogManager *log_manager) {
  // Allocate and create individual BufferPoolManagerInstances
  buffers = new BufferPoolManagerInstance *[num_instances];
  for (size_t i = 0; i < num_instances; i++) {
    BufferPoolManagerInstance *tmp_manager =
        new BufferPoolManagerInstance(pool_size, num_instances, i, disk_manager, log_manager);
    buffers[i] = tmp_manager;
  }
  num_instances_ = num_instances;
  pool_size_ = pool_size;
  new_index = 0;
}

// Update constructor to destruct all BufferPoolManagerInstances and deallocate any associated memory
ParallelBufferPoolManager::~ParallelBufferPoolManager() { delete[] buffers; }

size_t ParallelBufferPoolManager::GetPoolSize() {
  // Get size of all BufferPoolManagerInstances
  return num_instances_ * pool_size_;
}

BufferPoolManager *ParallelBufferPoolManager::GetBufferPoolManager(page_id_t page_id) {
  // Get BufferPoolManager responsible for handling given page id. You can use this method in your other methods.
  size_t index = page_id % num_instances_;
  return buffers[index];
}

Page *ParallelBufferPoolManager::FetchPgImp(page_id_t page_id) {
  // Fetch page for page_id from responsible BufferPoolManagerInstance
  size_t index = page_id % num_instances_;
  return buffers[index]->FetchPage(page_id);
}

bool ParallelBufferPoolManager::UnpinPgImp(page_id_t page_id, bool is_dirty) {
  // Unpin page_id from responsible BufferPoolManagerInstance
  size_t index = page_id % num_instances_;
  return buffers[index]->UnpinPage(page_id, is_dirty);
}

bool ParallelBufferPoolManager::FlushPgImp(page_id_t page_id) {
  // Flush page_id from responsible BufferPoolManagerInstance
  size_t index = page_id % num_instances_;
  return buffers[index]->FlushPage(page_id);
}

Page *ParallelBufferPoolManager::NewPgImp(page_id_t *page_id) {
  // create new page. We will request page allocation in a round robin manner from the underlying
  // BufferPoolManagerInstances
  // 1.   From a starting index of the BPMIs, call NewPageImpl until either 1) success and return 2) looped around to
  // starting index and return nullptr
  // 2.   Bump the starting index (mod number of instances) to start search at a different BPMI each time this function
  // is called

  std::scoped_lock lock(latch_);
  Page *tmpPage = new Page();
  for (size_t bg = new_index;;) {
    //    LOG_DEBUG("tmpPage %d\n", tmpPage->GetPageId());
    if ((tmpPage = buffers[new_index]->NewPage(page_id)) != nullptr) {
      return tmpPage;
    }
    new_index = (new_index + 1) % num_instances_;
    if (new_index == bg) break;
  }
  return nullptr;
}

bool ParallelBufferPoolManager::DeletePgImp(page_id_t page_id) {
  // Delete page_id from responsible BufferPoolManagerInstance
  size_t index = page_id % num_instances_;
  return buffers[index]->DeletePage(page_id);
}

void ParallelBufferPoolManager::FlushAllPgsImp() {
  // flush all pages from all BufferPoolManagerInstances
  for (size_t i = 0; i < num_instances_; i++) {
    buffers[i]->FlushAllPages();
  }
}

}  // namespace bustub
