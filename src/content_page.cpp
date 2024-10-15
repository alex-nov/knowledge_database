#include "content_page.hpp"

#include "database_manager.hpp"

void ContentPage::LoadTheme(const std::string & theme_uuid)
{
    auto index = _index.lock();

    _active_unit_id = index->LoadFromDB(theme_uuid);
    LoadUnit(_active_unit_id);
}

void ContentPage::LoadUnit(const std::string & uuid)
{
    _content = DatabaseManager::Instance().LoadUnit(uuid);
}

void ContentPage::AddIndexElement(std::shared_ptr<ContentIndexUnit> new_index)
{
    auto index = _index.lock();
    index->AddElement(new_index);
    index->SetActiveElement(new_index);
}

void ContentPage::SetActiveUnit(const std::string & unit_id)
{
    if(!unit_id.empty() || DatabaseManager::Instance().LoadUnit(unit_id))
    {
        _active_unit_id = unit_id;
    }
}

std::string ContentPage::ToJson()
{
    return "";
}
