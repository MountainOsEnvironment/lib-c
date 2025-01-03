CC = x86_64-elf-gcc
CFLAGS = -ffreestanding -static -m32 -nostdlib -O0 -c

SRC_DIR = src
BUILD_DIR = build
LIB_DIR = $(BUILD_DIR)/lib
INCLUDE_DIR = $(BUILD_DIR)/include

SRCS = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(LIB_DIR)/lib%.o, $(SRCS))

LIBC_FILES=\
$(LIB_DIR)/libcrt.o \
$(LIB_DIR)/libsys.o \
$(LIB_DIR)/libstd.o \
$(LIB_DIR)/libstdio.o

all: $(LIB_DIR) $(INCLUDE_DIR) $(OBJS) copy_headers link_libc

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(INCLUDE_DIR):
	mkdir -p $(INCLUDE_DIR)

$(LIB_DIR)/lib%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

copy_headers: $(INCLUDE_DIR)
	cp $(HEADERS) $(INCLUDE_DIR)

link_libc:
	x86_64-elf-ld -r -m elf_i386 -o $(LIB_DIR)/libc.o $(LIBC_FILES)

clean:
	rm -rf $(BUILD_DIR)

print:
	@echo "Sources: $(SRCS)"
	@echo "Headers: $(HEADERS)"
	@echo "Objects: $(OBJS)"