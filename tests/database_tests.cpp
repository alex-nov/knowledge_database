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

  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme(test_theme) );

  const auto all_themes = DatabaseManager::Instance().GetAllThemes();
  ASSERT_TRUE ( all_themes.size() == 1 );
  EXPECT_TRUE ( all_themes.back() == test_theme );

  EXPECT_FALSE( DatabaseManager::Instance().GetTheme("") == test_theme );
  EXPECT_FALSE( DatabaseManager::Instance().GetTheme( utils::generate_random_string( 10 ) ) == test_theme );
  EXPECT_FALSE( DatabaseManager::Instance().GetTheme( utils::generate_uuid_v4()) == test_theme );
  EXPECT_TRUE ( DatabaseManager::Instance().GetTheme( test_theme.uuid ) == test_theme );
}

TEST_F(DatabaseManagerFixture, DeleteTheme)
{
  ASSERT_TRUE ( DatabaseManager::Instance().GetAllThemes().empty() );

  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme(test_theme) );

  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable( "", database::themes_table_name ) );
  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable( utils::generate_uuid_v4(), database::themes_table_name ) );
  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable( 12, database::themes_table_name ) );

  EXPECT_TRUE ( DatabaseManager::Instance().DeleteFromTable( test_theme.uuid, database::themes_table_name ) );
}

TEST_F(DatabaseManagerFixture, GetEmptyUnit)
{
  EXPECT_FALSE( DatabaseManager::Instance().GetUnit( "" ));
  EXPECT_FALSE( DatabaseManager::Instance().GetUnit( utils::generate_random_string( 10 ) ));
  EXPECT_FALSE( DatabaseManager::Instance().GetUnit( utils::generate_uuid_v4() ));
}

TEST_F(DatabaseManagerFixture, InsertGetUnit)
{
  EXPECT_FALSE( DatabaseManager::Instance().InsertUnitWithIndex( std::make_shared<ContentUnit>( "without_theme", "" ), {} ) );
  EXPECT_FALSE( DatabaseManager::Instance().InsertUnitWithIndex( std::make_shared<ContentUnit>( "wrong_theme_theme", utils::generate_uuid_v4()), {} ) );

  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme( test_theme ) );
  const auto test_unit = GetRandomUnit( test_theme.uuid );
  const auto test_index_element = std::make_shared< ContentIndexUnit >( test_theme.uuid, std::string(""), test_unit->uuid );

  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit, test_index_element ) );
  const auto get_unit = DatabaseManager::Instance().GetUnit( test_unit->uuid );

  EXPECT_FALSE( get_unit->isEmpty() );
  EXPECT_TRUE ( *get_unit == *test_unit );
}

TEST_F(DatabaseManagerFixture, InsertDeleteUnit)
{
  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme( test_theme ) );
  const auto test_unit = GetRandomUnit( test_theme.uuid );
  const auto test_index_element = std::make_shared< ContentIndexUnit >( test_theme.uuid, std::string(""), test_unit->uuid ) ;
  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit, test_index_element ) );

  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable( "", database::units_table_name ) );
  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable( utils::generate_uuid_v4(), database::units_table_name ) );
  EXPECT_FALSE( DatabaseManager::Instance().DeleteFromTable( utils::generate_random_string(10), database::units_table_name ) );

  //with unit always delete it's index
  EXPECT_TRUE ( DatabaseManager::Instance().DeleteFromTable( test_unit->uuid, database::units_table_name ) );

  EXPECT_FALSE ( DatabaseManager::Instance().GetUnit( test_unit->GetUuid() ) );
  EXPECT_TRUE  ( DatabaseManager::Instance().GetIndexForTheme( test_theme.uuid ).empty() );
}

TEST_F(DatabaseManagerFixture, GetEmptyIndex)
{
  EXPECT_TRUE( DatabaseManager::Instance().GetIndexForTheme( "" ).empty() );
  EXPECT_TRUE( DatabaseManager::Instance().GetIndexForTheme( utils::generate_uuid_v4() ).empty() );
  EXPECT_TRUE( DatabaseManager::Instance().GetIndexForTheme( utils::generate_random_string( 10 ) ).empty() );
}

TEST_F(DatabaseManagerFixture, InsertGetIndex)
{
  const auto test_unit = GetRandomUnit( test_theme.uuid );
  const auto test_index_element = std::make_shared< ContentIndexUnit >( test_theme.uuid, std::string( "" ), test_unit->uuid );

  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme( test_theme ) );
  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit, test_index_element ) );

  EXPECT_TRUE ( DatabaseManager::Instance().GetIndexForTheme( "" ).empty() );
  EXPECT_TRUE ( DatabaseManager::Instance().GetIndexForTheme( utils::generate_uuid_v4() ).empty() );
  EXPECT_TRUE ( DatabaseManager::Instance().GetIndexForTheme( utils::generate_random_string(10) ).empty() );

  auto index = DatabaseManager::Instance().GetIndexForTheme( test_theme.uuid );
  ASSERT_FALSE( index.empty() );
  EXPECT_TRUE ( index.back()->unit_uuid == test_index_element->unit_uuid );
  EXPECT_TRUE ( index.back()->parent_uuid == test_index_element->parent_uuid );
  EXPECT_TRUE ( index.back()->theme_uuid == test_index_element->theme_uuid );
}

