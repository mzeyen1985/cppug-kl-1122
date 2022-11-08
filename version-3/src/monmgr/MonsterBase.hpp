#pragma once

#include <cstdint>
#include <string_view>

namespace monmgr
{

  class MonsterBase
  {
  public:
    virtual ~MonsterBase() = default;

    virtual std::string_view name() const = 0;
    virtual std::uint64_t health() const = 0;
    virtual std::string_view description() const = 0;
  };

}
