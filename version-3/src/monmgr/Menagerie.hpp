#pragma once

#include "monmgr/MonsterBase.hpp"

#include <memory>
#include <string>
#include <vector>

namespace monmgr
{

  class Menagerie
  {
  public:
    Menagerie();

    void list() const;
    void show (std::string name) const;

  private:
    std::vector<std::unique_ptr<MonsterBase>> _monsters;
  };

}
