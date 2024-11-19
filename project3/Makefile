useDijkstra.exe: useDijkstra.o heap.o hash.o graph.o
	g++ -o useDijkstra.exe useDijkstra.o heap.o hash.o graph.o

useDijkstra.o: useDijkstra.cpp graph.h
	g++ -c useDijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

debug:
	g++ -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups