#pragma once

#include <memory>
#include <string>

#include <pqxx/pqxx>

#include "common.hpp"
#include "content_unit.hpp"

using std::string;

struct DatabaseOptions
{
    string dbname;
    string user;
    string password;

    string hostaddr;
    int16_t port;
};

namespace sql_types
{
    const std::string_view text  = "TEXT";
    const std::string_view integer    = "INT";
    const std::string_view biginteger = "BIGINT";
    const std::string_view boolean    = "BOOLEAN";
    const std::string_view real       = "REAL";
    const std::string_view timestamp  = "TIMESTAMP";
    const std::string_view timestampz = "TIMESTAMP WITH TIME ZONE";
    const std::string_view binary     = "BYTEA";
    const std::string_view hstore     = "HSTORE";
    const std::string_view jsonb      = "JSONB";
}

class DatabaseManager
{
public:
    DatabaseManager()
    {
        // default
        _db_options = DatabaseOptions{.dbname = "knowledge", .user="know", .password = "know", .hostaddr = "127.0.0.1", .port = 5432};
    };

    virtual ~DatabaseManager()
    {};

    void Init( string db_options_str );

    bool InsertTheme(const ThemeTuple & theme);
    ThemeTuple GetTheme(std::string theme_uuid);

    bool SaveUnit( std::shared_ptr<ContentUnit> unit );
    std::shared_ptr<ContentUnit> LoadUnit( string & unit_uuid );
    std::vector< std::shared_ptr<ContentUnit> > LoadTheme( string & theme_uuid );

private:
    DatabaseOptions _db_options;
    std::unique_ptr<pqxx::connection> _conn_ptr;
};
