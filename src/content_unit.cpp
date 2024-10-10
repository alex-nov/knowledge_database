#include "content_unit.hpp"
#include "utils/utils.hpp"


ContentUnit::ContentUnit (std::string title, std::string theme)
    : _uuid(utils::generate_uuid_v4())
    , _title(title)
    , _theme_uuid(theme)
    , _text("")
    , _local_path("")
    , _content_url("")
    , _timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())
{
}
