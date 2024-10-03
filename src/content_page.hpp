#pragma once

#include "content_unit.hpp"
#include "content_tree.hpp"

#include <memory>

class ContentPage
{
public:

    ContentPage() {}

    void LoadUnit(std::string & uuid);
    std::string ToJson();

private:
    std::shared_ptr<ContentUnit> _content;
    std::weak_ptr<ContentTree>   _tree;

};