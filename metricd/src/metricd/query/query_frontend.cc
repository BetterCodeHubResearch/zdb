/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Paul Asmuth, FnordCorp B.V. <paul@asmuth.com>
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <assert.h>
#include "metricd/query/query_frontend.h"
#include "metricd/util/format.h"

namespace fnordmetric {

QueryFrontend::QueryFrontend(
    MetricService* metric_service) :
    metric_service_(metric_service) {}

} // namespace fnordmetric

