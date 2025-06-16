#include "content_page.hpp"

#include "database_manager.hpp"

#include <logger/logger.h>

#define log_error_m   alog::logger().error   (alog_line_location, "ContentPage")
#define log_info_m    alog::logger().info    (alog_line_location, "ContentPage")
#define log_debug_m   alog::logger().debug   (alog_line_location, "ContentPage")


void ContentPage::LoadUnit( const std::string & uuid )
{
    log_info_m << "ContentPage::LoadUnit uuid = " + uuid;
    _active_unit_id = uuid;
    _content = DatabaseManager::Instance().GetUnit( _active_unit_id );
    // make json
}

void ContentPage::LoadUnit( std::shared_ptr< ContentUnit > unit )
{
    if( !unit )
    {
        return;
    }

    log_info_m << "ContentPage::LoadUnit2 uuid = " + unit->GetUuid();
    _active_unit_id = unit->GetUuid();
    _content = unit;
    // make json
}

std::string ContentPage::ToJson()
{
    log_info_m << "ContentPage::ToJson";
    // TODO :
    return "";
}

#undef log_error_m
#undef log_info_m
#undef log_debug_m
