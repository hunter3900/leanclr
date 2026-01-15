#pragma once

#include "icall_base.h"

namespace leanclr::icalls
{

class SystemReflectionMethodBase
{
  public:
    static utils::Span<vm::InternalCallEntry> get_internal_call_entries();

    // Get the currently executing method
    static RtResult<vm::RtReflectionMethod*> get_current_method();
};

} // namespace leanclr::icalls
