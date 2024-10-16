#pragma once

#include <string>
namespace utils {
    std::string generate_uuid_v4();

    bool is_IP(const char *str);

    std::string generate_random_string(int length);

    time_t string_to_time_t(const std::string& str);
}