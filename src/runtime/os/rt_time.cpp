#include "rt_time.h"

namespace leanclr::os
{
int32_t Time::get_tick_count()
{
    assert(false && "Time::get_tick_count not implemented for this platform");
    return 0;
}

int64_t Time::get_current_time_millis()
{
    assert(false && "Time::get_current_time_millis not implemented for this platform");
    return 0;
}

int64_t Time::get_current_time_nanos()
{
    assert(false && "Time::get_current_time_nanos not implemented for this platform");
    return 0;
}

int64_t Time::get_ticks_100nanos()
{
    assert(false && "Time::get_ticks_100nanos not implemented for this platform");
    return 0;
}

int64_t Time::get_system_time_as_file_time()
{
    assert(false && "Time::get_system_time_as_file_time not implemented for this platform");
    return 0;
}
} // namespace leanclr::os
