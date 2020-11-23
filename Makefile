mon_executable: main.o lecture_fichier_txt.o 
	g++ -o mon_executable main.o lecture_fichier_txt.o -Wall -lstdc++fs

main.o: main.cpp lecture_fichier_txt.hpp 
	g++ -c main.cpp -Wall -g

lecture_fichier_txt.o: lecture_fichier_txt.hpp

clean:
	-rm *.o
