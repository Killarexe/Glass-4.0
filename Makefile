CXX = g++

NAME = glass4

CXX_FLAGS = -O2 -lsfml-graphics -lsfml-window -lsfml-system
DEBUG_FLAGS = -g
OBJ_FLAGS = $(CXX_FLAGS) -c

BUILD_DIR = build
BIN_DIR = lib
OBJ_DIR = obj
DEBUG_DIR = debug
SOURCE_DIR = src

BIN_PATH = $(BUILD_DIR)/$(BIN_DIR)
OBJ_PATH = $(BUILD_DIR)/$(OBJ_DIR)
DEBUG_PATH = $(BUILD_DIR)/$(DEBUG_DIR)

LIB_FILE = $(BIN_PATH)/$(NAME).a
LIB_FILE_DEBUG = $(DEBUG_DIR)/$(NAME).a

SOURCES = $(foreach x, $(SOURCE_DIR), $(wildcard $(addprefix $(x)/*,.c*)))
OBJS := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SOURCES)))))
OBJS_DEBUG := $(addprefix $(DEBUG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SOURCES)))))

all: $(BIN_PATH) $(OBJ_PATH) $(DEBUG_PATH) $(LIB_FILE)

debug: $(BIN_PATH) $(OBJ_PATH) $(DEBUG_PATH) $(LIB_FILE_DEBUG)

clean:
	rm -rf $(BUILD_DIR)

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(DEBUG_PATH):
	@mkdir -p $(DEBUG_PATH)

$(LIB_FILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXX_FLAGS)

$(OBJ_PATH)/%.o: $(SOURCE_DIR)/%.c*
	$(CXX) $(OBJ_FLAGS) -o $@ $<

$(LIB_FILE_DEBUG): $(OBJS_DEBUG)
	$(CXX) $(OBJS_DEBUG) $(DEBUG_FLAGS) $(OBJS_DEBUG) -o $@

$(DEBUG_PATH)/%.o: $(SOURCE_DIR)/%.c*
	$(CXX) $(OBJ_FLAGS) $(DEBUG_FLAGS) -o $@ $<
