#!/bin/sh

echo ""
echo "########## UMX Boot Service START ##########"
echo ""


insmod /lib/modules/$(uname -r)/kernel/fs/configfs/configfs.ko
insmod /lib/modules/$(uname -r)/kernel/drivers/usb/gadget/libcomposite.ko
insmod /lib/modules/$(uname -r)/kernel/drivers/usb/gadget/g_hid.ko


export DISPLAY=":0.0"
export LD_LIBRARY_PATH="/usr/local/lib"

/usr/local/bin/Neuro/Bin/Linux_armhf/Activation/run_pgd.sh start &
/etc/init.d/umx-boot.sh &
/usr/local/bin/umxDiscovery &
/home/root/rzagent &

echo ""
echo "########## UMX Boot Service Finish ##########"
echo ""

