#include "utils.hpp"

#include <unistd.h>

namespace __tc_color {
constexpr auto
__tc_color_r(__tc_type::__int __tc_col = 0) -> decltype(__tc_type::__int())
{
  return __tc_col;
}

constexpr auto
__tc_color_g(__tc_type::__int __tc_col = 0) -> decltype(__tc_type::__int())
{
  return __tc_col;
}

constexpr auto
__tc_color_b(__tc_type::__int __tc_col = 0) -> decltype(__tc_type::__int())
{
  return __tc_col;
}
} // namespace __tc_color

namespace __tc_animation {
enum __tc_type_enum
{
  __tc_normal = 0,
  __tc_random = 1
};

inline constexpr __tc_type::__int __tc_anim_count = 1;

auto
__tc_perform(__tc_type::__ofstream               &__tc_img,
             const __tc_animation::__tc_type_enum __tc_anim_type,
             __tc_type::__int x, __tc_type::__int y = 0,
             __tc_type::__int __tc_color_r = 0,
             __tc_type::__int __tc_color_g = 0,
             __tc_type::__int __tc_color_b = 0)

{
  switch (__tc_anim_type) {
  case __tc_normal:
    __tc_img << x * __tc_color::__tc_color_r(__tc_color_r) << " "
             << x * __tc_color::__tc_color_g(__tc_color_g) << " "
             << x * __tc_color::__tc_color_b(__tc_color_b) << '\n';
    break;
  case __tc_random: {
    srand(time(NULL));
    __tc_img << __tc_helper::__tc_clamp(
                    static_cast<__tc_type::__long__long__int>((x * y)) * rand())
             << " "
             << __tc_helper::__tc_clamp(
                    static_cast<__tc_type::__long__long__int>((x * y)) * rand())
             << " "
             << __tc_helper::__tc_clamp(
                    static_cast<__tc_type::__long__long__int>((x * y)) * rand())
             << '\n';
  } break;
  }
}
} // namespace __tc_animation

namespace __tc_image {
auto
__tc_write_img(__tc_type::__ofstream               &__tc_img,
               const __tc_animation::__tc_type_enum __tc_anim_type,
               const __tc_type::__int               __tc_size_x,
               const __tc_type::__int               __tc_size_y,
               const __tc_type::__int               __tc_color_r,
               const __tc_type::__int               __tc_color_g,
               const __tc_type::__int               __tc_color_b)
{
  __tc_print("Writing image data...\n");
  const __tc_type::__char *__type{"P3"};
  __tc_type::__int         __max_val = (__tc_size_x + 1);
  __tc_img << __type << '\n';
  __tc_img << __tc_size_x << " " << __tc_size_y << '\n';
  __tc_img << __max_val << '\n';
  for (__tc_type::__int y = 0; y < __tc_size_y % __max_val; ++y)
    for (__tc_type::__int x = 0; x < __tc_size_x % __max_val; ++x)
      __tc_animation::__tc_perform(__tc_img, __tc_anim_type, x, y, __tc_color_r,
                                   __tc_color_g, __tc_color_b);
}

auto
__tc_create_img(__tc_type::__ofstream               &__tc_img,
                const __tc_type::__char             *__tc_fname,
                const __tc_animation::__tc_type_enum __tc_anim_type,
                const __tc_type::__int               __tc_size_x,
                const __tc_type::__int               __tc_size_y,
                const __tc_type::__int               __tc_color_r,
                const __tc_type::__int               __tc_color_g,
                const __tc_type::__int               __tc_color_b)
    -> decltype(__tc_type::__void())
{
  __tc_img.open(__tc_fname);
  if (__tc_img.is_open())
    __tc_write_img(__tc_img, __tc_anim_type, __tc_size_x, __tc_size_y,
                   __tc_color_r, __tc_color_g, __tc_color_b);
  __tc_img.close();
  __tc_print("Initialized ppm image: %s\n", __tc_fname);
}
} // namespace __tc_image

extern "C"
{
auto
__tc_start(__tc_type::__int __tc_argc, __tc_type::__char *__tc_argv[])
    -> decltype(__tc_type::__int())
{
  __tc_type::__int __max_argc_val{0};
  if (__tc_argc <= 5)
    __max_argc_val = 5;
  else if (__tc_argc > 5)
    __max_argc_val = 8;

  if (__tc_argc < __max_argc_val || !__tc_argv[1])
    __tc_helper::__tc_throw_and_exit(
        "No valid arguments specified! [__tc_argc < available "
        "arguments(4)]\nUsage: %s <output_file> <animation_type> <size_x> "
        "<size_y>\nOptional: <color_red> <color_green> <color_blue>\n",
        __tc_argv[0]);
  else if (__tc_argc > __max_argc_val)
    __tc_helper::__tc_throw_and_exit(
        "Too many arguments! [__tc_argc > available arguments(4)]\nUsage: %s "
        "<output_file> <animation_type> <size_x> <size_y>\nOptional: "
        "<color_red> <color_green> <color_blue>\n",
        __tc_argv[0]);

  __tc_type::__string __fname_input{__tc_argv[1]};
  __fname_input += ".ppm";

  const __tc_type::__int __animation_type = std::stoi(__tc_argv[2]);
  if (__animation_type < 0 ||
      __animation_type > __tc_animation::__tc_anim_count)
    __tc_helper::__tc_throw_and_exit(
        "Invalid <animation_type>! Please specify a correct value (0-%i)",
        __tc_animation::__tc_anim_count);

  const __tc_type::__int __size_x = std::stoi(__tc_argv[3]);
  if (__size_x <= 0)
    __tc_helper::__tc_throw_and_exit(
        "Invalid size x! Please specify a value that is greater than %i.\n", 0);

  const __tc_type::__int __size_y = std::stoi(__tc_argv[4]);
  if (__size_y <= 0)
    __tc_helper::__tc_throw_and_exit(
        "Invalid size y! Please specify a value that is greater than %i.\n", 0);

  __tc_type::__int __color_r = 255;
  __tc_type::__int __color_g = 255;
  __tc_type::__int __color_b = 255;

  if (__max_argc_val == 8) {
    __color_r = std::stoi(__tc_argv[5]);
    if (__color_r > 255 || __color_r < 0)
      __tc_helper::__tc_throw_and_exit(
          "Invalid color red value specified! Please specify a value between 0 "
          "and 255.\n");
    __color_g = std::stoi(__tc_argv[6]);
    if (__color_g > 255 || __color_g < 0)
      __tc_helper::__tc_throw_and_exit(
          "Invalid color green value specified! Please specify a value between "
          "0 and 255.\n");
    __color_b = std::stoi(__tc_argv[7]);
    if (__color_b > 255 || __color_b < 0)
      __tc_helper::__tc_throw_and_exit(
          "Invalid color blue value specified! Please specify a value between "
          "0 and 255.\n");
  }
  __tc_type::__ofstream    __img{};
  const __tc_type::__char *__fname = __fname_input.c_str();
  __tc_image::__tc_create_img(
      __img, __fname, (__tc_animation::__tc_type_enum) __animation_type,
      __size_x, __size_y, __color_r, __color_g, __color_b);

  __tc_helper::__tc_throw_and_exit("Done!\n");
  __builtin_unreachable();
}
}

extern __typeof(__tc_start) main __attribute__((weak, alias("__tc_start")));
