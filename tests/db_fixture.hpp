#pragma once

#include <memory>
#include <string>

#include <pqxx/pqxx>
#include <gtest/gtest.h>
#include <fmt/core.h>

#include "common.hpp"
#include "utils/utils.hpp"
#include "database_manager.hpp"
#include "content_index.hpp"


// The fixture for testing class database_manager.
class DatabaseManagerFixture : public testing::Test {
 protected:

DatabaseManagerFixture() {
    auto db_options = database::DatabaseOptions{.dbname = "kd_test",
                                                .user="kd_test",
                                                .password = "kd_test",
                                                .hostaddr = "127.0.0.1",
                                                .port = 5432};
    DatabaseManager::Instance().Init(db_options);
    DatabaseManager::Instance().ClearDB();

    test_theme = ThemeTuple{ utils::generate_uuid_v4(), "test_theme" };
  }

  ~DatabaseManagerFixture() override
  {
    DatabaseManager::Instance().ClearDB();
  }

  std::shared_ptr< ContentUnit > GetRandomUnit(const std::string & theme_id)
  {
    auto unit = std::make_shared< ContentUnit >( utils::generate_random_string( 10 ), theme_id );
    unit->text = utils::generate_random_string( 20 );
    unit->local_path = utils::generate_random_string( 20 );
    unit->content_url = utils::generate_random_string( 20 );

    return unit;
  }

  ThemeTuple test_theme;
};