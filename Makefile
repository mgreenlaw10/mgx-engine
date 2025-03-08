#
#	Project structure.
#

CC = g++

INC_PATH 		= inc
LIB_PATH 		= lib
SRC_PATH 		= src
OBJ_PATH 		= obj

IMGUI_TARGET 	= imgui
MGX_TARGET 		= mgx
SCENE_TARGET 	= scene
STBI_TARGET 	= stbi

L_FLAGS =\
-lglew32s\
-lglfw3\
-lopengl32\
-lgdi32\
-luser32\
-lshell32

EXE_NAME = run.exe

#
#	Macros for determining what .o files should exist based on existing .cpp files.
#

IMGUI_SRCS = $(wildcard $(SRC_PATH)/$(IMGUI_TARGET)/*.cpp)
IMGUI_OBJS = $(IMGUI_SRCS:$(SRC_PATH)/$(IMGUI_TARGET)/%.cpp=$(OBJ_PATH)/$(IMGUI_TARGET)/%.o)

MGX_SRCS = $(wildcard $(SRC_PATH)/$(MGX_TARGET)/*.cpp)
MGX_OBJS = $(MGX_SRCS:$(SRC_PATH)/$(MGX_TARGET)/%.cpp=$(OBJ_PATH)/$(MGX_TARGET)/%.o)

SCENE_SRCS = $(wildcard $(SRC_PATH)/$(SCENE_TARGET)/*.cpp)
SCENE_OBJS = $(SCENE_SRCS:$(SRC_PATH)/$(SCENE_TARGET)/%.cpp=$(OBJ_PATH)/$(SCENE_TARGET)/%.o)

STBI_SRCS = $(wildcard $(SRC_PATH)/$(STBI_TARGET)/*.cpp)
STBI_OBJS = $(STBI_SRCS:$(SRC_PATH)/$(STBI_TARGET)/%.cpp=$(OBJ_PATH)/$(STBI_TARGET)/%.o)

MAIN_SRCS = $(SRC_PATH)/main.cpp
MAIN_OBJS = $(OBJ_PATH)/main.o

OBJS = $(IMGUI_OBJS) $(MGX_OBJS) $(SCENE_OBJS) $(STBI_OBJS) $(MAIN_OBJS)

#
#	Main target.
#

$(EXE_NAME): $(OBJS)
	$(CC) $^ -L $(LIB_PATH) $(L_FLAGS) -o $(EXE_NAME)

#	
#	Compilation targets.
# 	All of these targets describe dirs that exist in both src and obj.
#

# MAIN
$(OBJ_PATH)/main.o : $(SRC_PATH)/main.cpp
	$(CC) -Wextra -I $(SRC_PATH) -I $(INC_PATH) -c $(SRC_PATH)/main.cpp -o $@

# IMGUI
$(OBJ_PATH)/$(IMGUI_TARGET)/%.o: $(SRC_PATH)/$(IMGUI_TARGET)/%.cpp
	$(CC) -Wextra -I $(SRC_PATH) -I $(INC_PATH) -c $< -o $@

# MGX
$(OBJ_PATH)/$(MGX_TARGET)/%.o: $(SRC_PATH)/$(MGX_TARGET)/%.cpp
	$(CC) -Wextra -I $(SRC_PATH) -I $(INC_PATH) -c $< -o $@

# SCENE
$(OBJ_PATH)/$(SCENE_TARGET)/%.o: $(SRC_PATH)/$(SCENE_TARGET)/%.cpp
	$(CC) -Wextra -I $(SRC_PATH) -I $(INC_PATH) -c $< -o $@

# STBI
$(OBJ_PATH)/$(STBI_TARGET)/%.o: $(SRC_PATH)/$(STBI_TARGET)/%.cpp
	$(CC) -Wextra -I $(SRC_PATH) -I $(INC_PATH) -c $< -o $@

#
#	Clean targets.
#

# Delete all source files (keep libs)
.PHONY: clean
clean:
	del $(OBJ_PATH)\\*.o
	del $(OBJ_PATH)\\$(MGX_TARGET)\\*.o
	del $(OBJ_PATH)\\$(SCENE_TARGET)\\*.o
	del $(EXE_NAME)

# Delete everything
.PHONY: fullclean
fullclean:
	del $(OBJ_PATH)\\*.o
	del $(OBJ_PATH)\\$(IMGUI_TARGET)\\*.o
	del $(OBJ_PATH)\\$(MGX_TARGET)\\*.o
	del $(OBJ_PATH)\\$(SCENE_TARGET)\\*.o
	del $(OBJ_PATH)\\$(STBI_TARGET)\\*.o
	del $(EXE_NAME)

PHONY: mgxclean
mgxclean:
	del $(OBJ_PATH)\\$(MGX_TARGET)\\*.o

PHONY: sceneclean
sceneclean:
	del $(OBJ_PATH)\\$(SCENE_TARGET)\\*.o