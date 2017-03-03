/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Paul Asmuth, FnordCorp B.V. <paul@asmuth.com>
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <list>
#include <thread>
#include <regex>
#include <fnordmetric/util/return_code.h>

namespace fnordmetric {
class MetricService;

struct SensorConfig {
  SensorConfig();
  virtual ~SensorConfig() = default;
  std::string sensor_id;
  bool metric_id_rewrite_enabled;
  std::regex metric_id_rewrite_regex;
  std::string metric_id_rewrite_replace;
};

class SensorTask {
public:

  virtual ~SensorTask() = default;

  virtual uint64_t getNextInvocationTime() const = 0;

  virtual ReturnCode invoke() = 0;

};

ReturnCode mkSensorTask(
    MetricService* metric_service,
    const SensorConfig* sensor_cfg,
    std::unique_ptr<SensorTask>* sensor_task);

class SensorScheduler{
public:

  SensorScheduler(size_t thread_count = 1);
  void addTask(std::unique_ptr<SensorTask> task);

  ReturnCode start();
  void shutdown();

protected:

  ReturnCode executeNextTask();

  size_t thread_count_;
  std::vector<std::thread> threads_;
  std::atomic<bool> running_;

  std::mutex mutex_;
  std::condition_variable cv_;
  std::multiset<
      SensorTask*,
      std::function<bool (
          const SensorTask*,
          const SensorTask*)>> queue_;
  std::list<std::unique_ptr<SensorTask>> tasks_;
};

} // namespace fnordmetric

