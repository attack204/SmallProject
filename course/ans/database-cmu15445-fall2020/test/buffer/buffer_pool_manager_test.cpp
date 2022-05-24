//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// buffer_pool_manager_test.cpp
//
// Identification: test/buffer/buffer_pool_manager_test.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/buffer_pool_manager.h"
#include <cstdio>
#include <random>
#include <string>
#include "gtest/gtest.h"
#include "include/common/logger.h"  // 日志调试

namespace bustub {

// NOLINTNEXTLINE
// Check whether pages containing terminal characters can be recovered
// TEST(BufferPoolManagerTest, DISABLED_BinaryDataTest) {
TEST(BufferPoolManagerTest, DISABLED_BinaryDataTest) {
  const std::string db_name = "test.db";
  const size_t buffer_pool_size = 10;

  std::random_device r;
  std::default_random_engine rng(r());
  std::uniform_int_distribution<char> uniform_dist(0);

  auto *disk_manager = new DiskManager(db_name);
  auto *bpm = new BufferPoolManager(buffer_pool_size, disk_manager);

  page_id_t page_id_temp;
  auto *page0 = bpm->NewPage(&page_id_temp);  // 需要实现NewPageImpl

  // Scenario: The buffer pool is empty. We should be able to create a new page.
  ASSERT_NE(nullptr, page0);
  EXPECT_EQ(0, page_id_temp);  // 创建第一个page，其page_id为0

  char random_binary_data[PAGE_SIZE];
  // Generate random binary data
  for (char &i : random_binary_data) {
    i = uniform_dist(rng);
  }

  // Insert terminal characters both in the middle and at end
  random_binary_data[PAGE_SIZE / 2] = '\0';
  random_binary_data[PAGE_SIZE - 1] = '\0';

  // Scenario: Once we have a page, we should be able to read and write content.
  std::memcpy(page0->GetData(), random_binary_data, PAGE_SIZE);  // write content to page0
  EXPECT_EQ(0, std::memcmp(page0->GetData(), random_binary_data, PAGE_SIZE));

  // Scenario: We should be able to create new pages until we fill up the buffer pool.
  for (size_t i = 1; i < buffer_pool_size; ++i) {
    EXPECT_NE(nullptr, bpm->NewPage(&page_id_temp));
    // 创建pages，page_id为1~9，frame_id为1~9
    // 因为frame_id优先从free_list中的首部取得，page_id和frame_id暂时相等；page_table同步更新
    // 注意，新建pages的pin_count=1
  }
  // 缓冲池已满，free_list为空

  // Scenario: Once the buffer pool is full, we should not be able to create any new pages.
  for (size_t i = buffer_pool_size; i < buffer_pool_size * 2; ++i) {
    EXPECT_EQ(nullptr, bpm->NewPage(&page_id_temp));  // 缓冲池已满，无法创建page
  }

  // Scenario: After unpinning pages {0, 1, 2, 3, 4} and pinning another 4 new pages,
  // there would still be one cache frame left for reading page 0.
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(true, bpm->UnpinPage(i, true));  // 将page_id 0~4取消固定(pin_count--)，并置dirty为true
    // 此时page_id 0~4的pin_count均为0，将会调用replacer->unpin，从而将frame_id 0~4依次加入到replacer首部中
    bpm->FlushPage(i);  // 将page_id 0~4写入磁盘(不考虑pin_count和dirty变量，也不修改它们)
  }

  // my test
  for (size_t i = 0; i < buffer_pool_size; i++) {
    LOG_INFO("frame_id=%lu pin_count=%d", i, (bpm->GetPages() + i)->GetPinCount());  // size_t = long unsigned int
  }
  // 当前状态
  // page_table             page_id 0~9 对应 frame_id 0~9
  // page/frame_id 0~4      pin_count=0
  // page/frame_id 5~9      pin_count=1
  // replacer<frame_id>     {4,3,2,1,0}
  // free_list<frame_id>    空

