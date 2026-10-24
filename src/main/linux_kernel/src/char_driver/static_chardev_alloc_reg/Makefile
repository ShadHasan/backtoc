obj-m += static_alloc_device_reg.o
KVERSION = $(shell uname -r)

# ─── ADD THESE TWO LINES ───
ccflags-y += -fno-pic -fno-pie
ldflags-y += -no-pie
# ───────────────────────────

all:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean


