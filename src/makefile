objects = undirectedgraph.o\
	mwis.o

lib : mwis.o undirectedgraph.o
	g++ -O3 -Wall -shared -std=c++11 -fPIC -o ../lib/mwis`python3-config --extension-suffix` mwis.o undirectedgraph.o
	ln -sf ../lib/mwis`python3-config --extension-suffix` ../lib/mwis

mwis.o : mwis.cpp undirectedgraph.h exceptions.h
	g++ -std=c++11 -fPIC `python -m pybind11 --includes` -I"/usr/include/eigen3" -c mwis.cpp

undirectedgraph.o : undirectedgraph.cpp undirectedgraph.h exceptions.h
	g++ -std=c++11 -fPIC -c undirectedgraph.cpp

clean:
	rm ../lib/mwis ../lib/mwis`python3-config --extension-suffix` $(objects)
