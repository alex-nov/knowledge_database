#include "content_index.hpp"

bool ContentIndex::Init(const std::string & theme_id)
{
    LoadFromDB(theme_id);
    return !_theme_index.empty();
}

std::string ContentIndex::LoadFromDB(const std::string & theme)
{
    auto database = _db.lock();
    if (!database)
    {
        return "";
    }

    _theme_index = database->GetIndexForTheme(theme);
    if (!_theme_index.empty())
    {
        _active_index = _theme_index.front();
    }
    // TODO:
    // * parse _content
    // * sort content

    // TODO: return _active_index->id(int);
    return _active_index->unit_uuid;
}