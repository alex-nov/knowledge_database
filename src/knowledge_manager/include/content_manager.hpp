#pragma once

#include <memory>

#include "content_page.hpp"
#include "common.hpp"

class ContentManager
{
public:
    static ContentManager & Instance();

    virtual ~ContentManager();

    std::string CreateTheme( const std::string & name );
    std::vector<ThemeTuple> GetAllThemes();
    bool LoadTheme( const std::string & uuid );

    // return new index_id
    int32_t CreateUnit( const std::string & title, const std::string & parent_index, const std::string & text = "" );
    int32_t SaveUnit( std::shared_ptr<ContentUnit> new_unit, const std::string & parent_index = "" );
    bool    ModifyUnit( const std::string & uuid, const std::string & field, const std::string & value );

    void DeleteTheme( const std::string & uuid );
    void DeleteUnit( const std::string & uuid );

    void Run();
private:
    ContentManager(/* args */) {};
    ContentManager( ContentManager const& );
    ContentManager& operator= ( ContentManager const& );

    std::string _current_theme_uuid;
    std::shared_ptr<ContentPage> _content_page;
};
