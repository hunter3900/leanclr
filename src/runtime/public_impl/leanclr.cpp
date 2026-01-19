
#include "public/leanclr.h"
#include "vm/pinvoke.h"
#include "vm/method.h"
#include "vm/runtime.h"
#include "vm/rt_exception.h"
#include "vm/pinvoke.h"
#include "vm/internal_calls.h"
#include "vm/intrinsics.h"

using namespace leanclr;

struct LeanclrStackObject
{
    uint64_t __value;
};

#ifdef __cplusplus
extern "C"
{
#endif

    void leanclr_get_argument(const LeanclrStackObject* eval_stack, size_t* offset, void* data, size_t data_size)
    {
        std::memcpy(data, eval_stack + *offset, data_size);
        *offset += leanclr_get_stack_object_size_of_byte_size(data_size);
    }

    void leanclr_push_argument(LeanclrStackObject* eval_stack, size_t* offset, const void* data, size_t data_size)
    {
        std::memcpy(eval_stack + *offset, data, data_size);
        *offset += leanclr_get_stack_object_size_of_byte_size(data_size);
    }

    void leanclr_get_return_value(const LeanclrStackObject* ret_buff, void* data, size_t data_size)
    {
        std::memcpy(data, ret_buff, data_size);
    }

    void leanclr_set_return_value(LeanclrStackObject* eval_stack, const void* data, size_t data_size)
    {
        std::memcpy(eval_stack, data, data_size);
    }

    size_t leanclr_get_total_arg_stack_object_size(const LeanclrMethodInfo* method)
    {
        return vm::Method::get_total_arg_stack_object_size((const metadata::RtMethodInfo*)method);
    }

    size_t leanclr_get_return_value_stack_object_size(const LeanclrMethodInfo* method)
    {
        return vm::Method::get_return_value_stack_object_size((const metadata::RtMethodInfo*)method);
    }

    void leanclr_register_pinvoke_func(const char* name, LeanclrMethodPointer func, LeanclrMethodInvoker invoker)
    {
        vm::PInvokes::register_pinvoke(name, (metadata::RtManagedMethodPointer)func, (vm::PInvokeInvoker)invoker);
    }

    void leanclr_register_internal_call_func(const char* name, LeanclrMethodPointer func, LeanclrMethodInvoker invoker)
    {
        vm::InternalCalls::register_internal_call(name, (metadata::RtManagedMethodPointer)func, (vm::InternalCallInvoker)invoker);
    }

    void leanclr_register_newobj_internal_call_func(const char* name, LeanclrMethodInvoker invoker)
    {
        vm::InternalCalls::register_newobj_internal_call(name, (vm::InternalCallInvoker)invoker);
    }

    void leanclr_register_intrinsic_func(const char* name, LeanclrMethodPointer func, LeanclrMethodInvoker invoker)
    {
        vm::Intrinsics::register_intrinsic(name, (metadata::RtManagedMethodPointer)func, (vm::IntrinsicInvoker)invoker);
    }

    void leanclr_register_newobj_intrinsic_func(const char* name, LeanclrMethodInvoker invoker)
    {
        vm::Intrinsics::register_newobj_intrinsic(name, (vm::IntrinsicInvoker)invoker);
    }

    void leanclr_invoke_with_buffer(const LeanclrMethodInfo* method, const LeanclrStackObject* arg_buff, LeanclrStackObject* ret_buff, LeanclrException** out_exception)
    {
        auto ret = vm::Runtime::invoke_stackobject_arguments_with_run_cctor((const metadata::RtMethodInfo*)method,
                                                    (const interp::RtStackObject*)arg_buff,
                                                    (interp::RtStackObject*)ret_buff);
        if (ret.is_ok())
        {
            out_exception = nullptr;
        }
        else
        {
            if (out_exception)
            {
                *(vm::RtException**)out_exception = vm::Exception::raise_error_as_exception(ret.unwrap_err(), nullptr, nullptr);
            }
        }
    }

#ifdef __cplusplus
}
#endif