  // After unpinning pages {0, 1, 2, 3, 4} we should be able to create 5 new pages
  for (int i = 0; i < 5; ++i) {
    EXPECT_NE(nullptr,
              bpm->NewPage(&page_id_temp));  // 能重新分配page_id 0~4，pin_count=1，从replacer尾部取出frame_id 0~4
    bpm->UnpinPage(page_id_temp, false);  // 将page_id 0~4取消固定(pin_count--)，保持原来的dirty状态
    // 此时page_id 0~4的pin_count均为0，将会调用replacer->unpin，从而将frame_id 0~4依次加入到replacer首部中
  }

  // my test
  for (size_t i = 0; i < buffer_pool_size; i++) {
    LOG_INFO("frame_id=%lu pin_count=%d", i, (bpm->GetPages() + i)->GetPinCount());  // size_t = long unsigned int
  }
  // 当前状态
  // page_table             page_id 10~14 对应 frame_id 0~4（page_id 0~4已从页表中删去）
  // page_table             page_id 5~9 对应 frame_id 5~9
  // frame_id 0~4           pin_count=0
  // frame_id 5~9           pin_count=1
  // replacer<frame_id>     {4,3,2,1,0}
  // free_list<frame_id>    空

  // Scenario: We should be able to fetch the data we wrote a while ago.
  page0 = bpm->FetchPage(0);
  // 页表中不存在page_id=0，那么从replacer中取出victim frame，frame_id=0
  // 将page_id=0的页的内容 读出到 缓冲区中frame_id=0位置的页
  // 此时pin_count=1
  EXPECT_EQ(0, memcmp(page0->GetData(), random_binary_data, PAGE_SIZE));
  EXPECT_EQ(true, bpm->UnpinPage(0, true));

  // Shutdown the disk manager and remove the temporary file we created.
  disk_manager->ShutDown();
  remove("test.db");

  delete bpm;
  delete disk_manager;
}

// NOLINTNEXTLINE
// TEST(BufferPoolManagerTest, DISABLED_SampleTest) {
TEST(BufferPoolManagerTest, DISABLED_SampleTest) {
  const std::string db_name = "test.db";
  const size_t buffer_pool_size = 10;

  auto *disk_manager = new DiskManager(db_name);
  auto *bpm = new BufferPoolManager(buffer_pool_size, disk_manager);

  page_id_t page_id_temp;
  auto *page0 = bpm->NewPage(&page_id_temp);

  // Scenario: The buffer pool is empty. We should be able to create a new page.
  ASSERT_NE(nullptr, page0);
  EXPECT_EQ(0, page_id_temp);

  // Scenario: Once we have a page, we should be able to read and write content.
  snprintf(page0->GetData(), PAGE_SIZE, "Hello");
  EXPECT_EQ(0, strcmp(page0->GetData(), "Hello"));

  // Scenario: We should be able to create new pages until we fill up the buffer pool.
  for (size_t i = 1; i < buffer_pool_size; ++i) {
    EXPECT_NE(nullptr, bpm->NewPage(&page_id_temp));
  }

  // Scenario: Once the buffer pool is full, we should not be able to create any new pages.
  for (size_t i = buffer_pool_size; i < buffer_pool_size * 2; ++i) {
    EXPECT_EQ(nullptr, bpm->NewPage(&page_id_temp));
  }

  // Scenario: After unpinning pages {0, 1, 2, 3, 4} and pinning another 4 new pages,
  // there would still be one buffer page left for reading page 0.
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(true, bpm->UnpinPage(i, true));
  }
  for (int i = 0; i < 4; ++i) {
    EXPECT_NE(nullptr, bpm->NewPage(&page_id_temp));
  }

  // Scenario: We should be able to fetch the data we wrote a while ago.
  page0 = bpm->FetchPage(0);
  EXPECT_EQ(0, strcmp(page0->GetData(), "Hello"));

  // Scenario: If we unpin page 0 and then make a new page, all the buffer pages should
  // now be pinned. Fetching page 0 should fail.
  EXPECT_EQ(true, bpm->UnpinPage(0, true));
  EXPECT_NE(nullptr, bpm->NewPage(&page_id_temp));
  EXPECT_EQ(nullptr, bpm->FetchPage(0));

  // Shutdown the disk manager and remove the temporary file we created.
  disk_manager->ShutDown();
  remove("test.db");

  delete bpm;
  delete disk_manager;
}

