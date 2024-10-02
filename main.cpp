#include "src/content_unit.hpp"

#include <iostream>
#include <string>

int main(int argi, char ** argc)
{
    std::cout << "Hello, it's my knowledge base!" << std::endl;

    ContentUnit unit(L"test_unit");

    return 0;
}