build:
	rm -f application.exe
	g++ -std=c++11 -Wall application.cpp dist.cpp osm.cpp algs.cpp tinyxml2.cpp -o application.exe

run:
	./application.exe

buildt:
	rm -f testing.exe
	g++ -std=c++11 -Wall testing.cpp -o testing.exe

runt:
	./testing.exe
	

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./application.exe
