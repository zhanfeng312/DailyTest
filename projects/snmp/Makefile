TARGET = stbinfotest
TARGET_LIBRARY=libstbinfo.so

CC=/opt/toolchains/arm-android-gcc/bin/arm-linux-androideabi-gcc
CXX=/opt/toolchains/arm-android-gcc/bin/arm-linux-androideabi-g++

CURRDIR = $(shell pwd)
HEADER_DIR := $(CURRDIR)/include
SRC_DIR := $(CURRDIR)/src
OBJ_DIR := $(CURRDIR)/obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES_NOT_DIR := $(notdir ${SRC_FILES})
BUILDIR_OBJS_NOT_DIR := $(patsubst %.cpp, %.o, $(SRC_FILES_NOT_DIR))
BUILDIR_OBJS := $(addprefix $(OBJ_DIR)/, $(BUILDIR_OBJS_NOT_DIR))

CFLAGS += -I$(HEADER_DIR) -pie -fPIE
LIBS += -L$(CURRDIR) -lstbinfo -llog -pie -fPIE

$(TARGET): prepare $(BUILDIR_OBJS) $(TARGET_LIBRARY)
	$(CC) -o $(TARGET) $(OBJ_DIR)/main.o $(LIBS) 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ -fPIC
	
$(TARGET_LIBRARY): $(OBJ_DIR)/stbinfo.o
	$(CC) -o $@ $< -shared -llog

.PHONY: clean prepare run
run:
	./$(TARGET)

distclean: clean
clean:
	rm -rf $(TARGET) $(TARGET_LIBRARY) $(OBJ_DIR)
	
prepare:
	@mkdir -p $(HEADER_DIR) $(SRC_DIR) $(OBJ_DIR)
