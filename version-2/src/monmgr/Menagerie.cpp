#include "monmgr/Menagerie.hpp"

#include "monmgr/LonelyMonster.hpp"

#include <fmt/core.h>

#include <algorithm>

namespace monmgr
{

  Menagerie::Menagerie()
  {
    _monsters.emplace_back (std::make_unique<LonelyMonster>());
  }

  void Menagerie::list() const
  {
    fmt::print ("\n");
    std::for_each (
      _monsters.cbegin(),
      _monsters.cend(),
      [](auto const& monster)
      {
        fmt::print ("- {}\n", monster->name());
      }
    );
    fmt::print ("\n");
  }

  void Menagerie::show (std::string name) const
  {
    // search for monster name
    auto it = std::find_if (
      _monsters.cbegin(),
      _monsters.cend(),
      [&name](auto const& monster)
      {
        return monster->name() == name;
      }
    );

    // check if monster lives in menagerie
    if (it != _monsters.cend())
    {
      fmt::print (
        "\nName: {}\nHealth: {}\nDescription: {}\n\n",
        (*it)->name(),
        (*it)->health(),
        (*it)->description()
      );
    }
    else
    {
      fmt::print (
        "The menagerie has no monster named '{}'.\n",
        name
      );
    }
  }

}
