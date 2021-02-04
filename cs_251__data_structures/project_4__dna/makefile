builda:
	rm -f application.exe
	g++ -g -std=c++11 -Wall application.cpp -o application.exe
	
runa:
	./application.exe

valgrind_app:
	valgrind --tool=memcheck --leak-check=yes ./application.exe


buildt:
	rm -f tests.exe
	g++ tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread
	
runt:
	./tests.exe

valgrind_tests:
	valgrind --tool=memcheck --leak-check=yes ./tests.exe