#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "common.hpp"


class ContentIndex
{
public:
    ContentIndex() {}
    virtual ~ContentIndex() {}

    bool Init( const std::string & theme_id );

    /** return current active unit uuid */
    std::string LoadThemeFromDB( const std::string & theme );

    void DeleteIndexUnit( const std::string & uuid );
    void AddIndexUnit ( std::shared_ptr< ContentIndexUnit > new_index );
    void SetActiveUnit( std::shared_ptr< ContentIndexUnit > index );
    std::shared_ptr< ContentIndexUnit > GetActiveIndexUnit();

    // TODO
    // *to/from json

    void Clear();

private:
    std::vector< std::shared_ptr< ContentIndexUnit > > _theme_index;
    std::shared_ptr< ContentIndexUnit > _active_index;
};