#include "database_manager.hpp"

#include <fmt/core.h>

#include "utils/utils.hpp"

void DatabaseManager::Init( string db_options_str )
{
    //TODO : parse optins

    // TODO connect format
    auto connect_string = fmt::format("dbname = {0} user = {1} password = {2} {3} = {4} port = {5}",
                            _db_options.dbname,                                             // 0
                            _db_options.user,                                               // 1
                            _db_options.password,                                           // 2
                            utils::isIP(_db_options.hostaddr.c_str()) ? "hostaddr" : "host", // 3
                            _db_options.hostaddr,                                           // 4
                            _db_options.port);                                              // 5


    auto pqxx_connection = std::make_unique<pqxx::connection>(connect_string);
}

bool DatabaseManager::SaveUnit( std::shared_ptr<ContentUnit> unit )
{

    return true;
}

std::shared_ptr<ContentUnit> DatabaseManager::LoadUnit( std::string & unit_uuid )
{

    return std::shared_ptr<ContentUnit>();
}

std::vector< std::shared_ptr<ContentUnit> > DatabaseManager::LoadTheme( std::string & theme_uuid )
{

    return {};
}
