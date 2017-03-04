/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *   Copyright (c) 2016 Paul Asmuth, FnordCorp B.V. <paul@asmuth.com>
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <fnordmetric/listen_http.h>
#include <fnordmetric/util/logging.h>
#include <fnordmetric/util/stringutil.h>

namespace fnordmetric {

HTTPPushIngestionTaskConfig::HTTPPushIngestionTaskConfig() :
    bind("0.0.0.0"),
    port(8080) {}

ReturnCode HTTPPushIngestionTask::start(
    AggregationService* aggregation_service,
    const IngestionTaskConfig* config,
    std::unique_ptr<IngestionTask>* task) {
  auto c = dynamic_cast<const HTTPPushIngestionTaskConfig*>(config);
  if (!c) {
    return ReturnCode::error("ERUNTIME", "invalid ingestion task config");
  }

  if (c->port == 0) {
    return ReturnCode::error("ERUNTIME", "missing port");
  }

  auto self = new HTTPPushIngestionTask(aggregation_service);
  task->reset(self);

  auto rc = self->listen(c->bind, c->port);
  if (!rc.isSuccess()) {
    return rc;
  }

  return ReturnCode::success();
}

HTTPPushIngestionTask::HTTPPushIngestionTask(
    AggregationService* aggr_service) :
    aggr_service_(aggr_service) {
  http_server_.setRequestHandler(
      std::bind(
          &HTTPPushIngestionTask::handleRequest,
          this,
          std::placeholders::_1,
          std::placeholders::_2));
}

ReturnCode HTTPPushIngestionTask::listen(const std::string& addr, int port) {
  logInfo("Starting HTTP server on $0:$1", addr, port);

  if (http_server_.listen(addr, port)) {
    return ReturnCode::success();
  } else {
    return ReturnCode::error("ERUNTIME", "listen() failed");
  }
}

ReturnCode HTTPPushIngestionTask::start() {
  http_server_thread_ = std::thread([this] { http_server_.run(); });
  http_server_thread_.detach();
  return ReturnCode::success();
}

void HTTPPushIngestionTask::shutdown() {}

void HTTPPushIngestionTask::handleRequest(
    http::HTTPRequest* request,
    http::HTTPResponse* response) {}


} // namespace fnordmetric

