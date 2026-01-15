#pragma once

#include "icall_base.h"

namespace leanclr::icalls
{

class SystemDiagnosticsDebugger
{
  public:
    static utils::Span<vm::InternalCallEntry> get_internal_call_entries();

    // Check if a debugger is attached
    static RtResult<bool> is_attached_internal();

    // Check if logging is enabled
    static RtResult<bool> is_logging();

    // Log a message to the debugger
    static RtResultVoid log_icall(int32_t level, vm::RtString** category, vm::RtString** message);
};

} // namespace leanclr::icalls
