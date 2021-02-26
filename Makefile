CC := g++ -pthread 

BUILD_DIR=build

all: game.out

game.out: rm mk ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/kbhit.o
	$(CC) ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/kbhit.o -o ./game.out

${BUILD_DIR}/VnS.o: VnS.cpp
	$(CC) -c VnS.cpp -o ${BUILD_DIR}/VnS.o

${BUILD_DIR}/console_handler.o: console_handler.cpp
	$(CC) -c console_handler.cpp -o ${BUILD_DIR}/console_handler.o

${BUILD_DIR}/termcolor.o: termcolor.cpp
	$(CC) -c termcolor.cpp -o ${BUILD_DIR}/termcolor.o

${BUILD_DIR}/kbhit.o: kbhit.cpp
	$(CC) -c kbhit.cpp -o ${BUILD_DIR}/kbhit.o

mk:
	mkdir ./${BUILD_DIR}

rm:
	rm -rf ${BUILD_DIR}/ ./game.out

.PHONY: clean

clean:
	rm -rf ${BUILD_DIR}/ ./game.out
