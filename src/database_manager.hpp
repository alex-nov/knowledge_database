#pragma once

#include <memory>
#include <string>

#include <pqxx/pqxx>

#include "content_unit.hpp"

using std::string;

struct DatabaseOptions
{
    string dbname;
    string user;
    string password;

    string hostaddr;
    int16_t port;
} db_options;



class DatabaseManager
{
public:
    DatabaseManager() {};
    virtual ~DatabaseManager() {};

    void Init( string db_options_str );

    bool SaveUnit( std::shared_ptr<ContentUnit> unit );
    std::shared_ptr<ContentUnit> LoadUnit( string & unit_uuid );
    std::vector< std::shared_ptr<ContentUnit> > LoadTheme( string & theme_uuid );

private:
    DatabaseOptions _db_options;
    std::shared_ptr<pqxx::connection> _conn_ptr;
};
