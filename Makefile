CC := g++ -pthread 

BUILD_DIR=build

all: sins_virtues.out

sins_virtues.out: rm mk ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/kbhit.o ${BUILD_DIR}/game.o
	$(CC) ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/kbhit.o ${BUILD_DIR}/game.o -o ./sins_virtues.out

${BUILD_DIR}/VnS.o: VnS.cpp
	$(CC) -c VnS.cpp -o ${BUILD_DIR}/VnS.o

${BUILD_DIR}/console_handler.o: console_handler.cpp
	$(CC) -c console_handler.cpp -o ${BUILD_DIR}/console_handler.o

${BUILD_DIR}/termcolor.o: termcolor.cpp
	$(CC) -c termcolor.cpp -o ${BUILD_DIR}/termcolor.o

${BUILD_DIR}/kbhit.o: kbhit.cpp
	$(CC) -c kbhit.cpp -o ${BUILD_DIR}/kbhit.o

${BUILD_DIR}/game.o: game.cpp
	$(CC) -c game.cpp -o ${BUILD_DIR}/game.o

mk:
	mkdir ./${BUILD_DIR}

rm:
	rm -rf ${BUILD_DIR}/ ./sins_virtues.out

.PHONY: clean

clean:
	rm -rf ${BUILD_DIR}/ ./sins_virtues.out
