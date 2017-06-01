include sources.mk

OBJECTS=$(SOURCES:.cpp=.bc)

GLEW_OBJECTS=$(addprefix bin/glew/, $(OBJECTS))
GLES3_OBJECTS=$(addprefix bin/gles3/, $(OBJECTS))
ASMJS_OBJECTS=$(addprefix bin/asmjs/, $(OBJECTS))

LIBRARIES=gloopcpp
INCLUDES=$(addprefix -I, $(LIBRARIES))

.PHONY: all clean

all: bin/glew/inf_demo.exe bin/gles3/inf_demo.exe

bin/glew/%.bc: %.cpp
	clang++ $(INCLUDES) -DGL=GLEW -DUSE_SDL_IMAGE -emit-llvm -std=c++14 -O3 -c -o $@ $<

bin/gles3/%.bc: %.cpp
	clang++ -emit-llvm -D=GLES3 -DUSE_SDL_IMAGE -std=c++14 -O3 -c -o $@ $<

bin/asmjs/%.bc: %.cpp
	clang++ -emit-llvm -D=GLES2 -DUSE_SDL_IMAGE -std=c++14 -O3 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL_IMAGE_FORMATS='["png"]' -c -o $@ $<

bin/glew/inf_demo.exe: $(GLEW_OBJECTS)
	clang++ $(GLEW_OBJECTS) gloopcpp/bin/glew/libGLOOP.bc -o $@ `pkg-config --libs sdl2` `pkg-config --libs SDL2_image` `pkg-config --libs glew` 

bin/gles3/inf_demo.exe: $(GLEW_OBJECTS)
	clang++ $(GLEW_OBJECTS) gloopcpp/bin/gles3/libGLOOP.bc -o $@ `pkg-config --libs sdl2` `pkg-config --libs SDL2_image` `pkg-config --libs glesv2`

clean:
	rm -fv $(GLEW_OBJECTS)
	rm -fv $(GLES3_OBJECTS)
	rm -fv $(ASMJS_OBJECTS)
	rm -fv bin/glew/inf_demo.exe
	rm -fv bin/gles3/inf_demo.exe
	
