#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "common.hpp"


class ContentTree
{
public:
    ContentTree() {}
    virtual ~ContentTree() {}

    bool Init(std::string & theme_id) { return true; };
    bool LoadFromDB(std::string &) { return true; }
    // TODO
    // *to/from json

private:
    std::vector< std::shared_ptr<ContentTreeUnit> > _theme_tree;

};