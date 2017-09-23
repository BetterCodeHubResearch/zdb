/**
 * Copyright (c) 2016, Paul Asmuth <paul@asmuth.com>
 * All rights reserved.
 * 
 * This file is part of the "libzdb" project. libzdb is free software licensed
 * under the 3-Clause BSD License (BSD-3-Clause).
 */
#pragma once
#include <stdlib.h>
#include <atomic>
#include <memory>
#include <map>
#include <mutex>
#include "page_buffer.h"

namespace zdb {

/*

struct PageInfo {
  uint64_t version;
  bool is_dirty;
  uint64_t disk_addr;
  uint64_t disk_size;
};

*/

class page_map {
public:

/*
  using PageIDType = size_t;

  PageMap(int fd);
  PageMap(const PageMap& o) = delete;
  PageMap& operator=(const PageMap& o) = delete;
  ~PageMap();

  PageIDType allocPage(uint64_t value_size);

  PageIDType addColdPage(
      uint64_t value_size,
      uint64_t disk_addr,
      uint64_t disk_size);

  bool getPageInfo(PageIDType page_id, PageInfo* info);

  bool getPage(PageIDType page_id, PageBuffer* buf);

  bool modifyPage(
      PageIDType page_id,
      std::function<bool (PageBuffer* buf)> fn);

  void flushPage(
      PageIDType page_id,
      uint64_t version,
      uint64_t disk_addr,
      uint64_t disk_size);

  void deletePage(PageIDType page_id);

protected:

  struct PageMapEntry {
    std::unique_ptr<PageBuffer> buffer;
    std::mutex lock;
    uint64_t version;
    uint64_t value_size;
    uint64_t disk_addr;
    uint64_t disk_size;
    std::atomic<size_t> refcount;
  };

  void dropEntryReference(PageMap::PageMapEntry* entry);

  bool loadPage(
      uint64_t disk_addr,
      uint64_t disk_size,
      uint64_t value_size,
      PageBuffer* buffer);

  int fd_;
  std::mutex mutex_;
  PageIDType page_id_;
  std::map<PageIDType, PageMapEntry*> map_;
*/
};

using page_map_ref = std::shared_ptr<page_map>;

} // namespace zdb

