CXX = emcc
OUTPUT = imgui.js
IMGUI_DIR:=../imgui
IMPLOT_DIR:=../implot
SRC_DIR:= src
COM_DIR:= $(SRC_DIR)/Components

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
SOURCES += $(wildcard $(COM_DIR)/*.cpp)
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/imgui_tables.cpp
SOURCES += $(IMGUI_DIR)/implot.cpp $(IMGUI_DIR)/implot_items.cpp
# SOURCES += $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/implot_demo.cpp

LIBS = -lGL
WEBGL_VER = -s USE_WEBGL2=1 -s USE_GLFW=3 -s FULL_ES3=1
#WEBGL_VER = USE_GLFW=2
USE_WASM = -s WASM=1

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CXX)  $(SOURCES) -std=c++20 -o $(OUTPUT) $(LIBS) $(WEBGL_VER) -O3 $(USE_WASM) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

clean:
	rm -f $(OUTPUT)
