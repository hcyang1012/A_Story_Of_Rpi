SRC_URI_append = "${@bb.utils.contains("MACHINE_FEATURES", "my_gpio_in", " file://001-gpio-in.patch", "", d)}"
FILESEXTRAPATHS_prepend_rpi := "${THISDIR}/files:"

