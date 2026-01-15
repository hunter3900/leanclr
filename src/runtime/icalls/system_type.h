#pragma once

#include "icall_base.h"

namespace leanclr::icalls
{
class SystemType
{
  public:
    static utils::Span<vm::InternalCallEntry> get_internal_call_entries();

    static RtResult<vm::RtReflectionType*> internal_from_handle(size_t handle);
};
} // namespace leanclr::icalls
