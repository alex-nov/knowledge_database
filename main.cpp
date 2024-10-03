#include "src/content_unit.hpp"

#include <iostream>
#include <string>

int main(int argi, char ** argc)
{
    std::cout << "Hello, it's my knowledge base!" << std::endl;
    // std::wstring test_unit_text_rus (L"В лидерах рейтинга Индия и России, "
    //         L"причём с огромным отрывом. При этом зарплаты программистов в этих "
    //         L"странах самые низкие. Но за счёт «смешной» величина минималки они "
    //         L"вырываются вперёд. В среднем индийский программист зарабатывает в 14 раз, "
    //         L"а российских почти в 12 раз больше, чем официальный МРОТ в их странах. И, "
    //         L"конечно, при таких раскладах отечественные программисты действительно «в шоколаде».");


    std::wstring test_unit_text(L"Overload 7 is typically called with its second argument, f, obtained directly from "
                                L"a new-expression: the locale is responsible for calling the matching delete from its own destructor. ");

    ContentUnit unit(L"test_unit", L"test_theme");

    unit.SetContent(test_unit_text);

    auto [theme, title] = unit.GetUnitTitle();
    std::wcout << L"theme = " << theme <<L" | unit title = " << title << std::endl;
    std::cout << "unit uuid = " << unit.GetStringUuid() << std::endl;

    std::wcout.imbue(std::locale("en_US.UTF-8"));
    std::wcout << "unit text: \n" << unit.GetContentText() << std::endl;

    return 0;
}