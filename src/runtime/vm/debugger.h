#pragma once

#include "rt_managed_types.h"

namespace leanclr::vm
{

class Debugger
{
  public:
    static void log(int32_t level, RtString* category, RtString* message);
};

} // namespace leanclr::vm
