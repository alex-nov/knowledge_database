#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "common.hpp"
#include "utils/utils.hpp"

#include "content_manager.hpp"
#include "database_manager.hpp"

#include <logger/logger.h>

using std::endl;

void PrintUnit( const ContentUnit & unit )
{
    std::cout << "theme uuid = " << unit.theme_uuid << " | theme uuid = " << unit.theme_uuid << endl;
    std::cout << "unit title = " << unit.title << "  | unit uuid = " << unit.uuid << endl;

    //std::cout.imbue( std::locale("ru_UA.utf8") );
    std::cout << "unit text: \n" << unit.text << endl;
}

int main(int argi, char ** argc)
{
    alog::logger().start();
    alog::logger().addSaverStdOut(alog::Level::Info);

    DatabaseManager::Instance();
    auto & manager = ContentManager::Instance();

    std::string test_unit_text_rus ("В лидерах рейтинга Индия и России, "
             "причём с огромным отрывом. При этом зарплаты программистов в этих "
             "странах самые низкие. Но за счёт «смешной» величина минималки они ");
    std::string test_unit_text("Overload 7 is typically called with its second argument, f, obtained directly from \n"
                               "a new-expression: the locale is responsible for calling the matching delete from its own destructor. ");

    ThemeTuple theme{ utils::generate_uuid_v4(), "test_theme" };
    if( theme.uuid.empty() )
    {
        log_error << "ThemeTuple uuid is not valid!";
        return 1;
    }

    ContentUnit unit( "test_unit", theme.uuid );
    unit.text = test_unit_text;
    unit.Print();

    std::string command_text;
    std::vector< std::string > command_line;
    std::string command;

    try {
        do
        {
            std::cout << "Enter a command : " << endl;
            std::getline(std::cin, command_text);
            command_line = utils::split( command_text, " " );

            if( command_line.size() < 0 )
            {
                log_error << "Empty command!";
                continue;
            }

            command = command_line.front();

            if( command == "help" )
            {
                std::cout << "Command list: \n"
                          << " 1. help [] - show this manual\n"
                          << " 2. print [] - print full tree from current DB in format \"name\" - \"id\" \n"
                          << "    print themes - print all themes"
                          << "    print [unit id] - print full data from unit\n"
                          << " 3. create a) theme [theme name] - create head index for knowledge tree\n"
                          << "           b) unit [unit title] [parent_unit id] - create unit. If parent_unit_id = theme_id - add unit on top level\n"
                          << "              of theme. Text parameter is optional\n"
                          << " 4. modify [unit id] [field name] [field value] - modify unit parameters.\n"
                          << " 5. delete theme/unit [id] - delete unit or full tree by theme\n"
                          << " 6. exit - exit from knowledged database" << endl;
            }
            else if( command == "print" )
            {
                if( command_line.size() >= 2 && command_line.at( 1 ) == "themes" )
                {
                    auto themes = manager.GetAllThemes();
                    for( auto & theme : themes )
                    {
                        std::cout << "name : \"" << theme.name << "\" \t uuid = \"" << theme.uuid <<"\"\n";
                    }
                }
            }
            else if( command == "create" && command_line.size() >= 3 )
            {
                if( command_line.at( 1 ) == "theme" )
                {
                    auto new_theme_id = manager.CreateTheme( command_line.at( 2 ) );
                    log_info << "Created theme uuid = " + new_theme_id;
                }
                else if( command_line.at( 1 ) == "unit" && command_line.size() >= 4 )\
                {
                    std::cout << "Enter unit text: " << endl;
                    std::string unit_text;
                    std::getline(std::cin, unit_text);
                    auto new_unit_id = manager.CreateUnit( command_line.at( 2 ), command_line.at( 3 ), unit_text );
                    log_info << "Created unit uuid = " << new_unit_id;
                }
                else
                {
                    log_error << "Wrong command create \"" << command_text << "\"";
                }
            }
            else if( command == "delete" && command_line.size() >= 3 )
            {
                bool result = false;
                if( command_line.at( 1 ) == "theme" )
                {
                    result = manager.DeleteTheme( command_line.at( 2 ) );
                    log_info << "Delete theme " << command_line.at( 2 ) << ( result ? " successed" : " failed" );
                }
                else if( command_line.at( 1 ) == "unit" )
                {
                    result = manager.DeleteUnit( command_line.at( 2 ) );
                    log_info << "Delete unit " << command_line.at( 2 ) << ( result ? " successed" : " failed" );
                }
                else
                {
                    log_error << "Wrong command: \"" << command_text << "\"";
                }
            }
            else if( command == "modify" && command_line.size() >= 4 )
            {
                auto result = manager.ModifyUnit( command_line.at( 1 ), command_line.at( 2 ), command_line.at( 3 ) );
                log_info << "Modify unit " << command_line.at( 1 ) << ( result ? " successed" : " failed" );
            }
            else if( command == "exit" )
            {
                log_info << "Exit command";
                break;
            }
            else
            {
                log_error << "Wrong command: \"" << command_text << "\"";
            }

            command.clear();
            command_line.clear();
        } while( true );
    } catch (...)
    {
        log_error << "Exception on main menu";
    }

    alog::logger().stop();
    return 0;
}