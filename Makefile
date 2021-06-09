CC := g++ -pthread

BUILD_DIR=build

all: sins_virtues.out

sins_virtues.out: rm mk ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/kbhit.o ${BUILD_DIR}/game.o ${BUILD_DIR}/block.o ${BUILD_DIR}/item.o ${BUILD_DIR}/map.o ${BUILD_DIR}/enemy.o  ${BUILD_DIR}/utilities.o
	$(CC) ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/item.o ${BUILD_DIR}/enemy.o ${BUILD_DIR}/kbhit.o ${BUILD_DIR}/game.o ${BUILD_DIR}/block.o ${BUILD_DIR}/map.o ${BUILD_DIR}/utilities.o -o ./sins_virtues.out

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

${BUILD_DIR}/block.o: block.cpp
	$(CC) -c block.cpp -o ${BUILD_DIR}/block.o

${BUILD_DIR}/item.o: item.cpp
	$(CC) -c item.cpp -o ${BUILD_DIR}/item.o

${BUILD_DIR}/map.o: map.cpp
	$(CC) -c map.cpp -o ${BUILD_DIR}/map.o

${BUILD_DIR}/enemy.o: enemy.cpp
	$(CC) -c enemy.cpp -o ${BUILD_DIR}/enemy.o

${BUILD_DIR}/utilities.o: utilities.cpp
	$(CC) -c utilities.cpp -o ${BUILD_DIR}/utilities.o

mk:
	mkdir ./${BUILD_DIR}

rm:
	rm -rf ${BUILD_DIR}/ ./sins_virtues.out

.PHONY: clean

clean:
	rm -rf ${BUILD_DIR}/ ./sins_virtues.out
