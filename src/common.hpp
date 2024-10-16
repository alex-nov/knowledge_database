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

    bool IsEmpty() const
    {
        return uuid.empty() && name.empty();
    }

    bool operator==(const ThemeTuple & other) const
    {
        return uuid == other.uuid && name == other.name;
    }
};

struct ContentUnit
{
    ContentUnit () {}
    ContentUnit (std::string title, std::string theme_id)
        : uuid(utils::generate_uuid_v4())
        , title(title)
        , theme_uuid(theme_id)
        , text("")
        , local_path("")
        , content_url("")
        , timestamp(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())
    {}

    bool isEmpty() const
    {
        return uuid.empty() && title.empty() && theme_uuid.empty();
    }

    bool operator==(const ContentUnit & other) const
    {
        return uuid == other.uuid
            && title == other.title
            && theme_uuid == other.theme_uuid
            && local_path == other.local_path
            && content_url == other.content_url
            && timestamp == other.timestamp;
    }
    void Print() const
    {
        std::cout << "uuid = " << uuid << " | title = " << title;
        std::cout << " | theme_uuid = " << theme_uuid << " | local_path = " << local_path;
        std::cout << " | content_url = " << content_url << " | timestamp = " << timestamp << std::endl;

        std::cout.imbue(std::locale("en_US.UTF-8"));
        std::cout << "unit text: \n" << text << std::endl;
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
