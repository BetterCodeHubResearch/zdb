/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Paul Asmuth <paul@asmuth.com>
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../core/util/exception.h"
#include "../core/util/time.h"
#include "../core/zdb.h"
#include "unittest.h"

UNIT_TEST(ZDBTest);

TEST_CASE(ZDBTest, TestCreateAndInsert, [] () {
  unlink("/tmp/__test.zdb");
  auto t0 = WallClock::unixMicros();

  zdb::database_ref db;
  EXPECT_SUCCESS(zdb::open("/tmp/__test.zsb", ZDB_OPEN_DEFAULT, &db));
  EXPECT_SUCCESS(zdb::table_add(db, "mytbl"));
  EXPECT_SUCCESS(zdb::column_add(db, "mytbl", "time", ZDB_UINT64));
  EXPECT_SUCCESS(zdb::column_add(db, "mytbl", "val", ZDB_UINT64));

/*
  {
    std::unique_ptr<tsdb::TSDB> db;
    EXPECT(tsdb::TSDB::createDatabase(&db, "/tmp/__test.tsdb") == true);

    EXPECT(db->createSeries(1, sizeof(uint64_t), "") == true);
    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor, false) == true);
      for (uint64_t i = 0; i < 100000; ++i) {
        cursor.append(t0 + 20 * i, &i, sizeof(i));
      }
    }

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor) == true);

      for (uint64_t i= 0; i < 100000; ++i) {
        uint64_t ts;
        uint64_t value;
        EXPECT(cursor.next(&ts, &value, sizeof(value)) == true);
        EXPECT(ts == t0 + 20 * i);
        EXPECT(value == i);
      }
    }

    EXPECT(db->commit() == true);

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor) == true);

      for (uint64_t i= 0; i < 100000; ++i) {
        uint64_t ts;
        uint64_t value;
        EXPECT(cursor.next(&ts, &value, sizeof(value)) == true);
        EXPECT(ts == t0 + 20 * i);
        EXPECT(value == i);
      }
    }

    EXPECT(db->commit() == true);

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor, false) == true);
      for (uint64_t i = 100000; i < 200000; ++i) {
        cursor.append(t0 + 20 * i, &i, sizeof(i));
      }
    }

    EXPECT(db->commit() == true);

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor) == true);

      for (uint64_t i= 0; i < 200000; ++i) {
        uint64_t ts;
        uint64_t value;
        EXPECT(cursor.next(&ts, &value, sizeof(value)) == true);
        EXPECT(ts == t0 + 20 * i);
        EXPECT(value == i);
      }
    }
  }

  {
    std::unique_ptr<tsdb::TSDB> db;
    EXPECT(tsdb::TSDB::openDatabase(&db, "/tmp/__test.tsdb") == true);

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor) == true);

      for (uint64_t i= 0; i < 200000; ++i) {
        uint64_t ts;
        uint64_t value;
        EXPECT(cursor.next(&ts, &value, sizeof(value)) == true);
        EXPECT(ts == t0 + 20 * i);
        EXPECT(value == i);
      }
    }

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor, false) == true);
      for (uint64_t i= 300000; i < 400000; ++i) {
        cursor.append(t0 + 20 * i, &i, sizeof(i));
      }
    }

    EXPECT(db->commit() == true);

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor) == true);

      for (uint64_t i= 0; i < 200000; ++i) {
        uint64_t ts;
        uint64_t value;
        EXPECT(cursor.next(&ts, &value, sizeof(value)) == true);
        EXPECT(ts == t0 + 20 * i);
        EXPECT(value == i);
      }

      for (uint64_t i= 300000; i < 400000; ++i) {
        uint64_t ts;
        uint64_t value;
        EXPECT(cursor.next(&ts, &value, sizeof(value)) == true);
        EXPECT(ts == t0 + 20 * i);
        EXPECT(value == i);
      }
    }
  }

  {
    std::unique_ptr<tsdb::TSDB> db;
    EXPECT(tsdb::TSDB::openDatabase(&db, "/tmp/__test.tsdb") == true);

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor, false) == true);
      cursor.seekTo(t0 + 20 * 200000);
      for (uint64_t i= 200000; i < 300000; ++i) {
        cursor.insert(t0 + 20 * i, &i, sizeof(i));
        cursor.next();
      }
    }

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor) == true);

      for (uint64_t i= 0; i < 400000; ++i) {
        uint64_t ts;
        uint64_t value;
        EXPECT(cursor.next(&ts, &value, sizeof(value)) == true);
        EXPECT(ts == t0 + 20 * i);
        EXPECT(value == i);
      }
    }

    EXPECT(db->commit() == true);

    {
      tsdb::Cursor cursor;
      EXPECT(db->getCursor(1, &cursor) == true);

      for (uint64_t i= 0; i < 400000; ++i) {
        uint64_t ts;
        uint64_t value;
        EXPECT(cursor.next(&ts, &value, sizeof(value)) == true);
        EXPECT(ts == t0 + 20 * i);
        EXPECT(value == i);
      }
    }
  }
*/
});

