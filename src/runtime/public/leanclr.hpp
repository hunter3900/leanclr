#pragma once

#include "rt_base.h"
#include "vm/rt_managed_types.h"
#include "vm/pinvoke.h"
#include "vm/intrinsics.h"
#include "vm/internal_calls.h"

namespace leanclr
{
class RuntimeApi
{
  public:
    static size_t get_stack_object_size_of_byte_size(size_t byte_size)
    {
        return (byte_size + sizeof(interp::RtStackObject) - 1) / sizeof(interp::RtStackObject);
    }

    template <typename T>
    static constexpr size_t get_stack_object_size_for_type()
    {
        return (sizeof(T) + sizeof(interp::RtStackObject) - 1) / sizeof(interp::RtStackObject);
    }

    template <typename T>
    static void push_argument(interp::RtStackObject* eval_stack, size_t& offset, const T& value)
    {
        *(T*)(eval_stack + offset) = value;
        offset += get_stack_object_size_for_type<T>();
    }

    static void push_argument(interp::RtStackObject* eval_stack, size_t& offset, void* obj, size_t byte_size)
    {
        std::memcpy(eval_stack + offset, obj, byte_size);
        offset += get_stack_object_size_of_byte_size(byte_size);
    }

    template <typename T>
    static void get_argument(const interp::RtStackObject* eval_stack, size_t& offset, T& value)
    {
        value = *(T*)(eval_stack + offset);
        offset += get_stack_object_size_for_type<T>();
    }

    template <typename T>
    static T get_argument(const interp::RtStackObject* eval_stack, size_t& offset)
    {
        size_t old_offset = offset;
        offset += get_stack_object_size_for_type<T>();
        return *(T*)(eval_stack + old_offset);
    }

    static void get_argument(const interp::RtStackObject* eval_stack, size_t& offset, void* obj, size_t byte_size)
    {
        std::memcpy(obj, eval_stack + offset, byte_size);
        offset += get_stack_object_size_of_byte_size(byte_size);
    }

    template <typename T>
    static const T& get_return_value(interp::RtStackObject* ret_buff_name)
    {
        return *(T*)(ret_buff_name);
    }

    static void get_return_value(interp::RtStackObject* ret_buff_name, void* obj, size_t byte_size)
    {
        std::memcpy(obj, ret_buff_name, byte_size);
    }

    template <typename T>
    static void set_return_value(interp::RtStackObject* eval_stack, const T& value)
    {
        *(T*)eval_stack = value;
    }

    static void set_return_value(interp::RtStackObject* eval_stack, void* obj, size_t byte_size)
    {
        std::memcpy(eval_stack, obj, byte_size);
    }

    static size_t get_total_arg_stack_object_size(const metadata::RtMethodInfo* method);
    static size_t get_return_value_stack_object_size(const metadata::RtMethodInfo* method);

    static RtResultVoid invoke_with_buffer(const metadata::RtMethodInfo* method, interp::RtStackObject* arg_buff, interp::RtStackObject* ret_buff);

    static void register_pinvoke_func(const char* name, vm::PInvokeFunction func, vm::PInvokeInvoker invoker);
    static void register_internal_call_func(const char* name, vm::InternalCallFunction func, vm::InternalCallInvoker invoker);
    static void register_newobj_internal_call_func(const char* name, vm::InternalCallInvoker invoker);
    static void register_intrinsic_func(const char* name, vm::IntrinsicFunction func, vm::IntrinsicInvoker invoker);
    static void register_newobj_intrinsic_func(const char* name, vm::IntrinsicInvoker invoker);
};

#define DECLARING_ALLOC_METHOD_ARGUMENT_BUFFER(arg_buff_name, offset, method)                                                                   \
    interp::RtStackObject* arg_buff_name =                                                                                            \
        (interp::RtStackObject*)alloca(leanclr::RuntimeApi::get_total_arg_stack_object_size(method) * sizeof(interp::RtStackObject)); \
    size_t offset = 0;

#define DECLARING_ALLOC_METHOD_RETURN_BUFFER(ret_buff_name, method) \
    interp::RtStackObject* ret_buff_name =                \
        (interp::RtStackObject*)alloca(leanclr::RuntimeApi::get_return_value_stack_object_size(method) * sizeof(interp::RtStackObject));
} // namespace leanclr