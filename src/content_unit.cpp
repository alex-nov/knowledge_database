#include "content_unit.hpp"


ContentUnit::ContentUnit (std::wstring title)
    : _title(title)
{
    _timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}