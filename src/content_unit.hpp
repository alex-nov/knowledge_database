#pragma once

#include <string>
#include <chrono>
#include <iostream>

class ContentUnit
{
private:
    // TODO: make text & title std::wstring
    std::wstring _title;
    std::string _text;
    // TODO: image reference
    std::string _local_video_path;
    std::string _content_url;

    time_t _timestamp; // added to database

    // TODO:
    // * reference to ContentTree
    // * tags
    // * reference to global_title


public:
    ContentUnit() {}
    ContentUnit(std::wstring title);

    virtual ~ContentUnit()
    {
        std::cout << "end of unit" << std::endl;
    }
};