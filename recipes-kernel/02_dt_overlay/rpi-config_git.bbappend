
do_deploy_append(){
    # My device support
    if [ "${ENABLE_MY_DEVICE}" = "1" ]; then
        echo "# Enable My device" >>$CONFIG
        echo "dtoverlay=my-driver" >>$CONFIG
    fi

}

