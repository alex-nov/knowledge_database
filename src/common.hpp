#pragma once

#include <string>

struct ThemeTuple
{
    std::string uuid;
    std::string name;
    // tags
};

struct ContentTreeUnit
{
    std::string theme_uuid;
    std::string parent_uuid;
    std::string unit_uuid;
};
