#pragma once

#include "common.hpp"
#include "content_index.hpp"

#include <memory>

class ContentPage
{
public:

    ContentPage() {}

    // TODO: return current page, app can display. string json?
    void LoadTheme(const std::string & uuid);
    void LoadUnit(const std::string & uuid);
    std::string ToJson();

    void AddIndexElement(std::shared_ptr<ContentIndexUnit> new_index);
    void SetActiveUnit(const std::string & unit_id);

private:
    std::shared_ptr<ContentUnit> _content;
    std::weak_ptr<ContentIndex>  _index;

    std::string _active_unit_id;

};