#pragma once

#include "common.hpp"
#include "content_index.hpp"
#include "database_manager.hpp"

#include <memory>

class ContentPage
{
public:

    ContentPage() {}

    // TODO: return current page, app can display. string json?
    void LoadTheme(const std::string & uuid);
    void LoadUnit(const std::string & uuid);
    std::string ToJson();

private:
    std::shared_ptr<ContentUnit> _content;
    std::weak_ptr<ContentIndex>   _index;

    std::weak_ptr<DatabaseManager> _db;

    std::string _active_unit_id;

};