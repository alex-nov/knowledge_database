
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

}
