#include "content_manager.hpp"
#include "database_manager.hpp"
#include "utils/utils.hpp"

#include <logger/logger.h>

#include <unistd.h>

#define log_error_m   alog::logger().error   (alog_line_location, "ContentManager")
#define log_info_m    alog::logger().info    (alog_line_location, "ContentManager")
#define log_debug_m   alog::logger().debug   (alog_line_location, "ContentManager")

ContentManager & ContentManager::Instance()
{
    log_info_m << "ContentManager::Instance";

    static ContentManager instance;
    return instance;
}

ContentManager::ContentManager()
{
    _content_index = std::make_shared< ContentIndex >();
    _content_page  = std::make_shared< ContentPage >();
};

ContentManager::~ContentManager()
{
}

std::string ContentManager::CreateTheme(const std::string & name)
{
    log_info_m << "ContentManager::CreateTheme | name = " + name;

    ThemeTuple new_theme{ utils::generate_uuid_v4(), name };
    if( !DatabaseManager::Instance().InsertTheme(new_theme) )
    {
        log_error_m << "ContentManager::CreateTheme can not create theme " + name;
        return std::string();
    }

    _content_index->Init( new_theme.uuid );
    return new_theme.uuid;
}

std::vector< ThemeTuple > ContentManager::GetAllThemes()
{
    log_info_m << "ContentManager::GetAllThemes";

    return DatabaseManager::Instance().GetAllThemes();
}

bool ContentManager::LoadTheme(const std::string & uuid)
{
    log_info_m << "ContentManager::LoadTheme uuid = " + uuid;

    auto theme = DatabaseManager::Instance().GetTheme(uuid);
    if (theme.uuid.empty())
    {
        log_error_m << "ContentManager::LoadTheme can't load theme " + uuid;
        return false;
    }

    _content_index->Init( uuid );
    auto active_index = _content_index->GetActiveIndexUnit();
    if( active_index )
    {
        _content_page->LoadUnit( active_index->unit_uuid ) ;
    }

    return true;
}

std::string ContentManager::CreateUnit( const std::string & title, const std::string & parent_index, const std::string & text )
{
    log_info_m << "ContentManager::CreateUnit title = " + title + " | parent index = " + parent_index;

    bool is_parent_theme_id = !DatabaseManager::Instance().GetTheme( parent_index ).IsEmpty();
    std::shared_ptr< ContentIndexUnit > new_item_index;

    std::shared_ptr< ContentUnit > unit;
    if( is_parent_theme_id )
    {
        unit = std::make_shared< ContentUnit >( title, parent_index, text );
        new_item_index = SaveUnit( unit, "" );
    }
    else
    {
        auto parent_unit = DatabaseManager::Instance().GetUnit( parent_index );
        unit = std::make_shared< ContentUnit >( title, parent_unit->GetThemeUuid(), text );
        new_item_index = SaveUnit( unit, parent_unit->GetUuid() );
    }
    if ( ! new_item_index )
    {
        log_error_m << "ContentManager::CreateUnit can't create new unit " << title;
        return {};
    }

    _content_index->SetActiveUnit( new_item_index );
    _content_page->LoadUnit( unit );

    return unit->GetUuid();
}

std::shared_ptr< ContentIndexUnit > ContentManager::SaveUnit( std::shared_ptr<ContentUnit> new_unit, const std::string & parent_index )
{
    log_info_m << "ContentManager::SaveUnit unit_id = " + new_unit->GetUuid() + " | parent index = " + parent_index;
    // TODO move InsertIndexUnit into InsertUnit because of Single Responsible principe

    auto index = std::make_shared< ContentIndexUnit >( new_unit->theme_uuid, parent_index, new_unit->uuid );
    if( !DatabaseManager::Instance().InsertUnitWithIndex( new_unit, index ) )
    {
        log_error_m << "ContentManager::SaveUnit can't save unit " + new_unit->title;
        return {};
    }

    return index;
}

bool ContentManager::ModifyUnit( const std::string & uuid, const std::string & field, const std::string & value )
{
    log_info_m << "ContentManager::ModifyUnit unit_id = " + uuid + " | field = " + field + " | value = " + value;

    return DatabaseManager::Instance().ModifyUnit( uuid, field, value );
}

bool ContentManager::DeleteTheme( const std::string & uuid )
{
    log_info_m << "ContentManager::DeleteTheme uuid = " + uuid;

    auto active_index = _content_index->GetActiveIndexUnit();
    if( active_index && active_index->theme_uuid == uuid )
    {
        _content_index->SetActiveUnit( {} );
        _content_page->Clear();
    }

    if( this->_current_theme_uuid == uuid )
    {
        this->_current_theme_uuid.clear();
        _content_index->Clear();
    }

    if( ! DatabaseManager::Instance().DeleteUnitsByTheme( uuid ) ) return false;
    return DatabaseManager::Instance().DeleteFromTable( uuid, database::themes_table_name );
}

bool ContentManager::DeleteUnit( const std::string & uuid )
{
    log_info_m << "ContentManager::DeleteUnit unit_id = " + uuid;

    auto active_index = _content_index->GetActiveIndexUnit();
    if( active_index && active_index->unit_uuid == uuid )
    {
        _content_index->SetActiveUnit( {} );
        _content_page->Clear();
    }
    _content_index->DeleteIndexUnit( uuid );

    return DatabaseManager::Instance().DeleteFromTable( uuid, database::units_table_name );
}

void ContentManager::Run()
{
    //TODO
}

#undef log_error_m
#undef log_info_m
#undef log_debug_m
