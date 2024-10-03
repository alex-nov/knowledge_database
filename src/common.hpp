#pragma once

#include <string>

#include <uuid.h>

using uuid = uuids::uuid;

struct ThemeTuple
{
    std::wstring name;
    uuid id;
    // tags
};

struct ContentTreeUnit
{
    uuid theme_uuid;
    uuid unit_uuid;

    uuid parent_id;
};
