#include <fmt/core.h>

#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

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

class MonsterBase
{
public:
  virtual ~MonsterBase() = default;

  virtual std::string_view name() const = 0;
  virtual std::uint64_t health() const = 0;
  virtual std::string_view description() const = 0;
};

class LonelyMonster : public MonsterBase
{
public:
  std::string_view name() const override
  {
    return "Lonely Monster";
  }

  std::uint64_t health() const override
  {
    return _health;
  }

  std::string_view description() const override
  {
    return "This monster has been in the menagerie from the very beginning. It seems very lonely.";
  }

private:
  std::uint64_t _health = 1;
};

int main(int argc, char **argv)
{
  // display title banner
  fmt::print(
      "{}\n\nType 'help' for more information.\nType 'exit' to close the program.\n\n\n",
      banner);

  // populate menagerie
  std::vector<std::unique_ptr<MonsterBase>> menagerie;
  menagerie.emplace_back(std::make_unique<LonelyMonster>());

  // populate commands

  // main loop
  bool running = true;
  while (running)
  {
    // create command input
    std::string prompt_input;
    fmt::print("> ");
    std::getline(std::cin, prompt_input);

    // parse and execute command
    std::stringstream cmds(prompt_input);
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
        fmt::print("\n");
        for (auto &monster : menagerie)
        {
          fmt::print("- {}\n", monster->name());
        }
        fmt::print("\n");
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

        // search for monster name
        auto it = std::find_if(menagerie.begin(), menagerie.end(),
                               [&monster_name](std::unique_ptr<MonsterBase> &mon)
                               {
                                 return mon->name() == monster_name.str();
                               });

        // check if monster lives in menagerie
        if (it == menagerie.end())
        {
          fmt::print("The menagerie has no monster named '{}'.\n", monster_name.str());
          break;
        }

        // print monster data card
        fmt::print(
            "\nName: {}\nHealth: {}\nDescription: {}\n\n",
            (*it)->name(),
            (*it)->health(),
            (*it)->description());

        break;
      }

      // unknown command error -> try again
      fmt::print(
          "Unknown command '{}'\n{}",
          token,
          help_message);
    }
  }

  return EXIT_SUCCESS;
}
