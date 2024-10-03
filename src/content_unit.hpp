#pragma once

#include <string>
#include <chrono>
#include <iostream>

#include <uuid.h>

class ContentUnit
{
public:
    ContentUnit(std::wstring title, std::wstring theme);

    virtual ~ContentUnit()
    {
        std::cout << "end of unit" << std::endl;
    }

    std::string GetStringUuid() { return uuids::to_string(this->_uuid); }
    std::wstring GetContentText() { return this->_text; }
    std::pair<std::wstring, std::wstring> GetUnitTitle()
    {
        return std::make_pair(this->_content_theme, this->_title);
    }

    bool SetContent(std::wstring & text,
                    std::string local_path = "",
                    std::string url = "")
    {
        _text = text;
        if (!local_path.empty())
        {
            _local_path = local_path;
        }
        if (!url.empty())
        {
            _content_url = url;
        }
        return true;
    }

private:
    // identify
    uuids::uuid _uuid;

    // content tree titles
    std::wstring _title;
    std::wstring _content_theme;

    // fullfill
    std::wstring _text;
    // TODO: image reference
    std::string _local_path;
    std::string _content_url;

    // creation time
    time_t _timestamp; // added to database

    // TODO:
    // * tags
    // * json from/to conversation
};