#pragma once

#include "icall_base.h"

namespace leanclr::icalls
{
class SystemThreadingInternalThread
{
  public:
    static utils::Span<vm::InternalCallEntry> get_internal_call_entries();

    // Thread cleanup
    static RtResultVoid thread_free_internal(vm::RtInternalThread* this_thread);
};

} // namespace leanclr::icalls
