
.PHONY : clean todotui

todotui: build/todotui

build/todotui: CMakeLists.txt src/**.cc
		mkdir -p build && \
		cmake . -Bbuild -GNinja && \
		cmake --build build/


compile_commands.json: CMakeLists.txt
	cmake . -Bdebug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && \
		cp debug/compile_commands.json ./ && \
		rm -Rf debug

clean:
	rm -Rf build debug
