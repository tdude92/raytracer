bin/main: build/main.o build/vec3f.o build/geometry.o build/engine.o build/cfgparser.o build/stb_image_write.o
	g++ -Wall build/main.o build/vec3f.o build/geometry.o build/engine.o build/cfgparser.o build/stb_image_write.o -o bin/main

build/main.o: src/main.cpp include/cfgparser.hpp include/engine.hpp
	g++ -c src/main.cpp -o build/main.o -Iinclude/

build/cfgparser.o: src/cfgparser.cpp include/vec3f.hpp include/cfgparser.hpp
	g++ -c src/cfgparser.cpp -o build/cfgparser.o -Iinclude/

build/engine.o: src/engine.cpp include/engine.hpp include/vec3f.hpp include/geometry.hpp include/stb/stb_image_write.h
	g++ -c src/engine.cpp -o build/engine.o -Iinclude/

build/geometry.o: src/geometry.cpp include/geometry.hpp include/vec3f.hpp
	g++ -c src/geometry.cpp -o build/geometry.o -Iinclude/

build/vec3f.o: src/vec3f.cpp include/vec3f.hpp
	g++ -c src/vec3f.cpp -o build/vec3f.o -Iinclude/

build/stb_image_write.o: src/stb_image_write.cpp include/stb/stb_image_write.h
	g++ -c src/stb_image_write.cpp -o build/stb_image_write.o -Iinclude/

dirs:
	mkdir bin/ build/

clean:
	rm -rf bin/main build/*
