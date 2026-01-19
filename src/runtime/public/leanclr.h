#pragma once

#include <stdint.h>
#include <stddef.h>

#ifndef LEANCLR_EXPORT
#ifdef _MSC_VER
#define LEANCLR_EXPORT __declspec(dllexport)
#define LEANCLR_IMPORT __declspec(dllimport)
#else
#define LEANCLR_EXPORT __attribute__((visibility("default")))
#define LEANCLR_IMPORT
#endif
#endif

#ifdef LEANCLR_DLL_EXPORTS
#define LEANCLR_API LEANCLR_EXPORT
#else
#define LEANCLR_API LEANCLR_IMPORT
#endif

struct LeanclrStackObject;
struct LeanclrMethodInfo;
struct LeanclrException;
struct LeanclrTypeSig;

#define LEANCLR_STACK_OBJECT_SIZE 8

#define leanclr_get_stack_object_size_of_byte_size(byte_size) (((byte_size) + LEANCLR_STACK_OBJECT_SIZE - 1) / LEANCLR_STACK_OBJECT_SIZE)

#ifdef __cplusplus
extern "C"
{
#endif

    LEANCLR_API void leanclr_get_argument(const LeanclrStackObject* eval_stack, size_t* offset, void* data, size_t data_size);
    LEANCLR_API void leanclr_push_argument(LeanclrStackObject* eval_stack, size_t* offset, const void* data, size_t data_size);

    LEANCLR_API void leanclr_get_return_value(const LeanclrStackObject* ret_buff, void* data, size_t data_size);
    LEANCLR_API void leanclr_set_return_value(LeanclrStackObject* eval_stack, const void* data, size_t data_size);

    LEANCLR_API size_t leanclr_get_total_arg_stack_object_size(const LeanclrMethodInfo* method);
    LEANCLR_API size_t leanclr_get_return_value_stack_object_size(const LeanclrMethodInfo* method);

    typedef void (*LeanclrMethodPointer)();
    typedef void (*LeanclrMethodInvoker)(LeanclrMethodPointer method_ptr, const LeanclrMethodInfo* method, const LeanclrStackObject* args,
                                         LeanclrStackObject* ret, LeanclrException** exception);

    LEANCLR_API void leanclr_register_pinvoke_func(const char* name, LeanclrMethodPointer func, LeanclrMethodInvoker invoker);
    LEANCLR_API void leanclr_register_internal_call_func(const char* name, LeanclrMethodPointer func, LeanclrMethodInvoker invoker);
    LEANCLR_API void leanclr_register_newobj_internal_call_func(const char* name, LeanclrMethodInvoker invoker);
    LEANCLR_API void leanclr_register_intrinsic_func(const char* name, LeanclrMethodPointer func, LeanclrMethodInvoker invoker);
    LEANCLR_API void leanclr_register_newobj_intrinsic_func(const char* name, LeanclrMethodInvoker invoker);

    LEANCLR_API void leanclr_invoke_with_buffer(const LeanclrMethodInfo* method, const LeanclrStackObject* arg_buff, LeanclrStackObject* ret_buff,
                                                LeanclrException** out_exception);

#define LEANCLR_DECLARING_ALLOC_METHOD_ARGUMENT_BUFFER(arg_buff_name, offset, method)                                                                       \
    LeanclrStackObject* arg_buff_name = (LeanclrStackObject*)alloca(leanclr_get_total_arg_stack_object_size(method) * LEANCLR_STACK_OBJECT_SIZE); \
    size_t offset = 0;

#define LEANCLR_DECLARING_ALLOC_METHOD_RETURN_BUFFER(ret_buff_name, method) \
    LeanclrStackObject* ret_buff_name = (LeanclrStackObject*)alloca(leanclr_get_return_value_stack_object_size(method) * LEANCLR_STACK_OBJECT_SIZE);

#ifdef __cplusplus
}
#endif