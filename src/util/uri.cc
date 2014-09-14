/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <fnordmetric/util/runtimeexception.h>
#include <fnordmetric/util/uri.h>

namespace fnordmetric {
namespace util {

URI::URI(const std::string& uri_str) : port_(0) {
  parse(uri_str);
}

void URI::parse(const std::string& uri_str) {
  URI::parseURI(
      uri_str,
      &scheme_,
      &userinfo_,
      &host_,
      &port_,
      &path_,
      &query_,
      &fragment_);
}

const std::string& URI::scheme() const {
  return scheme_;
}

const std::string& URI::userinfo() const {
  return userinfo_;
}

const std::string& URI::host() const {
  return host_;
}

const unsigned URI::port() const {
  return port_;
}

const std::string& URI::path() const {
  return path_;
}

const std::string& URI::query() const {
  return query_;
}

const std::vector<std::pair<std::string, std::string>> URI::queryParams()
    const {
  if (query_.size() == 0) {
    return std::vector<std::pair<std::string, std::string>>();
  } else {
    return URI::parseQueryString(query_);
  }
}

const std::string& URI::fragment() const {
  return fragment_;
}

std::string URI::toString() const {
  std::string uri_str;

  uri_str.append(scheme());
  uri_str.append(":");

  if (host_.size() > 0) {
    uri_str.append("//");

    if (userinfo_.size() > 0) {
      uri_str.append(userinfo_);
      uri_str.append("@");
    }

    uri_str.append(host_);

    if (port_ > 0) { // FIXPAUL hasPort
      uri_str.append(":");
      uri_str.append(std::to_string(port_));
    }
  }

  uri_str.append(path_);

  if (query_.size() > 0) {
    uri_str.append("?");
    uri_str.append(query_);
  }

  if (fragment_.size() > 0) {
    uri_str.append("#");
    uri_str.append(fragment_);
  }

  return uri_str;
}

void URI::parseURI(
    const std::string& uri_str,
    std::string* scheme,
    std::string* userinfo,
    std::string* host,
    unsigned* port,
    std::string* path,
    std::string* query,
    std::string* fragment) {
  const char* begin = uri_str.c_str();
  const char* end = begin + uri_str.size();

  /* scheme */
  bool has_scheme = false;
  for (const char* cur = begin; cur < end; ++cur) {
    if (cur[0] == ':') {
      *scheme = std::string(begin, cur - begin);
      begin = cur + 1;
      has_scheme = true;
      break;
    }
  }

  if (!has_scheme) {
    RAISE(util::RuntimeException, "invalid URI: must begin with scheme:");
  }

  /* authority */
  if (begin < end - 2 && begin[0] == '/' && begin[1] == '/') {
    begin += 2;
    const char* cur = begin;
    for (; cur < end && *cur != '/' && *cur != '?' && *cur != '#'; ++cur);
    if (cur > begin) {
      const char* abegin = begin;
      const char* aend = cur;

      /* userinfo */
      for (const char* acur = abegin; acur < aend; ++acur) {
        if (*acur == '/' || *acur == '?' || *acur == '#') {
          break;
        }

        if (*acur == '@') {
          *userinfo = std::string(abegin, acur - abegin);
          abegin = acur + 1;
          break;
        }
      }

      /* host */
      const char* acur = abegin;
      for (; acur < aend &&
            *acur != '/' &&
            *acur != '?' &&
            *acur != '#' &&
            *acur != ':'; ++acur);
      *host = std::string(abegin, acur - abegin);

      /* port */
      if (acur < aend - 1 && *acur == ':') {
        abegin = ++acur;
        for (; *acur >= '0' && *acur <= '9'; ++acur);
        if (acur > abegin) {
          *port = std::stoi(std::string(abegin, acur - abegin));
        }
      }
    }
    begin = cur;
  }

  /* path */
  if (begin < end) {
    const char* cur = begin;
    for (; cur < end && *cur != '?' && *cur != '#'; ++cur);
    if (cur > begin) {
      *path = std::string(begin, cur - begin);
    }
    begin = cur;
  }

  /* query */
  if (begin < end && *begin == '?') {
    const char* cur = ++begin;
    for (; cur < end && *cur != '#'; ++cur);
    if (cur > begin) {
      *query = std::string(begin, cur - begin);
    }
    begin = cur;
  }

  /* fragment */
  if (begin < end - 1 && *begin == '#') {
    *fragment = std::string(begin + 1, end - begin - 1);
  }
}

std::vector<std::pair<std::string, std::string>> URI::parseQueryString(
    const std::string& query) {
  return std::vector<std::pair<std::string, std::string>>();
}

}
}