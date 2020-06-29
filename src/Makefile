../bin/main: ../build/main.o ../build/vec3f.o ../build/stb_image_write.o
	g++ -Wall ../build/main.o ../build/vec3f.o ../build/stb_image_write.o -o ../bin/main

../build/main.o: main.cpp ../include/vec3f.hpp ../include/stb/stb_image_write.h
	g++ -c main.cpp -o ../build/main.o -I../include/

../build/vec3f.o: vec3f.cpp ../include/vec3f.hpp
	g++ -c vec3f.cpp -o ../build/vec3f.o -I../include/

../build/stb_image_write.o: ../include/stb/stb_image_write.h
	g++ -c stb_image_write.cpp -o ../build/stb_image_write.o -I../include/

dirs:
	mkdir ../bin/ ../build/

clean:
	rm -rf ../bin/main ../build/*
