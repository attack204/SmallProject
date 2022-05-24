//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.h
//
// Identification: src/include/buffer/lru_replacer.h
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <list>
#include <mutex>  // NOLINT
#include <unordered_map>
#include <vector>

#include "buffer/replacer.h"
#include "common/config.h"

namespace bustub {

/**
 * LRUReplacer implements the Least Recently Used replacement policy.
 */
class LRUReplacer : public Replacer {
 public:
  /**
   * Create a new LRUReplacer.
   * @param num_pages the maximum number of pages the LRUReplacer will be required to store
   */
  explicit LRUReplacer(size_t num_pages);

  /**
   * Destroys the LRUReplacer.
   */
  ~LRUReplacer() override;

  bool Victim(frame_id_t *frame_id) override;

  void Pin(frame_id_t frame_id) override;

  void Unpin(frame_id_t frame_id) override;

  void removeTail();

  size_t Size() override;

 private:
  std::mutex mut;
  size_t num_page;
  // TODO(student): implement me!
  struct Node {
    frame_id_t id;
    struct Node *pre;
    struct Node *nxt;
    Node(frame_id_t id_, Node *pre_, Node *nxt_) {
      id = id_;
      pre = pre_;
      nxt = nxt_;
    }
  };
  Node *head, *tail;
  std::unordered_map<frame_id_t, Node *> umap;
};

}  // namespace bustub
