#pragma once

#include "content_page.hpp"
#include "database_manager.hpp"


class ContentManager
{
public:
    ContentManager(/* args */);
    virtual ~ContentManager();

    std::string CreateTheme(const std::string & name);
    std::vector<ThemeTuple> GetAllThemes();
    bool LoadTheme(const std::string & uuid);

    void Run();
private:
    std::string _current_theme_uuid;

    std::shared_ptr<ContentPage> _content_page;
    std::weak_ptr<DatabaseManager> _db;
};
