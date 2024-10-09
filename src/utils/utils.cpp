#include "utils.hpp"

#include <arpa/inet.h>

#include "utils.hpp"

namespace utils {

uuids::uuid generate_uuid_v4()
{
    static std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    static uuids::uuid_random_generator gen{generator};

    return gen();
}

bool is_ipv4(const char *host)
{
    struct in_addr addr;
    return 1 == inet_pton(AF_INET, host, &addr);
}

bool is_ipv6(const char *host)
{
    struct in6_addr addr;
    return 1 == inet_pton(AF_INET6, host, &addr);
}

bool isIP(const char *str) { return is_ipv4(str) || is_ipv6(str); }

}
