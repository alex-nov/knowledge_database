#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "src/common.hpp"
#include "src/utils/utils.hpp"

#include "src/content_manager.hpp"
#include "src/database_manager.hpp"

#include "logger/logger.h"

void PrintUnit( const ContentUnit & unit )
{
    std::cout /*<< "theme name = " << unit.theme_uuid*/ << " | theme uuid = " << unit.theme_uuid << std::endl;
    std::cout << "unit title = " << unit.title << "  | unit uuid = " << unit.uuid << std::endl;

    //std::cout.imbue( std::locale("ru_UA.utf8") );
    std::cout << "unit text: \n" << unit.text << std::endl;
}

int main(int argi, char ** argc)
{
    alog::logger().start();
    alog::logger().addSaverStdOut(alog::Level::Info);

    log_info << "Logger start 'Demo 01'\n";
    alog::logger().flush();

    // TODO: change std::cout messages on alog

    auto & manager = ContentManager::Instance();
    std::cout << "Hello, it's my knowledge base!" << std::endl;
    // std::wstring test_unit_text_rus (L"В лидерах рейтинга Индия и России, "
    //         L"причём с огромным отрывом. При этом зарплаты программистов в этих "
    //         L"странах самые низкие. Но за счёт «смешной» величина минималки они "
    //         L"вырываются вперёд. В среднем индийский программист зарабатывает в 14 раз, "
    //         L"а российских почти в 12 раз больше, чем официальный МРОТ в их странах. И, "
    //         L"конечно, при таких раскладах отечественные программисты действительно «в шоколаде».");

    // std::string test_unit_text_rus ("В лидерах рейтинга Индия и России, "
    //         "причём с огромным отрывом. При этом зарплаты программистов в этих "
    //         "странах самые низкие. Но за счёт «смешной» величина минималки они ");
    // create ----------

    std::string test_unit_text("Overload 7 is typically called with its second argument, f, obtained directly from \n"
                               "a new-expression: the locale is responsible for calling the matching delete from its own destructor. ");

    ThemeTuple theme{ utils::generate_uuid_v4(), "test_theme" };
    if( theme.uuid.empty() )
    {
        std::cout << "ThemeTuple uuid is not valid!" << std::endl;
        return 1;
    }

    ContentUnit unit( "test_unit", theme.uuid );
    unit.text = test_unit_text;
    // print ----------
    // TODO: fmt::print()

    PrintUnit( unit );
    std::cout << "\n\n";
    unit.Print();

    std::string command_text;
    std::vector< std::string > command_line;
    std::string command;

    try {
        do
        {
            std::cout << "Print command : " << std::endl;
            std::cin >> command_text;
            command_line = utils::split( command_text, " " );

            if( command_line.size() < 0 )
            {
                std::cout << "Wrong command!" << std::endl;
                continue;
            }

            command = command_line.front();

            if( command == "help" )
            {
                //print help
                std::cout << "Command list: \n"
                          << " 1. help [] - show this manual\n"
                          << " 2. print [] - print full tree from current DB in format \"name\" - \"id\" \n"
                          << "    print [unit id] - print full data from unit\n"
                          << " 3. create a) theme [theme name] - create head index for knowledge tree\n"
                          << "           b) unit [unit title] [parent_unit id] - create unit. If parent_unit_id = theme_id - add unit on top level\n"
                          << "              of theme. Text parameter is optional\n"
                          << " 4. modify [unit id] [field name] [field value] - modify unit parameters.\n"
                          << " 5. delete theme/unit [id] - delete unit or full tree by theme" << std::endl;
            }
            else if( command == "print" )
            {
                log_info << "Print command\n";
            }
            else if( command == "create" && command_line.size() > 3 )
            {
                if( command_line.at( 1 ) == "theme" )
                {
                    manager.CreateTheme( command_line.at( 2 ) );
                }
                else if( command_line.at( 1 ) == "unit" && command_line.size() >= 4 )\
                {
                    std::cout << "Enter unit text: " << std::endl;
                    std::string unit_text;
                    std::cin >> unit_text;
                    manager.CreateUnit( command_line.at( 2 ), command_line.at( 3 ), unit_text );
                }
            }
            else if( command == "delete" && command_line.size() >= 3 )
            {
                if( command_line.at( 1 ) == "theme" )
                {
                    manager.DeleteTheme( command_line.at( 2 ) );
                }
                else if( command_line.at( 1 ) == "unit" )
                {
                    manager.DeleteUnit( command_line.at( 2 ) );
                }
            }
            else if( command == "modify" && command_line.size() >= 4 )
            {
                manager.ModifyUnit( command_line.at( 2 ), command_line.at( 3 ), command_line.at( 4 ) );
            }
            else if( command == "exit" )
            {
                break;
            }
            else
            {
                std::cout << "Wrong command!" << std::endl;
            }
        } while( true );
    } catch (...)
    {
        std::cout << "Exception on main menu\n" << std::endl;
    }

    alog::logger().stop();
    return 0;
}