#pragma once

#include "content_page.hpp"
#include "common.hpp"

class ContentManager
{
public:
    ContentManager(/* args */);
    virtual ~ContentManager();

    std::string CreateTheme(const std::string & name);
    std::vector<ThemeTuple> GetAllThemes();
    bool LoadTheme(const std::string & uuid);

    // return new index_id
    int32_t SaveUnit(std::shared_ptr<ContentUnit> new_unit, const std::string & parent_index = "");

    void Run();
private:
    std::string _current_theme_uuid;

    std::shared_ptr<ContentPage> _content_page;
};
