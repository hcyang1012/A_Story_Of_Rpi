SUMMARY = "A sample out-of-tree kernel module"
SECTION = "base"

inherit module

SRC_URI = "file://02_dt_overlay.c \
           file://Makefile \
	   file://LICENSE \
	   "
S = "${WORKDIR}"

KERNEL_MODULE_AUTOLOAD = "02_dt_overlay"

