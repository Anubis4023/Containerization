run: manifest_reader.cpp
	g++ manifest_reader.cpp -o test
	./test

#sample: manifest_maker.cpp Only turn this on when I need a fresh new manifest
#	g++ manifest_maker.cpp -o sample
#	./sample