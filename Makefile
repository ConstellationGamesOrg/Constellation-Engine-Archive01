COMPILE_FILES = src/main.c lib/glad/src/glad.c

all:
	echo "This makefile is for macOS and linux. If you're on linux type make linux and on mac, make mac to use this makefile. If this is your first time compiling Constellation Engine, run make archdeps or make debiandeps depending on if you're on a debian-based or arch-based linux distro. On mac type make macdeps to install dependandices."

macdeps:
	curl -O https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh && sudo chmod a+x install.sh && ./install.sh && echo "export PATH=/usr/local/bin:$PATH" >> ~/.zshrc && source ~/.zshrc && brew install glfw && brew install cglm

mac:
	gcc -Wall -O3 -Ilib/ -I/Library/Frameworks/OpenGL.framework/Headers/ -I/Library/Frameworks/GLUT.framework/Headers/ -F/Library/Frameworks -lglfw -lglm -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework CoreVideo $(COMPILE_FILES) -o main.out && ./main.out

macdebug:
	gcc -Wall -Wextra -O0 -Ilib/ -I/Library/Frameworks/OpenGL.framework/Headers/ -I/Library/Frameworks/GLUT.framework/Headers/ -F/Library/Frameworks -lglfw -lglm -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework CoreVideo $(COMPILE_FILES) contrib/glad/src/glad.cpp -o main.out && ./main.out

archx11deps:
	sudo pacman -S glfw-x11 && git clone https://github.com/recp/cglm && cd cglm && mkdir build && cd build && cmake .. && make && sudo make install

archwaylanddeps:
	sudo pacman -S glfw-wayland && git clone https://github.com/recp/cglm && cd cglm && mkdir build && cd build && cmake .. && make && sudo make install

debiandeps:
	sudo apt install libglfw3 libglfw3-dev libxi-dev libstb-dev libcglm-dev

linux:
	gcc -Wall -O3 -o main.out $(COMPILE_FILES) -Ilib/ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lrt -lm -lpthread && ./main.out

linuxdebug:
	gcc -Wall -Wextra -O0 -o main.out $(COMPILE_FILES) -Ilib/ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lrt -lm -lpthread && ./main.out
