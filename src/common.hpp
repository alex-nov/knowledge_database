#pragma once

#include <string>
#include <iostream>
#include <chrono>

#include "utils/utils.hpp"

struct ThemeTuple
{
    std::string uuid;
    std::string name;
    // tags
};

struct ContentUnit
{
    ContentUnit () {}
    ContentUnit (std::string title, std::string theme)
        : uuid(utils::generate_uuid_v4())
        , title(title)
        , theme_uuid(theme)
        , text("")
        , local_path("")
        , content_url("")
        , timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())
    {}
    virtual ~ContentUnit()
    {
        std::cout << "end of unit" << std::endl;
    }

    // identify
    std::string uuid;

    // content index titles
    std::string title;
    std::string theme_uuid;

    // fullfill
    std::string text;
    // TODO: image reference
    std::string local_path;
    std::string content_url;

    // creation time
    time_t      timestamp; // added to database

    // TODO:
    // * tags
    // * json from/to conversation
};

struct ContentIndexUnit
{
    int32_t id;
    std::string theme_uuid;
    std::string parent_uuid;
    std::string unit_uuid;
};
