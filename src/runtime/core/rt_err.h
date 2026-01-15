#pragma once

namespace leanclr::core
{
enum class RtErr
{
    None = 0,
    ManagedException,
    ExceedMaxImageCount,
    NotImplemented,
    StackOverflow,
    InvalidCast,
    NullReference,
    ArrayTypeMismatch,
    IndexOutOfRange,
    OutOfMemory,
    Arithmetic,
    FieldAccess,
    MethodAccess,
    ExecutionEngine,
    ArgumentNull,
    DivideByZero,
    Overflow,
    TypeLoad,
    MissingField,
    MissingMethod,
    MissingMember,
    BadImageFormat,
    EntryPointNotFound,
    NotSupported,
    TypeUnloaded,
    ArgumentOutOfRange,
    Argument,
    FileNotFound,
    InvalidOperation,
    ModuleAlreadyLoaded,
};
} // namespace leanclr::core
