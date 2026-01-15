#pragma once

#include "rt_managed_types.h"

namespace leanclr::vm
{
class GenericMethod
{
  public:
    // Generic method inflation
    static RtResult<const metadata::RtMethodInfo*> get_method(const metadata::RtMethodInfo* methodDef, const metadata::RtGenericInst* classInst,
                                                              const metadata::RtGenericInst* methodInst);

    // Get inflated method from pooled generic method
    static RtResult<const metadata::RtMethodInfo*> get_method_from_pooled_generic_method(const metadata::RtGenericMethod* genericMethod);
};
} // namespace leanclr::vm
