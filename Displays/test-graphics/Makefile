CXX = g++-11
CXXFLAGS = -std=c++14 -Wall -MMD 
EXEC = buss
OBJECTS = biquadris-proxies.o biquadris.o graphics-view.o window.o display-observer.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@ -lX11

graphics-view.o: ../graphics-view.cc ../graphics-view.h ../display-observer.h ../window.h
	${CXX} -c ../graphics-view.cc

window.o: ../window.cc ../window.h 
	${CXX} -c ../window.cc

display-observer.o: ../display-observer.cc ../display-observer.h ../../Miscellaneous/observer.h ./biquadris-proxies.h
	${CXX} -c ../display-observer.cc

biquadris-proxies.o: ./biquadris-proxies.cc ./biquadris-proxies.h ./biquadris.h
	${CXX} -c biquadris-proxies.cc

biquadris.o: ./biquadris.cc ./biquadris.h
	${CXX} -c biquadris.cc

main.o: ../graphics-view.h ./biquadris-proxies.h ./biquadris.h main.cc
	${CXX} -c main.cc

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