TEST_F(DatabaseManagerFixture, InsertTwoSameThemeIndexElement)
{
  const auto test_unit = GetRandomUnit( test_theme.uuid );
  const auto test_unit2 = GetRandomUnit( test_theme.uuid );
  auto test_index_element = std::make_shared<ContentIndexUnit>( test_theme.uuid, std::string(""), test_unit->uuid);
  auto test_index_element2 = std::make_shared<ContentIndexUnit>( test_theme.uuid, std::string(""), test_unit2->uuid);

  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme( test_theme ) );
  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit, test_index_element ) );
  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit2, test_index_element2 ) );

  auto index = DatabaseManager::Instance().GetIndexForTheme(test_theme.uuid);
  ASSERT_TRUE ( index.size() == 2 );
  EXPECT_TRUE ( index[ 0 ] != index[ 1 ] );
}

TEST_F(DatabaseManagerFixture, InsertUnitsForTwoDifferentThemes)
{
  const auto test_unit  = GetRandomUnit( test_theme.uuid );
  auto test_index_element  = std::make_shared< ContentIndexUnit >( test_theme.uuid, std::string(""), test_unit->uuid );

  const ThemeTuple test_theme2{ utils::generate_uuid_v4(), "test_theme2" };
  const auto test_unit2 = GetRandomUnit( test_theme2.uuid );
  auto test_index_element2 = std::make_shared< ContentIndexUnit >( test_theme2.uuid, std::string(""), test_unit2->uuid );

  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme( test_theme ) );
  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme( test_theme2 ) );
  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit, test_index_element ) );
  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit2, test_index_element2 ) );

  auto index = DatabaseManager::Instance().GetIndexForTheme( test_theme.uuid );
  ASSERT_TRUE ( index.size() == 1 );
  EXPECT_TRUE ( index.back()->unit_uuid == test_index_element->unit_uuid );
  EXPECT_TRUE ( index.back()->parent_uuid == test_index_element->parent_uuid );
  EXPECT_TRUE ( index.back()->theme_uuid == test_index_element->theme_uuid );

  index = DatabaseManager::Instance().GetIndexForTheme( test_theme2.uuid );
  ASSERT_TRUE ( index.size() == 1 );
  EXPECT_TRUE ( index.back()->unit_uuid == test_index_element2->unit_uuid );
  EXPECT_TRUE ( index.back()->parent_uuid == test_index_element2->parent_uuid );
  EXPECT_TRUE ( index.back()->theme_uuid == test_index_element2->theme_uuid );
}

TEST_F(DatabaseManagerFixture, TreeIndex)
{
  const auto test_unit_parent = GetRandomUnit( test_theme.uuid );
  const auto test_unit_child = GetRandomUnit( test_theme.uuid );
  auto parent_index_element = std::make_shared< ContentIndexUnit >( test_theme.uuid, std::string(""), test_unit_parent->uuid );
  auto child_index_element = std::make_shared< ContentIndexUnit >( test_theme.uuid, test_unit_parent->uuid, test_unit_child->uuid );

  EXPECT_TRUE ( DatabaseManager::Instance().InsertTheme( test_theme ) );
  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit_parent, parent_index_element ) );
  EXPECT_TRUE ( DatabaseManager::Instance().InsertUnitWithIndex( test_unit_child, child_index_element ) );

  auto index = DatabaseManager::Instance().GetIndexForTheme( test_theme.uuid );
  ASSERT_TRUE ( index.size() == 2 );
  auto it = std::find_if( index.begin(), index.end(), [ parent_index_element ]( std::shared_ptr<ContentIndexUnit> index_unit )
                                                            { return parent_index_element->unit_uuid == index_unit->unit_uuid &&
                                                                parent_index_element->parent_uuid == index_unit->parent_uuid &&
                                                                parent_index_element->theme_uuid == index_unit->theme_uuid; });
  EXPECT_TRUE ( it != index.end() );
  it = std::find_if( index.begin(), index.end(), [ child_index_element ]( std::shared_ptr<ContentIndexUnit> index_unit )
                                                            { return child_index_element->unit_uuid == index_unit->unit_uuid &&
                                                                child_index_element->parent_uuid == index_unit->parent_uuid &&
                                                                child_index_element->theme_uuid == index_unit->theme_uuid; });
  EXPECT_TRUE ( it != index.end() );
}
