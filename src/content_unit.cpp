#include "content_unit.hpp"
#include "utils/utils.hpp"


ContentUnit::ContentUnit (std::wstring title, std::wstring theme)
    : _uuid(utils::generate_uuid_v4())
    , _title(title)
    , _content_theme(theme)
    , _text(L"")
    , _local_path("")
    , _content_url("")
    , _timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())
{
}
