#pragma once

#include "icall_base.h"

namespace leanclr::icalls
{

class MonoRuntimeMarshal
{
  public:
    static utils::Span<vm::InternalCallEntry> get_internal_call_entries();

    // Free an assembly name structure
    static RtResultVoid free_assembly_name(metadata::RtMonoAssemblyName* aname, bool free_struct);
};

} // namespace leanclr::icalls
