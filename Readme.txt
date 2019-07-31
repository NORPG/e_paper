1. build environment: ubuntu 16.04 (64 bit)

2. "make" to compile
"make clean" to clean

3. sudo ./IT8951_USB /dev/sg2

where the /dev/sg2 is path of IT8951 device: use lsscsi -g to get it
the Linux SCSI generic driver should be installed
