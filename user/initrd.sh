dd if=/dev/zero of=../initrd.fat bs=8M count=1
LOOP=`losetup -f`
losetup $LOOP ../initrd.fat
mkfs.vfat $LOOP
mount $LOOP /mnt
cp -r vfs/* /mnt
umount /mnt
losetup -d $LOOP
sync
chown $SUDO_USER:$SUDO_USER ../initrd.fat
