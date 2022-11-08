#include "monmgr/Menagerie.hpp"

#include <fmt/core.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

constexpr std::string_view banner =
    "  __  __                 _                               \n"
    " |  \\/  |               | |                              \n"
    " | \\  / | ___  _ __  ___| |_ ___ _ __                    \n"
    " | |\\/| |/ _ \\| '_ \\/ __| __/ _ \\ '__|                   \n"
    " | |  | | (_) | | | \\__ \\ ||  __/ |                      \n"
    " |_|  |_|\\___/|_| |_|___/\\__\\___|_|            _         \n"
    "      |  \\/  |                                (_)        \n"
    "      | \\  / | ___ _ __   __ _  __ _  ___ _ __ _  ___    \n"
    "      | |\\/| |/ _ \\ '_ \\ / _` |/ _` |/ _ \\ '__| |/ _ \\   \n"
    "      | |  | |  __/ | | | (_| | (_| |  __/ |  | |  __/   \n"
    "      |_|  |_|\\___|_| |_|\\__,_|\\__, |\\___|_|  |_|\\___|   \n"
    "                                __/ |                    \n"
    "                               |___/                     \n";

constexpr std::string_view help_message =
    "                                       \n"
    "Available Commands:                  \n\n"
    "  help        - Displays this message  \n"
    "  exit        - Quit the program       \n"
    "  list        - List all monsters      \n"
    "  show <name> - Display monster details\n";

int main (int argc, char **argv)
{
  // display title banner
  fmt::print (
    "{}\n\nType 'help' for more information.\nType 'exit' to close the program.\n\n\n",
    banner
  );

  // main loop
  bool running = true;
  while (running)
  {
    // create command input
    std::string prompt_input;
    fmt::print ("> ");
    std::getline (std::cin, prompt_input);

    // populate menagerie
    monmgr::Menagerie menagerie;

    // parse and execute command
    std::stringstream cmds (prompt_input);
    std::string token;
    while (cmds >> token)
    {
      if (token == "exit")
      {
        running = false;
        break;
      }

      if (token == "help")
      {
        fmt::print("{}\n", help_message);
        break;
      }

      if (token == "list")
      {
        menagerie.list();
        break;
      }

      if (token == "show")
      {
        // consume rest of tokens
        std::stringstream monster_name;
        while (cmds >> token)
        {
          if (monster_name.str().empty())
          {
            monster_name << token;
          }
          else
          {
            monster_name << " " << token;
          }
        }

        // show monster data card
        menagerie.show (monster_name.str());
        break;
      }

      // unknown command error -> try again
      fmt::print (
        "Unknown command '{}'\n{}",
        token,
        help_message
      );
    }
  }

  return EXIT_SUCCESS;
}
