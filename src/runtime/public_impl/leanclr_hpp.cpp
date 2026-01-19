
#include "public/leanclr.hpp"

#include "vm/pinvoke.h"
#include "vm/method.h"
#include "vm/runtime.h"
#include "vm/rt_exception.h"
#include "vm/pinvoke.h"
#include "vm/internal_calls.h"
#include "vm/intrinsics.h"

namespace leanclr
{
    size_t RuntimeApi::get_total_arg_stack_object_size(const metadata::RtMethodInfo* method)
    {
        return vm::Method::get_total_arg_stack_object_size(method);
    }

    size_t RuntimeApi::get_return_value_stack_object_size(const metadata::RtMethodInfo* method)
    {
        return vm::Method::get_return_value_stack_object_size(method);
    }

    RtResultVoid RuntimeApi::invoke_with_buffer(const metadata::RtMethodInfo* method, interp::RtStackObject* arg_buff, interp::RtStackObject* ret_buff)
    {
        return vm::Runtime::invoke_stackobject_arguments_with_run_cctor(method, arg_buff, ret_buff);
    }

    void RuntimeApi::register_pinvoke_func(const char* name, vm::PInvokeFunction func, vm::PInvokeInvoker invoker)
    {
        vm::PInvokes::register_pinvoke(name, func, invoker);
    }

    void RuntimeApi::register_internal_call_func(const char* name, vm::InternalCallFunction func, vm::InternalCallInvoker invoker)
    {
        vm::InternalCalls::register_internal_call(name, func, invoker);
    }

    void RuntimeApi::register_newobj_internal_call_func(const char* name, vm::InternalCallInvoker invoker)
    {
        vm::InternalCalls::register_newobj_internal_call(name, invoker);
    }

    void RuntimeApi::register_intrinsic_func(const char* name, vm::IntrinsicFunction func, vm::IntrinsicInvoker invoker)
    {
        vm::Intrinsics::register_intrinsic(name, func, invoker);
    }

    void RuntimeApi::register_newobj_intrinsic_func(const char* name, vm::IntrinsicInvoker invoker)
    {
        vm::Intrinsics::register_newobj_intrinsic(name, invoker);
    }
}