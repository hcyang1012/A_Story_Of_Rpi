SUMMARY = "A sample out-of-tree kernel module"
SECTION = "base"

inherit module

SRC_URI = "file://03_gpio_out.c \
           file://Makefile \
	   file://LICENSE \
	   "
S = "${WORKDIR}"

KERNEL_MODULE_AUTOLOAD = "03_gpio_out"

