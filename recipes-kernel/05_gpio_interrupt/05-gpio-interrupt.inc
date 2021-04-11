SUMMARY = "A sample out-of-tree kernel module"
SECTION = "base"

inherit module

SRC_URI = "file://04_gpio_in.c \
           file://Makefile \
	   file://LICENSE \
	   "
S = "${WORKDIR}"

KERNEL_MODULE_AUTOLOAD = "04_gpio_in"

