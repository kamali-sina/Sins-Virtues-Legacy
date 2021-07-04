CC := g++ -pthread

BUILD_DIR=build

all: sins_virtues.out

sins_virtues.out: rm mk ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/kbhit.o ${BUILD_DIR}/game.o ${BUILD_DIR}/block.o ${BUILD_DIR}/item.o ${BUILD_DIR}/map.o ${BUILD_DIR}/enemy.o  ${BUILD_DIR}/utilities.o ${BUILD_DIR}/handlers.o ${BUILD_DIR}/player.o ${BUILD_DIR}/dialogs.o
	$(CC) ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/item.o ${BUILD_DIR}/enemy.o ${BUILD_DIR}/kbhit.o ${BUILD_DIR}/game.o ${BUILD_DIR}/block.o ${BUILD_DIR}/map.o ${BUILD_DIR}/utilities.o ${BUILD_DIR}/handlers.o ${BUILD_DIR}/player.o ${BUILD_DIR}/dialogs.o -o ./sins_virtues.out

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

${BUILD_DIR}/handlers.o: handlers.cpp
	$(CC) -c handlers.cpp -o ${BUILD_DIR}/handlers.o

${BUILD_DIR}/player.o: player.cpp
	$(CC) -c player.cpp -o ${BUILD_DIR}/player.o

${BUILD_DIR}/dialogs.o: dialogs.cpp
	$(CC) -c dialogs.cpp -o ${BUILD_DIR}/dialogs.o

mk:
	mkdir ./${BUILD_DIR}

rm:
	rm -rf ${BUILD_DIR}/ ./sins_virtues.out

.PHONY: clean

clean:
	rm -rf ${BUILD_DIR}/ ./sins_virtues.out
