#pragma once

#include <string>
#include <chrono>
#include <iostream>

class ContentUnit
{
public:
    ContentUnit(std::string title, std::string theme);

    virtual ~ContentUnit()
    {
        std::cout << "end of unit" << std::endl;
    }

    std::string GetStringUuid() { return this->_uuid; }
    std::string GetContentText() { return this->_text; }
    std::pair<std::string, std::string> GetUnitTitle()
    {
        return std::make_pair(this->_theme_uuid, this->_title);
    }

    bool SetContent(std::string & text,
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
    std::string _uuid;

    // content tree titles
    std::string _title;
    std::string  _theme_uuid;

    // fullfill
    std::string _text;
    // TODO: image reference
    std::string  _local_path;
    std::string  _content_url;

    // creation time
    time_t       _timestamp; // added to database

    // TODO:
    // * tags
    // * json from/to conversation
};