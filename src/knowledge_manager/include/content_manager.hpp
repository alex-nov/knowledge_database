#pragma once

#include <memory>

#include "content_page.hpp"
#include "content_index.hpp"
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
    std::string CreateUnit( const std::string & title, const std::string & parent_index, const std::string & text = "" );
    std::shared_ptr< ContentIndexUnit > SaveUnit( std::shared_ptr<ContentUnit> new_unit, const std::string & parent_index = "" );
    bool ModifyUnit( const std::string & uuid, const std::string & field, const std::string & value );

    bool DeleteTheme( const std::string & uuid );
    bool DeleteUnit( const std::string & uuid );

    void Run();
private:
    ContentManager(/* args */);
    ContentManager( ContentManager const& ) = delete;
    ContentManager& operator= ( ContentManager const& ) = delete;

    std::string _current_theme_uuid;
    std::shared_ptr< ContentIndex > _content_index;
    std::shared_ptr< ContentPage >  _content_page;
};
