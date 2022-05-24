//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/index/b_plus_tree.cpp
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <string>

#include "common/exception.h"
#include "common/rid.h"
#include "storage/index/b_plus_tree.h"
#include "storage/page/header_page.h"

namespace bustub {
INDEX_TEMPLATE_ARGUMENTS
BPLUSTREE_TYPE::BPlusTree(std::string name, BufferPoolManager *buffer_pool_manager, const KeyComparator &comparator,
                          int leaf_max_size, int internal_max_size)
    : index_name_(std::move(name)),
      root_page_id_(INVALID_PAGE_ID),
      buffer_pool_manager_(buffer_pool_manager),
      comparator_(comparator),
      leaf_max_size_(leaf_max_size),
      internal_max_size_(internal_max_size) {}

/*
 * Helper function to decide whether current b+tree is empty
 */
INDEX_TEMPLATE_ARGUMENTS
template<typename N>
bool BPLUSTREE_TYPE::IsSafe(N *node, Operation operation) {
  if(node->IsRootPage()) {
    return (operation == Operation::INSERT && node->GetSize() + 1 < node->GetMaxSize()) ||
           (operation == Operation::DELETE && node->GetSize() > 2);
  }
  if(operation == Operation::INSERT) return node->GetSize() + 1 < node->GetMaxSize();
  if(operation == Operation::DELETE) return node->GetSize() > node->GetMinSize();
  return true;
}
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::IsEmpty() const {
  return root_page_id_ == INVALID_PAGE_ID;
}
/*****************************************************************************
 * SEARCH
 *****************************************************************************/
/*
 * Return the only value that associated with input key
 * This method is used for point query
 * @return : true means key exists
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::GetValue(const KeyType &key, std::vector<ValueType> *result, Transaction *transaction) {
  Page* tmp_page = FindLeafPageByOperation(key, Operation::FIND, transaction).first;
  LeafPage *leaf_page = reinterpret_cast<LeafPage *> (tmp_page->GetData());

  ValueType value{};
  bool is_find = leaf_page->Lookup(key, &value, comparator_);
  //注意在FindLeafPageByOperation之后leaf_page是lock的因此要解锁
  tmp_page->RUnlatch();
  buffer_pool_manager_->UnpinPage(tmp_page->GetPageId(), false);

  if(!is_find) {
    return false;
  }
  //因为key一定是unique的，所以这里最多只会有一个result
  result->push_back(value);
  return true;
}

/*****************************************************************************
 * INSERTION
 *****************************************************************************/
/*
 * Insert constant key & value pair into b+ tree
 * if current tree is empty, start new tree, update root page id and insert
 * entry, otherwise insert into leaf page.
 * @return: since we only support unique key, if user try to insert duplicate
 * keys return false, otherwise return true.
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::Insert(const KeyType &key, const ValueType &value, Transaction *transaction) {
  {
    const std::lock_guard<std::mutex> guard(root_latch_);
    if(IsEmpty()) {
      StartNewTree(key, value);
      return true;
    }
  }
  return InsertIntoLeaf(key, value, transaction);
}
/*
 * Insert constant key & value pair into an empty tree
 * User needs to first ask for new page from buffer pool manager(NOTICE: throw
 * an "out of memory" exception if returned value is nullptr), then update b+
 * tree's root page id and insert entry directly into leaf page.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::StartNewTree(const KeyType &key, const ValueType &value) {
  //创建新的节点
  page_id_t new_page_id = INVALID_PAGE_ID;
  Page *tmp_root_page = buffer_pool_manager_->NewPage(&new_page_id);
  if(tmp_root_page == nullptr) {
    throw std::runtime_error("out of memory");
  }
  
  //创建并更新B树根节点信息
  root_page_id_ = new_page_id;
  UpdateRootPageId(1);

  //初始化并更新root_page数据
  LeafPage *root_page = reinterpret_cast<LeafPage *> (tmp_root_page->GetData());
  root_page->Init(tmp_root_page->GetPageId(), INVALID_PAGE_ID, leaf_max_size_);
  root_page->Insert(key, value, comparator_);
  buffer_pool_manager_->UnpinPage(new_page_id, true);
}

/*
 * Insert constant key & value pair into leaf page
 * User needs to first find the right leaf page as insertion target, then look
 * through leaf page to see whether insert key exist or not. If exist, return
 * immdiately, otherwise insert entry. Remember to deal with split if necessary.
 * @return: since we only support unique key, if user try to insert duplicate
 * keys return false, otherwise return true.
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::InsertIntoLeaf(const KeyType &key, const ValueType &value, Transaction *transaction) {
  auto [tmp_page, is_root_latched] = FindLeafPageByOperation(key, Operation::INSERT, transaction);
  LeafPage *leaf_page = reinterpret_cast<LeafPage*> (tmp_page->GetData());
  int size = leaf_page->GetSize();
  int new_size = leaf_page->Insert(key, value, comparator_);
  if(size == new_size) {//插入失败，有重复key
    if(is_root_latched) {
      root_latch_.unlock();
    }
    UnLockUnpinPages(transaction);
    tmp_page->WUnlatch();
    buffer_pool_manager_->UnpinPage(tmp_page->GetPageId(), false);
    return false;
  }
  if(new_size < leaf_page->GetMaxSize()) {
    if(is_root_latched) {
      root_latch_.unlock();
    }
    //UnlockUnpinPages(transaction); TODOA: 为什么这里不用释放祖先？
    tmp_page->WUnlatch();
    buffer_pool_manager_->UnpinPage(tmp_page->GetPageId(), false);
    return true;
  }
  LeafPage *new_page = Split(&leaf_page);
  bool point_is_root_latched = new bool (is_root_latched);
  InsertIntoParent(leaf_page, new_page->KeyAt(0), new_page, transaction, point_is_root_latched);
  assert((*point_is_root_latched) == false);
  delete point_is_root_latched;
  tmp_page->WUnlatch();
  buffer_pool_manager_->UnpinPage(leaf_page->GetPageId(), true);
  buffer_pool_manager_->UnpinPage(new_page->GetPageId(), true);
  return true;
}

/*
 * Split input page and return newly created page.
 * Using template N to represent either internal page or leaf page.
 * User needs to first ask for new page from buffer pool manager(NOTICE: throw
 * an "out of memory" exception if returned value is nullptr), then move half
 * of key & value pairs from input page to newly created page
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
N *BPLUSTREE_TYPE::Split(N *node) {
  //1. 申请page_id并申请内存
  //2. 分情况讨论split的是什么节点，leaf节点还是internal节点
  //  2.1 如果是Page节点：把node的后半部分copy过去，设置next_page信息
  //  2.2 如果是Intern节点， 把node的后半部分copy过去
  page_id_t page_id = INVALID_PAGE_ID;
  Page *tmp_page = buffer_pool_manager_->NewPage(*page_id);
  if(tmp_page == nullptr) {
    throw std::runtime_error("out of memory");
  }
  N *new_node = reinterpret_cast<N* >(tmp_page->GetData());
  new_node->SetPageType(node->GetPageType());
  if(node->IsLeafPage()) {
    LeafPage * old_leaf_node = reinterpret_cast<LeafPage *> (node); 
    LeafPage * new_leaf_node = reinterpret_cast<LeafPage *> (new_node);
    new_leaf_node->Init(page_id, node->GetParentPageId(), leaf_max_size_);
    old_leaf_node->MoveHalfTo(new_leaf_node);
    new_leaf_node->SetNextPageId(old_leaf_node->GetNextPageId());
    old_leaf_node->SetNextPageId(new_leaf_node->GetPageId());
    new_node = reinterpret_cast<N*>(new_leaf_node);
  } else {
    InternalPage *old_internal_page = reinterpret_cast<InternalPage *> (node);
    InternalPage *new_internal_page = reinterpret_cast<InternalPage *> (new_node);
    new_internal_page->Init(page_id, node->GetParentPageId(), internal_max_size_);
    old_internal_page->MoveHalfTo(new_internal_page);
    new_node = reinterpret_cast<N*>(new_internal_page);
  }
  return new_node;
}

/*
 * Insert key & value pair into internal page after split
 * @param   old_node      input page from split() method
 * @param   key
 * @param   new_node      returned page from split() method
 * User needs to first find the parent page of old_node, parent node must be
 * adjusted to take info of new_node into account. Remember to deal with split
 * recursively if necessary.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::InsertIntoParent(BPlusTreePage *old_node, const KeyType &key, BPlusTreePage *new_node,
                                      Transaction *transaction, bool *is_root_latched) {

//1. 判断old_node是否是根节点，如果是根节点就需要让树加一层�
  if(old_node->IsRootPage()) {
    page_id_t new_page_id = INVALID_PAGE_ID;
  }                                  
}
/*****************************************************************************
 * REMOVE
 *****************************************************************************/
/*
 * Delete key & value pair associated with input key
 * If current tree is empty, return immdiately.
 * If not, User needs to first find the right leaf page as deletion target, then
 * delete entry from leaf page. Remember to deal with redistribute or merge if
 * necessary.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::Remove(const KeyType &key, Transaction *transaction) {}

/*
 * User needs to first find the sibling of input page. If sibling's size + input
 * page's size > page's max size, then redistribute. Otherwise, merge.
 * Using template N to represent either internal page or leaf page.
 * @return: true means target leaf page should be deleted, false means no
 * deletion happens
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
bool BPLUSTREE_TYPE::CoalesceOrRedistribute(N *node, Transaction *transaction) {
  return false;
}

/*
 * Move all the key & value pairs from one page to its sibling page, and notify
 * buffer pool manager to delete this page. Parent page must be adjusted to
 * take info of deletion into account. Remember to deal with coalesce or
 * redistribute recursively if necessary.
 * Using template N to represent either internal page or leaf page.
 * @param   neighbor_node      sibling page of input "node"
 * @param   node               input from method coalesceOrRedistribute()
 * @param   parent             parent page of input "node"
 * @return  true means parent node should be deleted, false means no deletion
 * happend
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
bool BPLUSTREE_TYPE::Coalesce(N **neighbor_node, N **node,
                              BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator> **parent, int index,
                              Transaction *transaction) {
  return false;
}

/*
 * Redistribute key & value pairs from one page to its sibling page. If index ==
 * 0, move sibling page's first key & value pair into end of input "node",
 * otherwise move sibling page's last key & value pair into head of input
 * "node".
 * Using template N to represent either internal page or leaf page.
 * @param   neighbor_node      sibling page of input "node"
 * @param   node               input from method coalesceOrRedistribute()
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
void BPLUSTREE_TYPE::Redistribute(N *neighbor_node, N *node, int index) {}
/*
 * Update root page if necessary
 * NOTE: size of root page can be less than min size and this method is only
 * called within coalesceOrRedistribute() method
 * case 1: when you delete the last element in root page, but root page still
 * has one last child
 * case 2: when you delete the last element in whole b+ tree
 * @return : true means root page should be deleted, false means no deletion
 * happend
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::AdjustRoot(BPlusTreePage *old_root_node) { return false; }

/*****************************************************************************
 * INDEX ITERATOR
 *****************************************************************************/
/*
 * Input parameter is void, find the leaftmost leaf page first, then construct
 * index iterator
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE BPLUSTREE_TYPE::Begin() { return INDEXITERATOR_TYPE(); }

/*
 * Input parameter is low key, find the leaf page that contains the input key
 * first, then construct index iterator
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE BPLUSTREE_TYPE::Begin(const KeyType &key) { return INDEXITERATOR_TYPE(); }

/*
 * Input parameter is void, construct an index iterator representing the end
 * of the key/value pair in the leaf node
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE BPLUSTREE_TYPE::End() { return INDEXITERATOR_TYPE(); }

/*****************************************************************************
 * UTILITIES AND DEBUG
 *****************************************************************************/
/*
 * Find leaf page containing particular key, if leftMost flag == true, find
 * the left most leaf page
 */
//TODOA: 写的bug好多，问题在于，第一层并不知道当前的是InternPage还是LeafPage，因此要用公共的BPlusTreePage。但是用了这玩意儿，又不好判断具体是什么类型
INDEX_TEMPLATE_ARGUMENTS
Page *BPLUSTREE_TYPE::FindLeafPage(const KeyType &key, bool leftMost) {
  // Page *tmp_root_page = buffer_pool_manager_->FetchPage(root_page_id_);
  // BPlusTreePage *cur = reinterpret_cast<BPlusTreePage*> (tmp_root_page->GetData());
  // buffer_pool_manager_->UnpinPage(root_page_id_);
  // while(cur->page_type_ != IndexPageType::LEAF_PAGE) {
  //   InternalPage* internal_cur = reinterpret_cast<InternalPage*> (cur);
  //   ValueType result = internal_cur->Lookup(key, comparator_);
  //   cur = reinterpret_cast<BPlusTreePage*> (buffer_pool_manager_->FetchPage(result)->GetData());
  //   buffer_pool_manager_->UnpinPage(result);
  // } 
  // ValueType tmp_value;
  // if(leftMost != true) {
  //   if(!tmp_cur->Lookup(key, &tmp_value, comparator_)) {
  //     return nullptr;
  //   } 
  // } else {
  //   tmp_value = tmp_cur->array_[0].second;
  // }
  // return buffer_pool_manager_->FetchPage(tmp_value);
}
INDEX_TEMPLATE_ARGUMENTS
std::pair<Page*, bool> BPLUSTREE_TYPE::FindLeafPageByOperation(const KeyType &key, Operation operation, Transaction *transaction, bool leftMost, bool rightMost) {
  assert(operation == Operation::FINE ? !(leftMost && rightMost) : transaction != nullptr);

  root_latch_.lock();//每次只能有一个线程进入FindLeafPageByOperation的操作
  bool is_root_page_latched = true;
  Page *page = buffer_pool_manager_->FetchPage(root_page_id_);
  BPlusTreePage *node = reinterpret_cast<BPlusTreePage *> (page->GetData());

  if(operation == Operation::FIND) {
    page->RLatch();
    is_root_page_latched = false;
    root_latch_.unlock();
  } else {
    page->WLatch();
    if(IsSafe(node, operation)) {
      is_root_page_latched = false;
      root_latch_.unlock();
    }
  }
  while(!node->IsLeafPage()) {
    InternalPage *cur = reinterpret_cast<InternalPage *> (node);
    page_id_t next;
    if(leftMost) {
      next = cur->array_[0].second;
    } else if(rightMost) {
      next = cur->array_[cur->GetSize() - 1].second;
    } else {
      next = cur->Lookup(key, comparator_);
    } 
    Page *tmp_next_page = buffer_pool_manager_->FetchPage(next);
    BPlusTreePage *next_page = reinterpret_cast<BPlusTreePage*>(tmp_next_page);

    node = next_page;
  }
  return std::make_pair<node, is_root_page_latched>;
}

INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::UnlockUnpinPages(Transaction *transaction) {
  if(transaction == nullptr) {
    return;
  }
  for(Page *page: *transaction->GetPageSet()) {
    page->WUnlatch();
    buffer_pool_manager_->UnpinPage(page->GetPageId(), false);
  }
  transaction->GetPageSet()->clear();
}
/*
 * Update/Insert root page id in header page(where page_id = 0, header_page is
 * defined under include/page/header_page.h)
 * Call this method everytime root page id is changed.
 * @parameter: insert_record      defualt value is false. When set to true,
 * insert a record <index_name, root_page_id> into header page instead of
 * updating it.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::UpdateRootPageId(int insert_record) {
  HeaderPage *header_page = static_cast<HeaderPage *>(buffer_pool_manager_->FetchPage(HEADER_PAGE_ID));
  if (insert_record != 0) {
    // create a new record<index_name + root_page_id> in header_page
    header_page->InsertRecord(index_name_, root_page_id_);
  } else {
    // update root_page_id in header_page
    header_page->UpdateRecord(index_name_, root_page_id_);
  }
  buffer_pool_manager_->UnpinPage(HEADER_PAGE_ID, true);
}

/*
 * This method is used for test only
 * Read data from file and insert one by one
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::InsertFromFile(const std::string &file_name, Transaction *transaction) {
  int64_t key;
  std::ifstream input(file_name);
  while (input) {
    input >> key;

    KeyType index_key;
    index_key.SetFromInteger(key);
    RID rid(key);
    Insert(index_key, rid, transaction);
  }
}
/*
 * This method is used for test only
 * Read data from file and remove one by one
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::RemoveFromFile(const std::string &file_name, Transaction *transaction) {
  int64_t key;
  std::ifstream input(file_name);
  while (input) {
    input >> key;
    KeyType index_key;
    index_key.SetFromInteger(key);
    Remove(index_key, transaction);
  }
}

/**
 * This method is used for debug only, You don't  need to modify
 * @tparam KeyType
 * @tparam ValueType
 * @tparam KeyComparator
 * @param page
 * @param bpm
 * @param out
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::ToGraph(BPlusTreePage *page, BufferPoolManager *bpm, std::ofstream &out) const {
  std::string leaf_prefix("LEAF_");
  std::string internal_prefix("INT_");
  if (page->IsLeafPage()) {
    LeafPage *leaf = reinterpret_cast<LeafPage *>(page);
    // Print node name
    out << leaf_prefix << leaf->GetPageId();
    // Print node properties
    out << "[shape=plain color=green ";
    // Print data of the node
    out << "label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
    // Print data
    out << "<TR><TD COLSPAN=\"" << leaf->GetSize() << "\">P=" << leaf->GetPageId() << "</TD></TR>\n";
    out << "<TR><TD COLSPAN=\"" << leaf->GetSize() << "\">"
        << "max_size=" << leaf->GetMaxSize() << ",min_size=" << leaf->GetMinSize() << ",size=" << leaf->GetSize()
        << "</TD></TR>\n";
    out << "<TR>";
    for (int i = 0; i < leaf->GetSize(); i++) {
      out << "<TD>" << leaf->KeyAt(i) << "</TD>\n";
    }
    out << "</TR>";
    // Print table end
    out << "</TABLE>>];\n";
    // Print Leaf node link if there is a next page
    if (leaf->GetNextPageId() != INVALID_PAGE_ID) {
      out << leaf_prefix << leaf->GetPageId() << " -> " << leaf_prefix << leaf->GetNextPageId() << ";\n";
      out << "{rank=same " << leaf_prefix << leaf->GetPageId() << " " << leaf_prefix << leaf->GetNextPageId() << "};\n";
    }

    // Print parent links if there is a parent
    if (leaf->GetParentPageId() != INVALID_PAGE_ID) {
      out << internal_prefix << leaf->GetParentPageId() << ":p" << leaf->GetPageId() << " -> " << leaf_prefix
          << leaf->GetPageId() << ";\n";
    }
  } else {
    InternalPage *inner = reinterpret_cast<InternalPage *>(page);
    // Print node name
    out << internal_prefix << inner->GetPageId();
    // Print node properties
    out << "[shape=plain color=pink ";  // why not?
    // Print data of the node
    out << "label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
    // Print data
    out << "<TR><TD COLSPAN=\"" << inner->GetSize() << "\">P=" << inner->GetPageId() << "</TD></TR>\n";
    out << "<TR><TD COLSPAN=\"" << inner->GetSize() << "\">"
        << "max_size=" << inner->GetMaxSize() << ",min_size=" << inner->GetMinSize() << ",size=" << inner->GetSize()
        << "</TD></TR>\n";
    out << "<TR>";
    for (int i = 0; i < inner->GetSize(); i++) {
      out << "<TD PORT=\"p" << inner->ValueAt(i) << "\">";
      if (i > 0) {
        out << inner->KeyAt(i);
      } else {
        out << " ";
      }
      out << "</TD>\n";
    }
    out << "</TR>";
    // Print table end
    out << "</TABLE>>];\n";
    // Print Parent link
    if (inner->GetParentPageId() != INVALID_PAGE_ID) {
      out << internal_prefix << inner->GetParentPageId() << ":p" << inner->GetPageId() << " -> " << internal_prefix
          << inner->GetPageId() << ";\n";
    }
    // Print leaves
    for (int i = 0; i < inner->GetSize(); i++) {
      auto child_page = reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(inner->ValueAt(i))->GetData());
      ToGraph(child_page, bpm, out);
      if (i > 0) {
        auto sibling_page = reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(inner->ValueAt(i - 1))->GetData());
        if (!sibling_page->IsLeafPage() && !child_page->IsLeafPage()) {
          out << "{rank=same " << internal_prefix << sibling_page->GetPageId() << " " << internal_prefix
              << child_page->GetPageId() << "};\n";
        }
        bpm->UnpinPage(sibling_page->GetPageId(), false);
      }
    }
  }
  bpm->UnpinPage(page->GetPageId(), false);
}

/**
 * This function is for debug only, you don't need to modify
 * @tparam KeyType
 * @tparam ValueType
 * @tparam KeyComparator
 * @param page
 * @param bpm
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::ToString(BPlusTreePage *page, BufferPoolManager *bpm) const {
  if (page->IsLeafPage()) {
    LeafPage *leaf = reinterpret_cast<LeafPage *>(page);
    std::cout << "Leaf Page: " << leaf->GetPageId() << " parent: " << leaf->GetParentPageId()
              << " next: " << leaf->GetNextPageId() << std::endl;
    for (int i = 0; i < leaf->GetSize(); i++) {
      std::cout << leaf->KeyAt(i) << ",";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  } else {
    InternalPage *internal = reinterpret_cast<InternalPage *>(page);
    std::cout << "Internal Page: " << internal->GetPageId() << " parent: " << internal->GetParentPageId() << std::endl;
    for (int i = 0; i < internal->GetSize(); i++) {
      std::cout << internal->KeyAt(i) << ": " << internal->ValueAt(i) << ",";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < internal->GetSize(); i++) {
      ToString(reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(internal->ValueAt(i))->GetData()), bpm);
    }
  }
  bpm->UnpinPage(page->GetPageId(), false);
}

template class BPlusTree<GenericKey<4>, RID, GenericComparator<4>>;
template class BPlusTree<GenericKey<8>, RID, GenericComparator<8>>;
template class BPlusTree<GenericKey<16>, RID, GenericComparator<16>>;
template class BPlusTree<GenericKey<32>, RID, GenericComparator<32>>;
template class BPlusTree<GenericKey<64>, RID, GenericComparator<64>>;

}  // namespace bustub
