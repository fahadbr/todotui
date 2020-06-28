
.PHONY : clean todotui cache

todotui: compile_commands.json
		cmake --build build/ -- todotui

test: build/CMakeCache.txt
	cmake --build build/ && cd build && ctest -V

cache: build/CMakeCache.txt

compile_commands.json: build/CMakeCache.txt
	cp build/compile_commands.json ./

build/CMakeCache.txt: CMakeLists.txt
			mkdir -p build && \
			cmake . -Bbuild -GNinja

clean:
	rm -Rf build
