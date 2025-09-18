# project information
PROJECT_DIR := .
LIBFDT_DIR := ./../../u-boot/scripts/dtc/libfdt

OUTPUT_DIR := ./out
CC := gcc

USER_OBJS := parse_device_tree.o

VPATH = ${PROJECT_DIR} ${LIBFDT_DIR} ${OUTPUT_DIR}

# collect make file libfdt
include ${LIBFDT_DIR}/Makefile.libfdt

# flag build
$(USER_OBJS): CFLAGS := -I$(PROJECT_DIR) -I$(LIBFDT_DIR)
$(LIBFDT_OBJS): CFLAGS := -I$(LIBFDT_DIR)

# colect all obj file
OBJ_FILE := ${USER_OBJS} ${LIBFDT_OBJS}
OBJ_FILE_PATH := $(addprefix $(OUTPUT_DIR)/,${USER_OBJS} ${LIBFDT_OBJS})

create_output_folder:
	mkdir -p ${OUTPUT_DIR}

app: ${OBJ_FILE}
	${CC} -o ${OUTPUT_DIR}/$@ ${OBJ_FILE_PATH}

%.o: %.c
	@echo "compling $<"
	@${CC} ${CFLAGS} -c $< -o ${OUTPUT_DIR}/$@

all: create_output_folder app

run:
	@${OUTPUT_DIR}/app

print-%:
	@echo "$*=$($*)"












