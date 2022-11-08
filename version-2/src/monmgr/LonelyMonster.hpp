#pragma once

#include "monmgr/MonsterBase.hpp"

#include <cstdint>
#include <string_view>

namespace monmgr
{

  class LonelyMonster : public MonsterBase
  {
  public:
    std::string_view name() const override;
    std::uint64_t health() const override;
    std::string_view description() const override;

  private:
    std::uint64_t _health = 1;
  };

}
