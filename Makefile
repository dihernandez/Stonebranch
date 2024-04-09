output:	main.o	CSV_File.o	Customer_Sample_File.o	Customer_Master_File.o
	g++	-std=c++17	main.o	CSV_File.o	Customer_Sample_File.o	Customer_Master_File.o	-o	output

main.o:	main.cpp
	g++ -std=c++17	-c	main.cpp

CSV_File.o:	CSV_File.cpp	CSV_File.hpp
	g++	-std=c++17	-c	CSV_File.cpp

Customer_Sample_File.o:	Customer_Sample_File.cpp	Customer_Sample_File.hpp
	g++	-std=c++17	-c	Customer_Sample_File.cpp

Customer_Master_File.o:	Customer_Master_File.cpp	Customer_Master_File.hpp
	g++	-std=c++17	-c	Customer_Master_File.cpp

clean:
	rm	*.o	output
