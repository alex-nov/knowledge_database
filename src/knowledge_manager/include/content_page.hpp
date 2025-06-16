#pragma once

#include "common.hpp"
#include "content_index.hpp"

#include <memory>

class ContentPage
{
public:
    // TODO: return current page, app can display. string json?

    void LoadUnit( const std::string & uuid );
    void LoadUnit( std::shared_ptr< ContentUnit > unit );
    std::string ToJson();

    void Clear()
    {
        _active_unit_id.clear();
        _content.reset();
    }

private:
    std::shared_ptr< ContentUnit > _content;

    std::string _active_unit_id;

};