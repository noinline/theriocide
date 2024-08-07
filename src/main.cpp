#include "utils.hpp"

#include <getopt.h>
#include <iostream>
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

namespace __tc_effect {
enum __tc_type_enum
{
  __tc_normal = 0,
  __tc_normal_gradient = 1,
  __tc_random = 2,
  __tc_random_gradient = 3
};

inline constexpr __tc_type::__int __tc_effect_count = 3;

auto
__tc_perform(__tc_type::__ostream             &__tc_img,
             const __tc_effect::__tc_type_enum __tc_effect_type,
             __tc_type::__int x = 0, __tc_type::__int y = 0,
             __tc_type::__int __tc_color_r = 0,
             __tc_type::__int __tc_color_g = 0,
             __tc_type::__int __tc_color_b = 0,
             __tc_type::__int __tc_max_value = 0,
             __tc_type::__int __tc_size_x = 0, __tc_type::__int __tc_size_y = 0)

{
  switch (__tc_effect_type) {
  case __tc_normal:
    __tc_img << __tc_helper::__tc_clamp(0, __tc_max_value,
                                        __tc_color::__tc_color_r(__tc_color_r))
             << " "
             << __tc_helper::__tc_clamp(0, __tc_max_value,
                                        __tc_color::__tc_color_g(__tc_color_g))
             << " "
             << __tc_helper::__tc_clamp(0, __tc_max_value,
                                        __tc_color::__tc_color_b(__tc_color_b))
             << std::endl;
    break;
  case __tc_normal_gradient:
    __tc_img
        << __tc_helper::__tc_clamp(0, __tc_max_value,
                                   ((__tc_type::__float) x / __tc_size_x) *
                                       __tc_color::__tc_color_r(__tc_color_r))
        << " "
        << __tc_helper::__tc_clamp(0, __tc_max_value,
                                   ((__tc_type::__float) x / __tc_size_x) *
                                       __tc_color::__tc_color_g(__tc_color_g))
        << " "
        << __tc_helper::__tc_clamp(0, __tc_max_value,
                                   ((__tc_type::__float) x / __tc_size_x) *
                                       __tc_color::__tc_color_b(__tc_color_b))
        << std::endl;
    break;
  case __tc_random: {
    srand(time(NULL));
    __tc_img << __tc_helper::__tc_clamp(
                    0, __tc_max_value,
                    __tc_color::__tc_color_r(
                        __tc_helper::__tc_rand(0, __tc_max_value)))
             << " "
             << __tc_helper::__tc_clamp(
                    0, __tc_max_value,
                    __tc_color::__tc_color_g(
                        __tc_helper::__tc_rand(0, __tc_max_value)))
             << " "
             << __tc_helper::__tc_clamp(
                    0, __tc_max_value,
                    __tc_color::__tc_color_b(
                        __tc_helper::__tc_rand(0, __tc_max_value)))
             << std::endl;
  } break;
  case __tc_random_gradient: {
    srand(time(NULL));

    __tc_img << __tc_helper::__tc_clamp(
                    0, __tc_max_value,
                    ((__tc_type::__float) x / __tc_size_x) *
                        __tc_helper::__tc_rand(0, __tc_max_value))
             << " "
             << __tc_helper::__tc_clamp(
                    0, __tc_max_value,
                    ((__tc_type::__float) x / __tc_size_x) *
                        __tc_helper::__tc_rand(0, __tc_max_value))
             << " "
             << __tc_helper::__tc_clamp(
                    0, __tc_max_value,
                    ((__tc_type::__float) x / __tc_size_x) *
                        __tc_helper::__tc_rand(0, __tc_max_value))
             << std::endl;
  } break;
  }
}
} // namespace __tc_effect

namespace __tc_image {
auto
__tc_write_img(__tc_type::__ostream             &__tc_img,
               const __tc_effect::__tc_type_enum __tc_effect_type,
               const __tc_type::__int            __tc_size_x,
               const __tc_type::__int            __tc_size_y,
               const __tc_type::__int            __tc_color_r,
               const __tc_type::__int            __tc_color_g,
               const __tc_type::__int            __tc_color_b)
{
  __tc_print("Writing image data...\n");
  const __tc_type::__char *__type{"P3"};
  __tc_type::__int         __max_val = (__tc_size_x + 1);
  __tc_type::__int         __max_rgb_val{255};
  __tc_img << __type << '\n';
  __tc_img << __tc_size_x << " " << __tc_size_y << '\n';
  __tc_img << __max_rgb_val << '\n';
  for (__tc_type::__int y = 0; y < __tc_size_y % __max_val; ++y)
    for (__tc_type::__int x = 0; x < __tc_size_x % __max_val; ++x)
      __tc_effect::__tc_perform(__tc_img, __tc_effect_type, x, y, __tc_color_r,
                                __tc_color_g, __tc_color_b, __max_rgb_val,
                                __tc_size_x, __tc_size_y);
}

auto
__tc_create_img(__tc_type::__ostream             &__tc_img,
                const __tc_type::__char          *__tc_fname,
                const __tc_effect::__tc_type_enum __tc_effect_type,
                const __tc_type::__int            __tc_size_x,
                const __tc_type::__int            __tc_size_y,
                const __tc_type::__int            __tc_color_r,
                const __tc_type::__int            __tc_color_g,
                const __tc_type::__int            __tc_color_b)
    -> decltype(__tc_type::__void())
{
  if (__tc_img.good())
    __tc_write_img(__tc_img, __tc_effect_type, __tc_size_x, __tc_size_y,
                   __tc_color_r, __tc_color_g, __tc_color_b);
  __tc_print("Initialized ppm image: %s\n", __tc_fname);
}
} // namespace __tc_image

