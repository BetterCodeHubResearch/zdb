/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <string>

namespace fnordmetric {

class Buffer {
public:

  Buffer(const void* initial_data, size_t initial_size);
  Buffer(size_t initial_size);
  Buffer(const Buffer& copy);
  Buffer(Buffer&& move);
  Buffer& operator=(const Buffer& copy) = delete;
  ~Buffer();

  void* data() const;
  size_t size() const;
  std::string toString() const;

protected:
  void* data_;
  size_t size_;
};

}
