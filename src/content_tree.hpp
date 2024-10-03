#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include <uuid.h>

#include "common.hpp"


class ContentTree
{
public:
    ContentTree() {}
    virtual ~ContentTree() {}

    void Init(uuid & theme_id) {};
    // TODO
    // *to/from json
private:
    std::string _content_theme_name;
    uuid        _content_theme_id;

    std::unordered_map< std::string, ContentTreeUnit > _structure;

};