template <typename... Args>
void LaunchParallelTest(uint64_t num_threads, Args &&... args) {
  std::vector<std::thread> thread_group;

  // Launch a group of threads
  for (uint64_t thread_itr = 0; thread_itr < num_threads; ++thread_itr) {
    thread_group.push_back(std::thread(args..., thread_itr));
  }

  // Join the threads with the main thread
  for (uint64_t thread_itr = 0; thread_itr < num_threads; ++thread_itr) {
    thread_group[thread_itr].join();
  }
}

// helper function to PinPage
void NewPageHelper(BufferPoolManager *bpm, Page **page, page_id_t *page_id) {
  *page = bpm->NewPage(page_id);
  // LOG_INFO("page id=%d page data=%s", (*page)->GetPageId(), (*page)->GetData());
}

TEST(BufferPoolManagerTest, my_concurrent_SampleTest) {
  const std::string db_name = "test.db";
  const size_t buffer_pool_size = 10;

  auto *disk_manager = new DiskManager(db_name);
  BufferPoolManager *bpm = new BufferPoolManager(buffer_pool_size, disk_manager);

  page_id_t page_id_temp;
  // Page *page0 = bpm->NewPage(&page_id_temp);
  Page *page0 = nullptr;
  NewPageHelper(bpm, &page0, &page_id_temp);
  // LaunchParallelTest(1, NewPageHelper, bpm, &page0, &page_id_temp);  // 有问题，编译不通过
  assert(page0 != nullptr);

  // Scenario: The buffer pool is empty. We should be able to create a new page.
  ASSERT_NE(nullptr, page0);
  EXPECT_EQ(0, page_id_temp);

  // Scenario: Once we have a page, we should be able to read and write content.
  snprintf(page0->GetData(), PAGE_SIZE, "Hello");
  EXPECT_EQ(0, strcmp(page0->GetData(), "Hello"));

  // Scenario: We should be able to create new pages until we fill up the buffer pool.
  for (size_t i = 1; i < buffer_pool_size; ++i) {
    EXPECT_NE(nullptr, bpm->NewPage(&page_id_temp));
  }

  // Scenario: Once the buffer pool is full, we should not be able to create any new pages.
  for (size_t i = buffer_pool_size; i < buffer_pool_size * 2; ++i) {
    EXPECT_EQ(nullptr, bpm->NewPage(&page_id_temp));
  }

  // Scenario: After unpinning pages {0, 1, 2, 3, 4} and pinning another 4 new pages,
  // there would still be one buffer page left for reading page 0.
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(true, bpm->UnpinPage(i, true));
  }
  for (int i = 0; i < 4; ++i) {
    EXPECT_NE(nullptr, bpm->NewPage(&page_id_temp));
  }

  // Scenario: We should be able to fetch the data we wrote a while ago.
  page0 = bpm->FetchPage(0);
  EXPECT_EQ(0, strcmp(page0->GetData(), "Hello"));

  // Scenario: If we unpin page 0 and then make a new page, all the buffer pages should
  // now be pinned. Fetching page 0 should fail.
  EXPECT_EQ(true, bpm->UnpinPage(0, true));
  EXPECT_NE(nullptr, bpm->NewPage(&page_id_temp));
  EXPECT_EQ(nullptr, bpm->FetchPage(0));

  // Shutdown the disk manager and remove the temporary file we created.
  disk_manager->ShutDown();
  remove("test.db");

  delete bpm;
  delete disk_manager;
}

}  // namespace bustub
