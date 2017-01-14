/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Paul Asmuth, FnordCorp B.V. <paul@asmuth.com>
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <metricd/sensor_http.h>
#include <metricd/util/time.h>

namespace fnordmetric {

uint64_t HTTPSensorTask::getNextInvocationTime() const {
  return MonotonicClock::now() + 1 * kMicrosPerSecond;
}

ReturnCode HTTPSensorTask::invoke() {
  return ReturnCode::success();
}

} // namespace fnordmetric
