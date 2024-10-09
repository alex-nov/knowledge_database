#pragma once

#include <uuid.h>

namespace utils {
    uuids::uuid generate_uuid_v4();

    bool isIP(const char *str);
}