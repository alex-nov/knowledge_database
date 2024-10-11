#include "content_manager.hpp"
#include "utils/utils.hpp"


ContentManager::ContentManager(/* args */)
{
}

ContentManager::~ContentManager()
{
}

std::string ContentManager::CreateTheme(const std::string & name)
{
    ThemeTuple new_theme{ utils::generate_uuid_v4(), name };

    auto strong_db = _db.lock();
    if(!strong_db && !strong_db->InsertTheme(new_theme))
    {
        // TODO log error
        return std::string();
    }
    return new_theme.uuid;
}

std::vector<ThemeTuple> ContentManager::GetAllThemes()
{
    auto strong_db = _db.lock();
    if(!strong_db)
    {
        // TODO log error
        return {};
    }
    return strong_db->GetAllThemes();
}

bool ContentManager::LoadTheme(const std::string & uuid)
{
    auto strong_db = _db.lock();
    auto theme = strong_db->GetTheme(uuid);
    if (theme.uuid.empty())
    {
        // TODO log error
        return false;
    }
    _content_page->LoadTheme(uuid);

    return true;
}


void ContentManager::Run()
{
}
