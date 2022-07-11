COMPILE_FILES = src/main.cpp src/core/graphics/graphics.cpp src/core/window/window.cpp src/utils/utils.cpp src/utils/shader/shader.cpp contrib/glad/src/glad.cpp

MAC_PARAMS = -I/Library/Frameworks/OpenGL.framework/Headers/ -I/Library/Frameworks/GLUT.framework/Headers/ -F/Library/Frameworks -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework CoreVideo

all:
	echo "This makefile is for macOS, linux and windows. If you're on linux type make linux, on windows make windows and on mac, make mac to use this makefile. If this is your first time compiling Constellation Engine, run make archdeps or make debiandeps depending on if you're on a debian-based or arch-based linux distro. On mac type make macdeps to install dependandices."

macdeps:
	curl -O https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh && sudo chmod a+x install.sh && ./install.sh && echo "export PATH=/usr/local/bin:$PATH" >> ~/.zshrc && source ~/.zshrc && brew install glfw

mac:
	g++ -Wall -O3 -Icontrib/ $(MAC_PARAMS) -lglfw $(COMPILE_FILES) -o main.out && ./main.out

macdebug:
	g++ -Wall -Wextra -O0 -Icontrib/ $(MAC_PARAMS) -lglfw $(COMPILE_FILES) -o main.out && ./main.out

archx11deps:
	sudo pacman -S glfw-x11

archwaylanddeps:
	sudo pacman -S glfw-wayland

debiandeps:
	sudo apt install libglfw3 libglfw3-dev libxi-dev libstb-dev

linux:
	g++ -Wall -O3 -o main.out $(COMPILE_FILES) -Icontrib/ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lrt -lm -lpthread && ./main.out

linuxdebug:
	g++ -Wall -Wextra -O0 -o main.out $(COMPILE_FILES) -Icontrib/ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lrt -lm -lpthread && ./main.out

windows:
	g++ -Wall -O3 -o ConstellationEngine.exe $(COMPILE_FILES) -l../thirdparty/glfw-3.3.6.bin.WIN32/include/ -lcontrib/ && ./ConstellationEngine.exe

windowsdebug:
	g++ -Wall -Wextra -O0 -o ConstellationEngine-debug.exe $(COMPILE_FILES) -l../thirdparty/glfw-3.3.6.bin.WIN32/include/ -lcontrib/ && ./ConstellationEngine-debug.exe
