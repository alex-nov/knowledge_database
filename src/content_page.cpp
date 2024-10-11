#include "content_page.hpp"

void ContentPage::LoadTheme(const std::string & theme_uuid)
{
    auto strong_ptr = _index.lock();

    _active_unit_id = strong_ptr->LoadFromDB(theme_uuid);
    LoadUnit(_active_unit_id);
}

void ContentPage::LoadUnit(const std::string & uuid)
{
    auto database = _db.lock();
    if (!database)
    {
        // TODO: log error;
        return;
    }
    _content = database->LoadUnit(uuid);
}

std::string ContentPage::ToJson()
{
    return "";
}
