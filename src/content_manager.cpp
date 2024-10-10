#include "content_manager.hpp"
#include "utils/utils.hpp"


ContentManager::ContentManager(/* args */)
{
}

ContentManager::~ContentManager()
{
}

std::string ContentManager::CreateTheme(std::string name)
{
    ThemeTuple new_theme{ utils::generate_uuid_v4(), name };

    auto strong_db = _db.lock();
    if(!strong_db->InsertTheme(new_theme))
    {
        // TODO log error
        return std::string();
    }
    return new_theme.uuid;
}

void ContentManager::Run()
{
}
