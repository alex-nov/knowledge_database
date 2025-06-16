#include "content_index.hpp"
#include "database_manager.hpp"

#include <logger/logger.h>


#define log_error_m   alog::logger().error   (alog_line_location, "ContentIndex")
#define log_info_m    alog::logger().info    (alog_line_location, "ContentIndex")
#define log_debug_m   alog::logger().debug   (alog_line_location, "ContentIndex")

bool ContentIndex::Init( const std::string & theme_id )
{
    log_info_m << "ContentIndex::Init theme_id = \"" << theme_id << "\"";

    Clear();
    LoadThemeFromDB( theme_id );
    return !_theme_index.empty();
}

std::string ContentIndex::LoadThemeFromDB( const std::string & theme_id )
{
    log_info_m << "ContentIndex::LoadThemeFromDB theme_id = \"" << theme_id << "\"";

    // TODO: make safe / if can't load - keep current
    _theme_index = DatabaseManager::Instance().GetIndexForTheme( theme_id );
    if ( !_theme_index.empty() )
    {
        // TODO:
        // * parse _content
        // * set _active_index as first top level unit
        _active_index = _theme_index.front();
    }

    // TODO: return _active_index->id(int);
    if( _active_index )
    {
        return _active_index->unit_uuid;
    }

    return {};
}

void ContentIndex::AddIndexUnit( std::shared_ptr<ContentIndexUnit> new_index )
{
    log_info_m << "ContentIndex::AddIndexUnit index_id = \"" << new_index->id << "\"";

    _theme_index.push_back( new_index );
    _active_index = new_index;
}

void ContentIndex::DeleteIndexUnit( const std::string & uuid )
{
    log_info_m << "ContentIndex::DeleteIndexUnit uuid = \"" << uuid << "\"";

    if( _theme_index.empty() )
    {
        return;
    }

    auto it = std::find_if( _theme_index.begin(), _theme_index.end(),
                            [ uuid ]( std::shared_ptr< ContentIndexUnit > index )
                            {
                                return index->unit_uuid == uuid;
                            });
    if( ( *it )->unit_uuid == _active_index->unit_uuid )
    {
        _active_index.reset();
    }
    _theme_index.erase( it );
}

void ContentIndex::SetActiveUnit( std::shared_ptr< ContentIndexUnit > index )
{
    if( ! index )
    {
        log_info_m << "ContentIndex::SetActiveUnit uuid = \"nullptr\"";
        _active_index.reset();
        return;
    }

    log_info_m << "ContentIndex::SetActiveUnit uuid = \"" << index->unit_uuid << "\"";
    _active_index = index;
}

std::shared_ptr< ContentIndexUnit > ContentIndex::GetActiveIndexUnit()
{
    log_info_m << "ContentIndex::GetActiveIndexUnit";

    return _active_index;
}

void ContentIndex::Clear()
{
    log_info_m << "ContentIndex::Clear";

    _theme_index.clear();
    _active_index.reset();
}

#undef log_error_m
#undef log_info_m
#undef log_debug_m
