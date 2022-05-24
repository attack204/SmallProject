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
#include "common/logger.h"
namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {
  num_page = num_pages;
  head = new Node(-1, nullptr, nullptr);
  tail = new Node(-1, nullptr, nullptr);
  head->nxt = tail;
  tail->pre = head;
}

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(frame_id_t *frame_id) {
  std::lock_guard<std::mutex> lock{mut};
  if (tail->pre == head) {  // LRU is empty
    *frame_id = 0;
    return false;
  }
  *frame_id = tail->pre->id;
  removeTail();
  return true;
}

// remove frame_id
void LRUReplacer::Pin(frame_id_t frame_id) {
  std::lock_guard<std::mutex> lock{mut};
  if (umap.find(frame_id) == umap.end()) {
    return;
  }
  Node *tmp = umap[frame_id];
  tmp->pre->nxt = tmp->nxt;
  tmp->nxt->pre = tmp->pre;
  umap.erase(frame_id);
}

// add frame_id
void LRUReplacer::Unpin(frame_id_t frame_id) {
  std::lock_guard<std::mutex> lock{mut};

  if (umap.size() > num_page) return;

  if (umap.find(frame_id) != umap.end()) return;

  //  LOG_DEBUG("Begin %d", frame_id);

  Node *nw = new Node(frame_id, head, head->nxt);
  head->nxt->pre = nw;
  head->nxt = nw;
  umap[frame_id] = nw;

  // LOG_DEBUG("End %d", frame_id);
}

size_t LRUReplacer::Size() { return umap.size(); }

void LRUReplacer::removeTail() {
  // std::lock_guard<std::mutex> lock{mut};
  Node *pos = tail->pre;
  pos->pre->nxt = tail;
  tail->pre = pos->pre;
  umap.erase(pos->id);
}

}  // namespace bustub