/*
TEST_CASE(TSDBTest, TestSeek, [] () {
  unlink("/tmp/__test.tsdb");

  {
    std::unique_ptr<tsdb::TSDB> db;
    EXPECT(tsdb::TSDB::createDatabase(&db, "/tmp/__test.tsdb") == true);

    EXPECT(db->createSeries(1, sizeof(uint64_t), "") == true);
    tsdb::Cursor cursor;
    EXPECT(db->getCursor(1, &cursor, false));
    for (uint64_t i= 1; i <= 50000; ++i) {
      cursor.append(i * 2, &i, sizeof(i));
    }

    EXPECT(db->commit() == true);
  }

  {
    std::unique_ptr<tsdb::TSDB> db;
    EXPECT(tsdb::TSDB::openDatabase(&db, "/tmp/__test.tsdb") == true);

    tsdb::Cursor cursor;
    EXPECT(db->getCursor(1, &cursor));
    EXPECT(cursor.valid() == true);
    {
      uint64_t ts;
      uint64_t value;
      cursor.get(&ts, &value, sizeof(value));
      EXPECT(ts == 2);
      EXPECT(value == 1);
    }
    EXPECT(cursor.next() == true);
    EXPECT(cursor.valid() == true);
    {
      uint64_t ts;
      uint64_t value;
      cursor.get(&ts, &value, sizeof(value));
      EXPECT(ts == 4);
      EXPECT(value == 2);
    }

    cursor.seekTo(1337);
    EXPECT(cursor.valid() == true);
    {
      uint64_t ts;
      uint64_t value;
      cursor.get(&ts, &value, sizeof(value));
      EXPECT(ts == 1338);
      EXPECT(value == 669);
    }

    cursor.seekTo(90000);
    EXPECT(cursor.valid() == true);
    {
      uint64_t ts;
      uint64_t value;
      cursor.get(&ts, &value, sizeof(value));
      EXPECT(ts == 90000);
      EXPECT(value == 45000);
    }

    cursor.seekTo(100000);
    EXPECT(cursor.valid() == true);
    {
      uint64_t ts;
      uint64_t value;
      cursor.get(&ts, &value, sizeof(value));
      EXPECT(ts == 100000);
      EXPECT(value == 50000);
    }

    cursor.seekTo(100001);
    EXPECT(cursor.valid() == false);
  }
});

TEST_CASE(TSDBTest, TestUpdate, [] () {
  unlink("/tmp/__test.tsdb");

  {
    std::unique_ptr<tsdb::TSDB> db;
    EXPECT(tsdb::TSDB::createDatabase(&db, "/tmp/__test.tsdb") == true);

    EXPECT(db->createSeries(1, sizeof(uint64_t), "") == true);
    tsdb::Cursor cursor;
    EXPECT(db->getCursor(1, &cursor, false));
    for (uint64_t i= 1; i <= 50000; ++i) {
      cursor.append(i * 2, &i, sizeof(i));
    }

    EXPECT(db->commit() == true);
  }

  {
    std::unique_ptr<tsdb::TSDB> db;
    EXPECT(tsdb::TSDB::openDatabase(&db, "/tmp/__test.tsdb") == true);

    tsdb::Cursor cursor;
    EXPECT(db->getCursor(1, &cursor, false));
    EXPECT(cursor.valid() == true);
    cursor.seekTo(1337);
    EXPECT(cursor.valid() == true);
    {
      uint64_t ts;
      uint64_t value;
      cursor.get(&ts, &value, sizeof(value));
      EXPECT(ts == 1338);
      EXPECT(value == 669);
    }

    uint64_t new_value = 1234;
    cursor.update(&new_value, sizeof(new_value));

    {
      uint64_t ts;
      uint64_t value;
      cursor.get(&ts, &value, sizeof(value));
      EXPECT(ts == 1338);
      EXPECT(value == 1234);
    }

    EXPECT(db->commit() == true);
  }

  {
    std::unique_ptr<tsdb::TSDB> db;
    EXPECT(tsdb::TSDB::openDatabase(&db, "/tmp/__test.tsdb") == true);

    tsdb::Cursor cursor;
    EXPECT(db->getCursor(1, &cursor));
    EXPECT(cursor.valid() == true);
    cursor.seekTo(1337);
    EXPECT(cursor.valid() == true);
    {
      uint64_t ts;
      uint64_t value;
      cursor.get(&ts, &value, sizeof(value));
      EXPECT(ts == 1338);
      EXPECT(value == 1234);
    }
  }

});
*/

