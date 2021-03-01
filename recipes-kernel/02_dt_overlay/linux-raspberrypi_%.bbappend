SRC_URI_append = "${@bb.utils.contains("MACHINE_FEATURES", "mydevice", " file://001-my-driver-overlay.patch", "", d)}"
FILESEXTRAPATHS_prepend_rpi := "${THISDIR}/files:"

