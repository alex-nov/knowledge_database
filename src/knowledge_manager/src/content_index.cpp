#include "content_index.hpp"
#include "database_manager.hpp"

#include <logger/logger.h>

bool ContentIndex::Init(const std::string & theme_id)

#define log_error_m   alog::logger().error   (alog_line_location, "ContentIndex")
#define log_info_m    alog::logger().info    (alog_line_location, "ContentIndex")
#define log_debug_m   alog::logger().debug   (alog_line_location, "ContentIndex")
{
    LoadFromDB(theme_id);
    log_info_m << "ContentIndex::Init theme_id = \"" << theme_id << "\"";
    return !_theme_index.empty();
}

std::string ContentIndex::LoadFromDB(const std::string & theme)
{
    _theme_index = DatabaseManager::Instance().GetIndexForTheme(theme);
    if (!_theme_index.empty())
    log_info_m << "ContentIndex::LoadThemeFromDB theme_id = \"" << theme_id << "\"";
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
    log_info_m << "ContentIndex::AddIndexUnit index_id = \"" << new_index->id << "\"";
    _active_index = new_index;
}
    log_info_m << "ContentIndex::DeleteIndexUnit uuid = \"" << uuid << "\"";

    log_info_m << "ContentIndex::GetActiveIndexUnit";

    log_info_m << "ContentIndex::Clear";
#undef log_error_m
#undef log_info_m
#undef log_debug_m
