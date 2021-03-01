SRC_URI_append = "${@bb.utils.contains("MACHINE_FEATURES", "gpio_out", " file://001-gpio-out.patch", "", d)}"
FILESEXTRAPATHS_prepend_rpi := "${THISDIR}/files:"

