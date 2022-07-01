COMPILE_FILES = src/main.c src/core/graphics/graphics.c src/core/window/window.c src/core/input/input.c src/util/util.c lib/glad/src/glad.c

MAC_PARAMS = -I/Library/Frameworks/OpenGL.framework/Headers/ -I/Library/Frameworks/GLUT.framework/Headers/ -F/Library/Frameworks -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework CoreVideo

all:
	echo "This makefile is for macOS and linux. If you're on linux type make linux and on mac, make mac to use this makefile. If this is your first time compiling Constellation Engine, run make archdeps or make debiandeps depending on if you're on a debian-based or arch-based linux distro. On mac type make macdeps to install dependandices."

macdeps:
	curl -O https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh && sudo chmod a+x install.sh && ./install.sh && echo "export PATH=/usr/local/bin:$PATH" >> ~/.zshrc && source ~/.zshrc && brew install glfw && brew install cglm

mac:
	gcc -Wall -O3 -Ilib/ $(MAC_PARAMS) -lglfw -lcglm $(COMPILE_FILES) -o main.out && ./main.out

macdebug:
	gcc -Wall -Wextra -O0 -D_DEBUG=1 -Ilib/ $(MAC_PARAMS) -lglfw -lcglm $(COMPILE_FILES) -o main.out && ./main.out

archx11deps:
	sudo pacman -S glfw-x11 && git clone https://github.com/recp/cglm && cd cglm && mkdir build && cd build && cmake .. && make && sudo make install

archwaylanddeps:
	sudo pacman -S glfw-wayland && git clone https://github.com/recp/cglm && cd cglm && mkdir build && cd build && cmake .. && make && sudo make install

debiandeps:
	sudo apt install libglfw3 libglfw3-dev libxi-dev libstb-dev libcglm-dev

linux:
	gcc -Wall -O3 -o main.out $(COMPILE_FILES) -Ilib/ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lrt -lm -lpthread && ./main.out

linuxdebug:
	gcc -Wall -Wextra -O0 -o main.out -D_DEBUG=1 $(COMPILE_FILES) -Ilib/ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lrt -lm -lpthread && ./main.out

windows:
	gcc -Wall -O3 -o ConstellationEngine.exe $(COMPILE_FILES) -Ilib/ -l../thirdparty/glfw-3.3.6.bin.WIN32/include/ -l../thirdparty/cglm-0.8.5/include/ && ./ConstellationEngine.exe

windowsdebug:
	gcc -Wall -Wextra -O0 -o ConstellationEngine-debug.exe -D_DEBUG=1 $(COMPILE_FILES) -Ilib/ -l../thirdparty/glfw-3.3.6.bin.WIN32/include/ -l../thirdparty/cglm-0.8.5/include/ && ./ConstellationEngine-debug.exe
