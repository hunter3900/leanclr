#include "architecture.h"

#include "../vm/rt_string.h"

namespace leanclr::os
{
vm::RtString* Architecture::get_architecture_name()
{
    return vm::String::get_empty_string();
}

vm::RtString* Architecture::get_os_name()
{
    return vm::String::get_empty_string();
}
} // namespace leanclr::os
