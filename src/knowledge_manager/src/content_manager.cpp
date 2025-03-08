#include "content_manager.hpp"
#include "database_manager.hpp"
#include "utils/utils.hpp"

#include <logger/logger.h>

#include <unistd.h>

#define log_error_m   alog::logger().error   (alog_line_location, "Module1")
#define log_info_m    alog::logger().info    (alog_line_location, "Module1")
#define log_debug_m   alog::logger().debug   (alog_line_location, "Module1")


ContentManager & ContentManager::Instance()
{
    log_debug_m << "Func1. Message ";
    static ContentManager instance;
    return instance;
}

ContentManager::~ContentManager()
{
}

std::string ContentManager::CreateTheme(const std::string & name)
{
    ThemeTuple new_theme{ utils::generate_uuid_v4(), name };

    if(!DatabaseManager::Instance().InsertTheme(new_theme))
    {
        // TODO log error
        return std::string();
    }
    return new_theme.uuid;
}

std::vector<ThemeTuple> ContentManager::GetAllThemes()
{
    return DatabaseManager::Instance().GetAllThemes();
}

bool ContentManager::LoadTheme(const std::string & uuid)
{
    auto theme = DatabaseManager::Instance().GetTheme(uuid);
    if (theme.uuid.empty())
    {
        // TODO log error
        return false;
    }
    _content_page->LoadTheme(uuid);

    return true;
}

int32_t ContentManager::CreateUnit( const std::string & title, const std::string & parent_index, const std::string & text )
{
    bool is_parent_theme_id = !DatabaseManager::Instance().GetTheme( parent_index ).IsEmpty();
    int32_t new_item_id = -1;

    if( is_parent_theme_id )
    {
        auto unit = std::make_shared< ContentUnit >( title, parent_index, text );
        new_item_id = SaveUnit( unit, "" );
    }
    else
    {
        auto parent_unit = DatabaseManager::Instance().GetUnit( parent_index );
        auto unit = std::make_shared< ContentUnit >( title, parent_unit->GetThemeUuid(), text );
        new_item_id = SaveUnit( unit, parent_unit->GetUuid() );
    }

    return new_item_id;
}


int32_t ContentManager::SaveUnit( std::shared_ptr<ContentUnit> new_unit, const std::string & parent_index )
{
    if( !DatabaseManager::Instance().InsertUnit(new_unit) )
    {
        //TODO log error
        return -1;
    }

    auto index = std::make_shared<ContentIndexUnit>(new_unit->theme_uuid, parent_index, new_unit->uuid);
    index->id = DatabaseManager::Instance().InsertIndexUnit(index);
    if( index->id < 0 )
    {
        //TODO log error
        return -1;
    }
    _content_page->AddIndexElement( index );
    _content_page->SetActiveUnit( index->unit_uuid );
    //TODO : update viewable page on new unit

    return index->id;
}

bool ContentManager::ModifyUnit( const std::string & uuid, const std::string & field, const std::string & value )
{
    return DatabaseManager::Instance().ModifyUnit( uuid, field, value );
}

void ContentManager::DeleteTheme( const std::string & uuid )
{
    this->_current_theme_uuid.clear();
    this->_content_page.reset();
    DatabaseManager::Instance().DeleteUnitsByTheme( uuid );
    DatabaseManager::Instance().DeleteFromTable( uuid, database::themes_table_name );
}

void ContentManager::DeleteUnit( const std::string & uuid )
{
    DatabaseManager::Instance().DeleteFromTable( uuid, database::units_table_name );
}

void ContentManager::Run()
{
}

#undef log_error_m
#undef log_info_m
#undef log_debug_m
