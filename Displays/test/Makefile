CXX = g++-11
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = a.out
OBJECTS = biquadris-proxies.o biquadris.o console-view.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

biquadris-proxies.o: ./biquadris-proxies.cc ./biquadris-proxies.h ./biquadris.h
	${CXX} -c biquadris-proxies.cc

biquadris.o: ./biquadris.cc ./biquadris.h
	${CXX} -c biquadris.cc

console-view.o: ../console-view.cc ../console-view.h ../../Miscellaneous/observer.h ./biquadris-proxies.h 
	${CXX} -c ../console-view.cc

main.o: ../console-view.h ./biquadris-proxies.h ./biquadris.h main.cc
	${CXX} -c main.cc

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
