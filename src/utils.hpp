#include <algorithm>
#include <fstream>
#include <string.h>

/*
 * it looks so majestic with these >w<
 * i like it.
 */
namespace __tc_type {
typedef bool          __bool;
typedef char          __char;
typedef float         __float;
typedef int           __int;
typedef long long int __long__long__int;
typedef std::ofstream __ofstream;
typedef std::ostream  __ostream;
typedef std::string   __string;
typedef unsigned char __unsigned_char;
typedef unsigned int  __unsigned_int;
typedef void          __void;
} // namespace __tc_type

#define __tc_print(__tc_fmt, ...)                                              \
  do {                                                                         \
    __tc_type::__char __buf[1024];                                             \
    snprintf(__buf, sizeof(__buf), __tc_fmt, ##__VA_ARGS__);                   \
    asm volatile("movq $1, %%rax;"                                             \
                 "movq $1, %%rdi;"                                             \
                 "movq %0, %%rsi;"                                             \
                 "movq %1, %%rdx;"                                             \
                 "syscall;"                                                    \
                 :                                                             \
                 : "r"(__buf), "r"(strlen(__buf))                              \
                 : "%rax", "%rdi", "%rsi", "%rdx");                            \
  } while (0)

#define __tc_exit(__tc_num)                                                    \
  do {                                                                         \
    const __tc_type::__int __rawrturn = __tc_num;                              \
    asm volatile("mov $60, %%rax;"                                             \
                 "mov %[__rawrturn], %%rdi;"                                   \
                 "syscall;"                                                    \
                 :                                                             \
                 : [__rawrturn] "i"(__rawrturn)                                \
                 : "%rax", "%rdi");                                            \
  } while (0)

namespace __tc_value {
const __tc_type::__int             __tc_int_max = 2147483647;
const __tc_type::__long__long__int __tc_long_long_int_max = 9223372036854775807;
const __tc_type::__int             __tc_int_min = -2147483648;
const __tc_type::__long__long__int __tc_long_long_int_min =
    -9223372036854775807; /* will output an integer literal is too large warning
                             if correct value defined */

} // namespace __tc_value

namespace __tc_helper {

inline auto
__tc_check_flag(__tc_type::__char  *__tc_flag,
                __tc_type::__string __tc_flag_to_check)
    -> decltype(__tc_type::__bool())
{
  if (strcmp(__tc_flag, __tc_flag_to_check.c_str()) == 0)
    return true;
  else
    return false;
}

inline auto
__tc_clamp_int_max(__tc_type::__int __tc_value) -> decltype(__tc_type::__int())
{
  return std::max(__tc_value::__tc_int_min,
                  std::min(__tc_value, __tc_value::__tc_int_max));
}

inline auto
__tc_clamp(const __tc_type::__int __tc_value_min,
           const __tc_type::__int __tc_value_to_clamp,
           const __tc_type::__int __tc_value_max)
    -> decltype(__tc_type::__int())
{
  if (__tc_value_to_clamp > __tc_value_max)
    return __tc_value_max;
  if (__tc_value_to_clamp < __tc_value_min)
    return __tc_value_min;
  return __tc_value_to_clamp;
}

inline auto
__tc_rand(const __tc_type::__int __tc_min,
          const __tc_type::__int __tc_max) -> decltype(__tc_type::__int())
{
  return rand() % (__tc_max - __tc_min + 1) + __tc_min;
}

template <typename... __tc_args>
auto
__tc_throw_and_exit(const __tc_type::__char *__tc_msg,
                    __tc_args &&...args) -> decltype(__tc_type::__void())
{
  if constexpr (sizeof...(args) == 0)
    __tc_print("%s", __tc_msg);
  else
    __tc_print(__tc_msg, std::forward<__tc_args>(args)...);
  __tc_exit(0);
}

} // namespace __tc_helper
