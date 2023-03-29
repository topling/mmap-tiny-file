# must use root
mkfs.ext4 -b 4096 -I 256 -O inline_data testfs.img 256m
mkdir mount
mount testfs.img mount
dd bs=75 count=1 if=/dev/zero of=mount/testfile
