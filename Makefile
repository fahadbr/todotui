
.PHONY : clean todotui compile_commands

todotui: build/todotui

build/todotui: build/CMakeCache.txt
		cmake --build build/

build/CMakeCache.txt: CMakeLists.txt src/**.cpp
			mkdir -p build && \
			cmake . -Bbuild -GNinja && \
			cp build/compile_commands.json ./

clean:
	rm -Rf build
