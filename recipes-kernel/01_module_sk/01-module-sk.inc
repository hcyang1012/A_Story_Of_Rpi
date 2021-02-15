SUMMARY = "A sample out-of-tree kernel module"
SECTION = "base"

inherit module

SRC_URI = "file://01_module_sk.c \
           file://Makefile \
	   file://LICENSE \
	   "
S = "${WORKDIR}"

KERNEL_MODULE_AUTOLOAD = "01_module_sk"
