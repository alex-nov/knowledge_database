#pragma once

#include <memory>
#include <string>

#include <pqxx/pqxx>

#include "common.hpp"

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
    const std::string_view text       = "TEXT";
    const std::string_view integer    = "INT";
    const std::string_view boolean    = "BOOLEAN";
    const std::string_view real       = "REAL";
    const std::string_view timestampz = "TIMESTAMP WITH TIME ZONE";
}

class DatabaseManager : public std::enable_shared_from_this<DatabaseManager>
{
public:
    static std::shared_ptr<DatabaseManager> Instance()
    {
        static std::shared_ptr<DatabaseManager> _DM;
        if (!_DM)
        {
            _DM = std::shared_ptr<DatabaseManager>();
        }
        return _DM;
    }

    virtual ~DatabaseManager()
    {};

    void Init(const string & db_options_str);

    bool InsertTheme(const ThemeTuple & theme);
    ThemeTuple GetTheme(const std::string & theme_uuid) const;
    std::vector<ThemeTuple> GetAllThemes() const;

    bool InsertUnit(const  std::shared_ptr<ContentUnit> unit );
    std::shared_ptr<ContentUnit> LoadUnit(const  string & unit_uuid ) const;

    int32_t InsertIndexUnit(std::shared_ptr<ContentIndexUnit> index_unit);
    std::vector< std::shared_ptr<ContentIndexUnit> > GetIndexForTheme(const std::string & theme_id);

private:
    DatabaseManager()
    {
        // default
        _db_options = DatabaseOptions{.dbname = "knowledge", .user="know", .password = "know", .hostaddr = "127.0.0.1", .port = 5432};
    };

    DatabaseOptions _db_options;
    std::unique_ptr<pqxx::connection> _conn_ptr;
};
