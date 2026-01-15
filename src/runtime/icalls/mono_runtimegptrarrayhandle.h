#pragma once

#include "icall_base.h"

namespace leanclr::icalls
{

class MonoRuntimeGPtrArrayHandle
{
  public:
    static utils::Span<vm::InternalCallEntry> get_internal_call_entries();

    // Mono.RuntimeGPtrArrayHandle icalls
    static RtResultVoid gptr_array_free(void* arr);
};

} // namespace leanclr::icalls
