#pragma once

#include <memory>
#include <string>

#include <pqxx/pqxx>
#include <gtest/gtest.h>
#include <fmt/core.h>

#include "common.hpp"
#include "database_manager.hpp"


// The fixture for testing class database_manager.
class DatabaseManagerFixture : public testing::Test {
 protected:

DatabaseManagerFixture() {
    auto db_options = DatabaseOptions{.dbname = "kd_test", .user="kd_test", .password = "kd_test", .hostaddr = "127.0.0.1", .port = 5432};
    DatabaseManager::Instance().Init(db_options);
    DatabaseManager::Instance().ClearDB();
  }

  ~DatabaseManagerFixture() override {
    DatabaseManager::Instance().ClearDB();
  }
};