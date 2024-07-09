#define cimg_display 0
#include "../utils.hpp"

#include <CImg.h>
#include <getopt.h>

extern "C"
{
auto
__tc_start(__tc_type::__int __tc_argc, __tc_type::__char *__tc_argv[])
    -> decltype(__tc_type::__int())
{
  __tc_type::__int __max_argc_val{3};

  static struct option __long_options[] = {
      {"help", no_argument, 0, 'h'},
      {0,      0,           0, 0  }
  };
  __tc_type::__int __option_index = 0;

  __tc_type::__int __c =
      getopt_long(__tc_argc, __tc_argv, "h", __long_options, &__option_index);

  __tc_type::__char *__flag = (__tc_type::__char *) "";
  switch (__c) {
  case 'h':
    __flag = (__tc_type::__char *) "--help";
    __tc_helper::__tc_throw_and_exit("Important note:\nImage names should be "
                                     "specified without file extension.\n\n"
                                     "Usage:\n"
                                     "%s <input_image> <output_image>\n\n"
                                     "Optional flags:\n"
                                     "'--help' - prints this message\n\n"
                                     "Example:\n%s input_image output_image\n",
                                     __tc_argv[0], __tc_argv[0]);
    break;

  case '?':
    /* getopt_long already printed an error message. */
    break;
  }

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

  __tc_type::__string __input_image{__tc_argv[1]};
  __input_image += ".ppm";
  __tc_print("Input image: %s\n", __input_image.c_str());

  const cimg_library::CImg<__tc_type::__unsigned_char> __image(
      __input_image.c_str());

  __tc_type::__string __output_image{__tc_argv[2]};
  __output_image += ".jpg";

  __tc_print("Output image: %s\n", __output_image.c_str());

  __image.save(__output_image.c_str());
  __tc_helper::__tc_throw_and_exit("Succesfully converted %s to %s.\nDone!\n",
                                   __input_image.c_str(),
                                   __output_image.c_str());
  __builtin_unreachable();
}
}

extern __typeof(__tc_start) main __attribute__((weak, alias("__tc_start")));
