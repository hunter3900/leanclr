#pragma once

#include "icall_base.h"

namespace leanclr::icalls
{

class SystemThreadingTimer
{
  public:
    static utils::Span<vm::InternalCallEntry> get_internal_call_entries();

    static RtResult<int64_t> get_time_monotonic();
};

} // namespace leanclr::icalls
