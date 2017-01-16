CC = i386-elf-gcc
LD = i386-elf-ld
AS = i386-elf-as
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
 		 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror \
		 -Isrc
ASFLAGS = -march=generic32

SRCPATH = src
OBJPATH = obj
TARPATH = bin
GRUBPATH = boot/grub

LDSCRIPT = $(SRCPATH)/link.ld
LDFLAGS = -T $(LDSCRIPT) -melf_i386

GRUBMENU = menu.lst
GRUBBOOT = stage2_eltorito

ISO = mkisofs
ISOFLAGS = -R -b $(GRUBPATH)/$(GRUBBOOT) -no-emul-boot -boot-load-size 4 \
		   -boot-info-table -input-charset utf8 -A os

LIB = mm/segment io/port io/serial io/dev util/string
OBJ = loader kmain mm/segment_s $(LIB)
LIBFILE = $(patsubst %, $(OBJPATH)/%.o, $(LIB))
LIBHEADER = $(patsubst %, $(SRCPATH)/%.h, $(LIB))
OBJFILE = $(patsubst %, $(OBJPATH)/%.o, $(OBJ))
TARGET = $(TARPATH)/kernel

GRUB = $(GRUBMENU) $(GRUBBOOT)
GRUBFILE = $(patsubst %, $(TARPATH)/$(GRUBPATH)/%, $(GRUB))
IMAGE = os.iso

BOCHS = bochs
BOCHSRC = .bochsrc
BOCHSFLAGS = -f $(BOCHSRC) -q

all : $(IMAGE)

run : all
	$(BOCHS) $(BOCHSFLAGS)

rebuild : clean all

clean :
	rm -fr $(IMAGE) $(TARGET) $(OBJPATH)/**/*.o

$(IMAGE) : $(TARGET) $(GRUBFILE) makefile
	$(ISO) $(ISOFLAGS) -o $(IMAGE) $(TARPATH)

$(TARPATH)/$(GRUBPATH)/$(GRUBMENU) : $(SRCPATH)/$(GRUBMENU) makefile
	cp $< $@

$(TARGET) : $(OBJFILE) $(LDSCRIPT) makefile
	$(LD) $(LDFLAGS) -o $@ $(OBJFILE)

$(OBJPATH)/%.o : $(SRCPATH)/%.s makefile
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJPATH)/%.o : $(SRCPATH)/%.c makefile
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)/kmain.o : $(LIBHEADER)

$(LIBFILE) : $(OBJPATH)/%.o : $(SRCPATH)/%.h

.PHONY : all clean rebuild
