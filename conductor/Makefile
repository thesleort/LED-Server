
EXE = conductor.out

SRC_DIR = src
OBJ_DIR = build
INC_DIR = -Iinclude/

LIB = $(LDFLAGS)

CC = gcc

CFLAGS += -std=c11 `pkg-config --cflags gtk+-3.0` -Wall -Wextra -pedantic -g

LDFLAGS += -Llib

LDLIBS += -lm `pkg-config --libs gtk+-3.0`

SRC = $(wildcard $(SRC_DIR)/*.c \
		$(SRC_DIR)/*/*.c)
INC		= $(INC_DIR)
OBJROOT = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ 	= $(OBJROOT:$(SRC_DIR)/*/%.c=$(OBJ_DIR)/*/%.o)

MODULES = $(filter-out $(MOD_DIR)/README.md $(wildcard $(SRC_DIR)/*.c), $(wildcard $(SRC_DIR)/*/))

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LIB) $(INC) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(addprefix $(OBJ_DIR)/, $(MODULES:$(SRC_DIR)/%=%))
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*
	$(RM) $(EXE)