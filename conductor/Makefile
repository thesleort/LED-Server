
EXE = conductor.out

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include

PKG = gtk+-3.0 webkit2gtk-4.0 gstreamer-1.0 gstreamer-video-1.0 libconfig

LIB = $(LDFLAGS)

CC = gcc

CFLAGS += -std=c11 `pkg-config --cflags $(PKG)` -Wall -Wextra -pedantic -g

LDFLAGS += -Llib

LDLIBS += -lm `pkg-config --libs $(PKG)`

SRC = $(wildcard $(SRC_DIR)/*.c \
		$(SRC_DIR)/*/*.c)
INC		= -I$(INC_DIR)/
OBJROOT = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ 	= $(OBJROOT:$(SRC_DIR)/*/%.c=$(OBJ_DIR)/*/%.o)

MODULES = $(filter-out $(MOD_DIR)/README.md $(wildcard $(SRC_DIR)/*.c) $(wildcard $(INC_DIR)/*.h), $(wildcard $(SRC_DIR)/*/))

all: $(EXE)

$(EXE): $(OBJ) 
	$(CC) $(INC) $^ -o $@ $(LIB) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	mkdir -p $(addprefix $(OBJ_DIR)/, $(MODULES:$(SRC_DIR)/%=%))
	$(CC) $(INC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*
	$(RM) $(EXE)