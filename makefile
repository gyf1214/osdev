CC = i386-elf-gcc
LD = i386-elf-ld
AS = i386-elf-as
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
 		 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror \
		 -Isrc -g
ASFLAGS = -march=generic32

SRCPATH = src
OBJPATH = obj
TARPATH = bin
TMPPATH = tmp
GRUBPATH = boot/grub

LDSCRIPT = $(SRCPATH)/link.ld
LDFLAGS = -T $(LDSCRIPT) -melf_i386

GRUBMENU = menu.lst
GRUBBOOT = stage2_eltorito

ISO = mkisofs
ISOFLAGS = -R -b $(GRUBPATH)/$(GRUBBOOT) -no-emul-boot -boot-load-size 4 \
		   -boot-info-table -input-charset utf8 -A os

LIB = mm/segment io/port io/serial io/device util/string io/framebuffer
OBJ = loader kmain mm/segment_s $(LIB)
LIBFILE = $(patsubst %, $(OBJPATH)/%.o, $(LIB))
LIBHEADER = $(patsubst %, $(SRCPATH)/%.h, $(LIB))
OBJFILE = $(patsubst %, $(OBJPATH)/%.o, $(OBJ))
TARGET = $(TARPATH)/kernel
IMAGE = os.iso

BOCHS = bochs
BOCHSRC = .bochsrc
BOCHSFLAGS = -f $(BOCHSRC) -q

QEMU = qemu-system-i386
QEMULOG = tmp/qemu.log
QEMUSERIAL = tmp/com1.log
QEMUFLAGS = -D $(QEMULOG) -serial file:$(QEMUSERIAL) -s -S -cdrom

GDB = i386-elf-gdb

all : $(IMAGE)

run : all
	mkdir -p $(TMPPATH)
	$(QEMU) $(QEMUFLAGS) $(IMAGE) &
	$(GDB)

rebuild : clean all

clean :
	rm -fr $(IMAGE) $(TARGET) $(OBJPATH)/**/*.o

$(IMAGE) : $(TARGET) $(GRUBFILE) makefile
	$(ISO) $(ISOFLAGS) -o $(IMAGE) $(TARPATH)

$(TARGET) : $(OBJFILE) $(LDSCRIPT) makefile
	mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $(OBJFILE)

$(OBJPATH)/%.o : $(SRCPATH)/%.s makefile
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJPATH)/%.o : $(SRCPATH)/%.c makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)/kmain.o : $(LIBHEADER)

$(LIBFILE) : $(OBJPATH)/%.o : $(SRCPATH)/%.h

.PHONY : all clean rebuild
