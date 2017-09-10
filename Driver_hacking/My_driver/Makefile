# Makefile za kernel module.
# Več info: https://www.kernel.org/doc/Documentation/kbuild/makefiles.txt

# Za compilat kernel module, morš imet kernel (header/src?) lokacijo
# Za pogledat kateri kernel uporabljaš trenutno: uname -r
# Kernel headerji so v /usr/src/
KDIR = /usr/src/linux-headers-4.4.0-78-generic

# obj-m pomeni da hočeš nrdit Kernel MODULE iz xxx.o (xxx.o se nrdi iz xxx.c)
# obj-y pomeni kernel BUILT-IN
# ponavadi se za -m ali -y uporablja spremenljivka $(CONFIG_IMEPROGRAMA)
obj-m += 01_nothing.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order .[^.]*


# Module skompajlaš z: make
# Potem ga vstavi v kernel: sudo insmod 01_nothing.ko
# Poglej če je vstavljen: lsmod
# Odstrani ga iz kernela: sudo rmmod 01_nothing.ko
