#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "common.hpp"
#include "database_manager.hpp"


class ContentIndex
{
public:
    ContentIndex() {}
    virtual ~ContentIndex() {}

    bool Init(const std::string & theme_id);

    // return current active unit uuid
    std::string LoadFromDB(const std::string & theme);

    // TODO
    // *to/from json

private:
    std::vector< std::shared_ptr<ContentIndexUnit> > _theme_index;
    std::shared_ptr<ContentIndexUnit> _active_index;

    std::weak_ptr<DatabaseManager> _db;
};