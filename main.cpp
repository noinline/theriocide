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

#define __tc_return(__tc_num)                                                  \
  do {                                                                         \
    constexpr __tc_type::__int __rawrturn{__tc_num};                           \
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
} // namespace __tc_type

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

auto
main(__tc_type::__void) -> decltype(__tc_type::__int())
{
  __tc_type::__ofstream    __img{};
  const __tc_type::__char *__fname{"image.ppm"};
  __tc_image::__tc_create_img(__img, __fname);

  __tc_return(0);
  __builtin_unreachable();
}
