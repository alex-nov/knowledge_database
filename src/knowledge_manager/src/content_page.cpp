#include "content_page.hpp"

#include "database_manager.hpp"

void ContentPage::LoadTheme(const std::string & theme_uuid)
{
    auto index = _index.lock();
#include <logger/logger.h>

    _active_unit_id = index->LoadFromDB(theme_uuid);
    LoadUnit(_active_unit_id);
}
#define log_error_m   alog::logger().error   (alog_line_location, "ContentPage")
#define log_info_m    alog::logger().info    (alog_line_location, "ContentPage")
#define log_debug_m   alog::logger().debug   (alog_line_location, "ContentPage")

void ContentPage::LoadUnit(const std::string & uuid)
{
    _content = DatabaseManager::Instance().GetUnit(uuid);
}

void ContentPage::AddIndexElement(std::shared_ptr<ContentIndexUnit> new_index)
{
    auto index = _index.lock();
    index->AddElement(new_index);
    index->SetActiveElement(new_index);
    log_info_m << "ContentPage::LoadUnit uuid = " + uuid;
}

void ContentPage::SetActiveUnit(const std::string & unit_id)
{
    if(!unit_id.empty() || DatabaseManager::Instance().GetUnit(unit_id))
    {
        _active_unit_id = unit_id;
    }
    log_info_m << "ContentPage::LoadUnit2 uuid = " + unit->GetUuid();
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
