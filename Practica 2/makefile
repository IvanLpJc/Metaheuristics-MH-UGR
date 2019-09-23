folders = obj bin

all: make_folders bin/main

make_folders:
	mkdir -p ${folders}
bin/main : obj/main.o obj/Utilidades.o obj/PreparacionDatos.o obj/K-NN.o obj/Relief.o
	g++ -g -O2 -std=c++11 -o bin/main obj/main.o obj/Utilidades.o obj/PreparacionDatos.o obj/K-NN.o obj/Relief.o
obj/main.o : src/main.cpp
	g++ -g -O2 -std=c++11 -c -I./include -o obj/main.o src/main.cpp
obj/Utilidades.o : src/Utilidades.cpp include/Utilidades.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/Utilidades.o src/Utilidades.cpp
obj/PreparacionDatos.o : src/PreparacionDatos.cpp include/PreparacionDatos.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/PreparacionDatos.o src/PreparacionDatos.cpp
obj/K-NN.o : src/K-NN.cpp include/K-NN.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/K-NN.o src/K-NN.cpp
obj/Relief.o : src/Relief.cpp include/Relief.h
	g++ -g -O2 -std=c++11 -c -I./include -o obj/Relief.o src/Relief.cpp
clean:
	rm -r obj/ bin/
