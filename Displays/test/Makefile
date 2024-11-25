CXX = g++-11
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = a.out
OBJECTS = biquadris-proxies.o biquadris.o display-observer.o console-view.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

biquadris-proxies.o: ./biquadris-proxies.cc ./biquadris-proxies.h ./biquadris.h
	${CXX} -c biquadris-proxies.cc

biquadris.o: ./biquadris.cc ./biquadris.h
	${CXX} -c biquadris.cc

display-observer.o: ../display-observer.cc ../display-observer.h ../../Miscellaneous/observer.h ./biquadris-proxies.h
	${CXX} -c ../display-observer.cc

console-view.o: ../console-view.cc ../console-view.h ../display-observer.h
	${CXX} -c ../console-view.cc

main.o: ../console-view.h ./biquadris-proxies.h ./biquadris.h ../display-observer.h main.cc
	${CXX} -c main.cc

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
