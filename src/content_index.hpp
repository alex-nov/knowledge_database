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

    bool Init(const std::string & theme_id);

    // return current active unit uuid
    std::string LoadFromDB(const std::string & theme);

    void AddElement(std::shared_ptr<ContentIndexUnit> new_index);
    void SetActiveElement(std::shared_ptr<ContentIndexUnit> new_index)
    {
        _active_index = new_index;
    }

    // TODO
    // *to/from json

private:
    std::vector< std::shared_ptr<ContentIndexUnit> > _theme_index;
    std::shared_ptr<ContentIndexUnit> _active_index;
};