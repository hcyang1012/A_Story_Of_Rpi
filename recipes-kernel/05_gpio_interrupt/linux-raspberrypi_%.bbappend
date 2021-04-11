SRC_URI_append = "${@bb.utils.contains("MACHINE_FEATURES", "my_gpio_interrupt", " file://001-gpio-interrupt.patch", "", d)}"
FILESEXTRAPATHS_prepend_rpi := "${THISDIR}/files:"

