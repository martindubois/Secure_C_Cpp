
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# Course         07 - Driver development
# Video          03 - Read, Write and IoCtl
# File           Driver/Makefile

obj-m += DriverA.o

DriverA-objs := Device.o Driver.o

# ===== Targets =============================================================

module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
