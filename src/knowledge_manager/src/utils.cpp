#include "utils/utils.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <arpa/inet.h>
#include <random>
#include <iomanip>

namespace utils {

std::string generate_uuid_v4()
{
    return boost::uuids::to_string( boost::uuids::random_generator()() );
}

bool is_ipv4( const char *host )
{
    struct in_addr addr;
    return 1 == inet_pton( AF_INET, host, &addr );
}

bool is_ipv6( const char *host )
{
    struct in6_addr addr;
    return 1 == inet_pton( AF_INET6, host, &addr );
}

bool is_IP( const char *str )
{
    return is_ipv4(str) || is_ipv6(str);
}

std::string generate_random_string( int length )
{
    static const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    std::random_device rd;
    std::mt19937 generator( rd() );

    std::string random_string;
    for( int i = 0; i < length; ++i )
    {
        size_t pos = generator() % ( sizeof( CHARACTERS ) - 1 );
        random_string.push_back( CHARACTERS[ pos ] );
    }

    return random_string;
}

time_t string_to_time_t( const std::string& str )
{
    static const std::string& format = "%Y-%b-%d %H:%M:%S+%Z";
    std::tm t = {0};
    t.tm_isdst = 0;
    std::istringstream ss( str );
    ss >> std::get_time( &t, format.c_str() );
    return mktime( &t );
}

std::vector< std::string > split(const std::string & str, const char * delim)
{
    std::vector< std::string > ret;
    size_t last = 0;
    auto index = str.find( delim, last );
    while( index != std::string::npos )
    {
        if( index != last )
        {
            ret.push_back( str.substr( last, index - last ));
        }
        last = index + strlen( delim );
        index = str.find( delim, last );
    }
    if ( !str.size() || str.size() != last )
    {
        ret.push_back( str.substr( last ));
    }
    return ret;
}

}
