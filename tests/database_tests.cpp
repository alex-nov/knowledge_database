#include <gtest/gtest.h>

#include "db_fixture.hpp"
#include "database_manager.hpp"

TEST_F(DatabaseManagerFixture, BasicPingTest)
{
  EXPECT_TRUE( DatabaseManager::Instance().Ping());
}
