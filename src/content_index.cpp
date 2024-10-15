#include "content_index.hpp"
#include "database_manager.hpp"


bool ContentIndex::Init(const std::string & theme_id)
{
    LoadFromDB(theme_id);
    return !_theme_index.empty();
}

std::string ContentIndex::LoadFromDB(const std::string & theme)
{
    _theme_index = DatabaseManager::Instance().GetIndexForTheme(theme);
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

void ContentIndex::AddElement(std::shared_ptr<ContentIndexUnit> new_index)
{
    _theme_index.push_back(new_index);
    _active_index = new_index;
}
