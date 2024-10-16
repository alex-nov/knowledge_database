#include <string>

#include <gtest/gtest.h>

#include "database_manager.hpp"
#include "common.hpp"
#include "db_fixture.hpp"
#include "utils/utils.hpp"

TEST_F(DatabaseManagerFixture, BasicPingTest)
{
  ASSERT_TRUE( DatabaseManager::Instance().Ping() );
}

TEST_F(DatabaseManagerFixture, GetEmptyTheme)
{
  EXPECT_TRUE ( DatabaseManager::Instance().GetTheme("").IsEmpty() );
  EXPECT_TRUE ( DatabaseManager::Instance().GetTheme(utils::generate_random_string(10)).IsEmpty() );
  EXPECT_TRUE ( DatabaseManager::Instance().GetTheme(utils::generate_uuid_v4()).IsEmpty() );
  EXPECT_TRUE ( DatabaseManager::Instance().GetAllThemes().empty() );
}

TEST_F(DatabaseManagerFixture, AddGetTheme)
{
  ASSERT_TRUE ( DatabaseManager::Instance().GetAllThemes().empty() );

  const ThemeTuple test_theme{utils::generate_uuid_v4(), "test_theme"};
  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme(test_theme) );

  auto all_themes = DatabaseManager::Instance().GetAllThemes();
  EXPECT_TRUE ( all_themes.size() == 1 );
  EXPECT_TRUE ( all_themes.back() == test_theme );

  EXPECT_FALSE( DatabaseManager::Instance().GetTheme("") == test_theme );
  EXPECT_FALSE( DatabaseManager::Instance().GetTheme(utils::generate_random_string(10)) == test_theme );
  EXPECT_FALSE( DatabaseManager::Instance().GetTheme(utils::generate_uuid_v4()) == test_theme );
  EXPECT_TRUE ( DatabaseManager::Instance().GetTheme(test_theme.uuid) == test_theme );
}

TEST_F(DatabaseManagerFixture, DeleteTheme)
{
  ASSERT_TRUE ( DatabaseManager::Instance().GetAllThemes().empty() );

  const ThemeTuple test_theme{utils::generate_uuid_v4(), "test_theme"};
  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme(test_theme) );

  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable("", database::themes_table_name) );
  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable(utils::generate_uuid_v4(), database::themes_table_name) );
  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable(12, database::themes_table_name) );
  EXPECT_TRUE ( DatabaseManager::Instance().DeleteFromTable(test_theme.uuid, database::themes_table_name) );
}

TEST_F(DatabaseManagerFixture, GetEmptyUnit)
{
  EXPECT_FALSE(DatabaseManager::Instance().GetUnit(""));
  EXPECT_FALSE(DatabaseManager::Instance().GetUnit(utils::generate_random_string(10)));
  EXPECT_FALSE(DatabaseManager::Instance().GetUnit(utils::generate_uuid_v4()));
}

TEST_F(DatabaseManagerFixture, InsertGetUnit)
{
  //printf("___InsertGetUnit 1\n");
  const ThemeTuple test_theme{utils::generate_uuid_v4(), "test_theme"};
  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme(test_theme) );

  auto unit = std::make_shared<ContentUnit>("title", test_theme.uuid);
  unit->text = utils::generate_random_string(20);

  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnit(unit) );
  auto get_unit = DatabaseManager::Instance().GetUnit(unit->uuid);

  EXPECT_FALSE( get_unit->isEmpty() );
  EXPECT_TRUE ( *get_unit == *unit );
}
