# Custom P/Invoke Methods in LeanCLR

LeanCLR supports custom P/Invoke (Platform Invocation) methods to enable seamless interoperability between managed C# code and native code across platforms. For maximum portability, LeanCLR only supports AOT (Ahead-Of-Time) compiled functions as P/Invoke targets. As the IL-to-AOT toolchain is still under development, manual registration of P/Invoke functions is currently required.

## Example Projects

- [custom-pinvoke-win64](../src/samples/custom-pinvoke-win64)
- [custom-pinvoke-wasm](../src/samples/custom-pinvoke-wasm)

## Steps to Create a Custom P/Invoke Function

There are two main steps:

1. Define the P/Invoke method in C#.
2. Register the native implementation in C++ at runtime.

### 1. Define the P/Invoke Method in `C#`

```csharp
using System.Runtime.InteropServices;

namespace test
{
    public class CustomPInvoke
    {
        [DllImport("CustomNativeLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Add(int a, int b);
    }
}
```

> Note: Since registration is manual, the `DllImport` attribute's DLL name and `CallingConvention` are currently placeholders and do not affect the actual binding.

### 2. Register the Native Implementation in C++

#### a. Include the LeanCLR Header

```cpp
#include "public/leanclr.hpp"
// #include "public/leanclr.h" in c
```

#### b. Implement the Native Function

```cpp
int32_t my_add(int32_t a, int32_t b)
{
    return a + b;
}
```

#### c. Write the Invoker Function

LeanCLR cannot directly invoke arbitrary native signatures. Instead, you must provide an invoker function with a fixed signature:

```cpp
RtResultVoid my_add_invoker(metadata::RtManagedMethodPointer, const metadata::RtMethodInfo*, const interp::RtStackObject* params, interp::RtStackObject* ret)
{
    size_t offset = 0;
    auto a = RuntimeApi::get_argument<int32_t>(params, offset);
    auto b = RuntimeApi::get_argument<int32_t>(params, offset);
    int32_t result = my_add(a, b);
    RuntimeApi::set_return_value<int32_t>(ret, result);
    RET_VOID_OK();
}
```

- The invoker signature must be:
  ```cpp
  RtResultVoid (metadata::RtManagedMethodPointer, const metadata::RtMethodInfo*, const interp::RtStackObject* params, interp::RtStackObject* ret)
  ```
- Use `RuntimeApi::get_argument<T>()` to extract arguments. Note that `offset` is not always the parameter index, as struct parameters may occupy multiple stack slots.
- Use `RuntimeApi::set_return_value()` to set the return value.
- Use `RET_VOID_OK();` to return success.

#### d. Register the P/Invoke Function

Register the invoker after the runtime is initialized:

```cpp
void RegisterCustomPInvokeMethods()
{
    RuntimeApi::register_pinvoke_func(
        "[CoreTests]test.CustomPInvoke::Add(System.Int32,System.Int32)",
        (vm::PInvokeFunction)&my_add,
        my_add_invoker
    );
}

int main()
{
    // ...
    auto ret = vm::Runtime::Initialize();
    if (ret.is_err())
    {
        // ...
        return -1;
    }
    RegisterCustomPInvokeMethods();
    // ...
}
```

- `<signature>`: The function signature string. The full format is `[<dll>]<fullname>::<method name>(T1,T2,...,TN)`. If you are sure there will be no conflicts, you may use the short form `<fullname>::<method name>(T1,T2,...,TN)`.
- `<pinvoke_func>`: The native function implementation.
- `<pinvoke_invoker>`: The invoker function.

## Best Practices

- Always register custom P/Invoke methods after the runtime is successfully initialized.
- Ensure the signature string matches the C# declaration exactly, including namespace, class, method name, and parameter types.
- Use the provided stack access helpers to safely extract arguments and set return values.

## References

- See the sample projects for complete working examples.
- For more details, refer to the LeanCLR documentation and source code.
