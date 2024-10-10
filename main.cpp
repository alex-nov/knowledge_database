#include "src/content_unit.hpp"
#include "src/common.hpp"
#include "src/utils/utils.hpp"

#include <iostream>
#include <string>

int main(int argi, char ** argc)
{
    std::cout << "Hello, it's my knowledge base!" << std::endl;
    // std::string test_unit_text_rus (L"В лидерах рейтинга Индия и России, "
    //         L"причём с огромным отрывом. При этом зарплаты программистов в этих "
    //         L"странах самые низкие. Но за счёт «смешной» величина минималки они "
    //         L"вырываются вперёд. В среднем индийский программист зарабатывает в 14 раз, "
    //         L"а российских почти в 12 раз больше, чем официальный МРОТ в их странах. И, "
    //         L"конечно, при таких раскладах отечественные программисты действительно «в шоколаде».");


    // create ----------

    std::string test_unit_text("Overload 7 is typically called with its second argument, f, obtained directly from "
                               "a new-expression: the locale is responsible for calling the matching delete from its own destructor. ");

    ThemeTuple theme{ utils::generate_uuid_v4(), "test_theme" };
    if(theme.uuid.empty())
    {
        std::cout << "ThemeTuple uuid is not valid!" << std::endl;
        return 1;
    }
    ContentUnit unit("test_unit", theme.uuid);

    unit.SetContent(test_unit_text);

    // print ----------
    // TODO: fmt::print()

    auto [theme_id, title] = unit.GetUnitTitle();
    std::cout << "theme = " << theme_id;
    std::cout << " | unit title = " << title << std::endl;
    std::cout << "unit uuid = " << unit.GetStringUuid() << std::endl;

    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << "unit text: \n" << unit.GetContentText() << std::endl;

    return 0;
}