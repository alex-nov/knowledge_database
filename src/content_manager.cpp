#include "content_manager.hpp"
#include "database_manager.hpp"
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

    if(!DatabaseManager::Instance()->InsertTheme(new_theme))
    {
        // TODO log error
        return std::string();
    }
    return new_theme.uuid;
}

std::vector<ThemeTuple> ContentManager::GetAllThemes()
{
    return DatabaseManager::Instance()->GetAllThemes();
}

bool ContentManager::LoadTheme(const std::string & uuid)
{
    auto theme = DatabaseManager::Instance()->GetTheme(uuid);
    if (theme.uuid.empty())
    {
        // TODO log error
        return false;
    }
    _content_page->LoadTheme(uuid);

    return true;
}

int32_t ContentManager::SaveUnit(std::shared_ptr<ContentUnit> new_unit, const std::string & parent_index)
{
    if(!DatabaseManager::Instance()->InsertUnit(new_unit))
    {
        //TODO log error
        return -1;
    }

    auto index = std::make_shared<ContentIndexUnit>();
    index->theme_uuid = new_unit->theme_uuid;
    index->parent_uuid = parent_index;
    index->unit_uuid = new_unit->uuid;
    index->id = DatabaseManager::Instance()->InsertIndexUnit(index);
    if(index->id < 0)
    {
        //TODO log error
        return -1;
    }
    _content_page->AddIndexElement(index);
    _content_page->SetActiveUnit(index->unit_uuid);
    //TODO : update viewable page on new unit

    return index->id;
}

void ContentManager::Run()
{
}
