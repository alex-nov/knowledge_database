#include "utils.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <arpa/inet.h>

namespace utils {

std::string generate_uuid_v4()
{
    return boost::uuids::to_string(boost::uuids::random_generator()());
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
