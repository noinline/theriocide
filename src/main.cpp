#include <fstream>
#include <string.h>
#include <unistd.h>

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
    const __tc_type::__int __rawrturn{__tc_num};                               \
    asm volatile("mov $60, %%rax;"                                             \
                 "mov %[__rawrturn], %%rdi;"                                   \
                 "syscall;"                                                    \
                 :                                                             \
                 : [__rawrturn] "i"(__rawrturn)                                \
                 : "%rax", "%rdi");                                            \
  } while (0)

/* it looks so majestic with these >w< */
namespace __tc_type {
typedef int           __int;
typedef char          __char;
typedef void          __void;
typedef std::ofstream __ofstream;
typedef std::string   __string;
} // namespace __tc_type

namespace __tc_helper {
template <typename... __tc_args>
auto
__tc_throw_and_exit(const __tc_type::__char *__tc_msg,
                    const __tc_type::__int   __tc_num, __tc_args &&...args)
    -> decltype(__tc_type::__void())
{
  __tc_print(__tc_msg, std::forward<__tc_args>(args)...);
  __tc_exit(__tc_num);
}
} // namespace __tc_helper

namespace __tc_animation {
/* i'll do something later */
}

namespace __tc_image {
auto
__tc_write_img(__tc_type::__ofstream &__tc_img)
{
  const __tc_type::__char   *__type{"P3"};
  constexpr __tc_type::__int __size_x = 250, __size_y = 250, __max_val = 255;
  __tc_img << __type << '\n';
  __tc_img << __size_x << " " << __size_y << '\n';
  __tc_img << __max_val << '\n';
  for (__tc_type::__int y = 0; y < __size_y % __max_val; ++y)
    for (__tc_type::__int x = 0; x < __size_x % __max_val; ++x)
      __tc_img << x << " " << x << " " << x << '\n';
}

auto
__tc_create_img(__tc_type::__ofstream   &__tc_img,
                const __tc_type::__char *__tc_fname)
    -> decltype(__tc_type::__void())
{
  __tc_img.open(__tc_fname);
  if (__tc_img.is_open())
    __tc_write_img(__tc_img);
  __tc_img.close();
  __tc_print("Created ppm image: %s\n", __tc_fname);
}
} // namespace __tc_image

extern "C"
{
auto
__tc_start(__tc_type::__int __tc_argc, __tc_type::__char *__tc_argv[])
    -> decltype(__tc_type::__int())
{
  constexpr __tc_type::__int __max_argc_val{2};
  if (__tc_argc < __max_argc_val || !__tc_argv[1])
    __tc_helper::__tc_throw_and_exit(
        "No valid arguments specified! [__tc_argc < available "
        "arguments(1)]\nUsage: %s <output_file>\n",
        1, __tc_argv[0]);
  else if (__tc_argc > __max_argc_val)
    __tc_helper::__tc_throw_and_exit(
        "Too many arguments! [__tc_argc > available arguments(1)]\nUsage: %s "
        "<output_file>\n",
        1, __tc_argv[0]);

  __tc_type::__string __fname_input{__tc_argv[1]};
  __fname_input += ".ppm";
  __tc_type::__ofstream    __img{};
  const __tc_type::__char *__fname = __fname_input.c_str();
  __tc_image::__tc_create_img(__img, __fname);

  __tc_exit(0);
  __builtin_unreachable();
}
}
extern __typeof(__tc_start) main __attribute__((weak, alias("__tc_start")));
