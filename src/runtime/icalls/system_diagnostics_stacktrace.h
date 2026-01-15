#pragma once

#include "icall_base.h"

namespace leanclr::icalls
{

class SystemDiagnosticsStackTrace
{
  public:
    static utils::Span<vm::InternalCallEntry> get_internal_call_entries();

    // Get stack trace from exception
    static RtResult<vm::RtArray*> get_trace(vm::RtException* ex, int32_t skip_frames, bool need_file_info);
};

} // namespace leanclr::icalls