extern "C"
{
auto
__tc_start(__tc_type::__int __tc_argc, __tc_type::__char *__tc_argv[])
    -> decltype(__tc_type::__int())
{
  __tc_type::__int __max_argc_val{5};

  static struct option __long_options[] = {
      {"color", no_argument, 0, 'c'},
      {"help",  no_argument, 0, 'h'},
      {0,       0,           0, 0  }
  };
  __tc_type::__int __option_index = 0;

  __tc_type::__int __c =
      getopt_long(__tc_argc, __tc_argv, "ch", __long_options, &__option_index);

  __tc_type::__char *__flag = (__tc_type::__char *) "";

  switch (__c) {
  case 'c': __flag = (__tc_type::__char *) "--color"; break;
  case 'h':
    __flag = (__tc_type::__char *) "--help";
    __tc_helper::__tc_throw_and_exit(
        "Usage:\n	%s "
        "<output_file> <effect_type> <size_x> "
        "<size_y>\n\n"
        "Effect types:\n	<0> - normal\n	<1> - normal gradient\n	<2> - "
        "random\n	<3> - random gradient\n\n"
        "Optional flags:\n	"
        "'--color' - colorize image(lol)\n	"
        "'--help' - prints this message\n\n"
        "Examples:\n	%s test 0 500 500\n	%s test 1 500 "
        "500\n	%s test 0 500 "
        "500 "
        "--color 255 255 255\n	"
        "%s test 1 500 500 --color 255 255 255\n",
        __tc_argv[0], __tc_argv[0], __tc_argv[0], __tc_argv[0], __tc_argv[0],
        __tc_argv[0], __tc_argv[0]);
    break;

  case '?':
    /* getopt_long already printed an error message. */
    break;
  }

  if (strcmp(__flag, "--color") == 0)
    __max_argc_val = 9;
  else
    __max_argc_val = 5;

  if (__tc_argc < __max_argc_val || !__tc_argv[1])
    __tc_helper::__tc_throw_and_exit(
        "No valid arguments specified! [__tc_argc < available "
        "arguments(%i)].\nConsider using '--help' flag for more information.\n",
        __max_argc_val);
  else if (__tc_argc > __max_argc_val)
    __tc_helper::__tc_throw_and_exit(
        "Too many arguments! [__tc_argc > available arguments(%i)].\nConsider "
        "using '--help' flag for more information.\n",
        __max_argc_val);

  __tc_type::__string __fname_input{__tc_argv[1]};
  __fname_input += ".ppm";

  const __tc_type::__int __effect_type = std::stoi(__tc_argv[2]);
  if (__effect_type < 0 || __effect_type > __tc_effect::__tc_effect_count)
    __tc_helper::__tc_throw_and_exit(
        "Invalid <effect_type>! Please specify a correct value (0-%i)",
        __tc_effect::__tc_effect_count);

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

  /* if --color flag is present and effect type not equals random, colorize
   * image. */
  if (strcmp(__flag, "--color") == 0 &&
      (__effect_type != 2 && __effect_type != 3))
  {
    __color_r = std::stoi(__tc_argv[6]);
    if (__color_r > 255 || __color_r < 0)
      __tc_helper::__tc_throw_and_exit(
          "Invalid color red value specified! Please specify a value between 0 "
          "and 255.\n");
    __color_g = std::stoi(__tc_argv[7]);
    if (__color_g > 255 || __color_g < 0)
      __tc_helper::__tc_throw_and_exit(
          "Invalid color green value specified! Please specify a value between "
          "0 and 255.\n");
    __color_b = std::stoi(__tc_argv[8]);
    if (__color_b > 255 || __color_b < 0)
      __tc_helper::__tc_throw_and_exit(
          "Invalid color blue value specified! Please specify a value between "
          "0 and 255.\n");
  } else if (strcmp(__flag, "--color") == 0 &&
             (__effect_type == 2 | __effect_type == 3))
    __tc_helper::__tc_throw_and_exit(
        "Invalid flag '%s' specified along with <effect_type> (%i).\n", __flag,
        __effect_type);

  __tc_type::__ofstream    __img{};
  const __tc_type::__char *__fname = __fname_input.c_str();
  __img.open(__fname);
  __tc_image::__tc_create_img(
      __img, __fname, (__tc_effect::__tc_type_enum) __effect_type, __size_x,
      __size_y, __color_r, __color_g, __color_b);
  __img.close();

  __tc_helper::__tc_throw_and_exit("Done!\n");
  __builtin_unreachable();
}
}

extern __typeof(__tc_start) main __attribute__((weak, alias("__tc_start")));
