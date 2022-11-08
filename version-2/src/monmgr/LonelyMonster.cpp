#include "monmgr/LonelyMonster.hpp"

namespace monmgr
{

  std::string_view LonelyMonster::name() const
  {
    return "Lonely Monster";
  }

  std::uint64_t LonelyMonster::health() const
  {
    return _health;
  }

  std::string_view LonelyMonster::description() const
  {
    return "This monster has been in the menagerie from the very beginning. It seems very lonely.";
  }

}
