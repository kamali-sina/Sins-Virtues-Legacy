CC := g++ -pthread

BUILD_DIR=build
SRC_DIR=src
OUTPUT_NAME=sins_virtues

all: ${OUTPUT_NAME}

${OUTPUT_NAME}: rm mk ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/kbhit.o ${BUILD_DIR}/game.o ${BUILD_DIR}/block.o ${BUILD_DIR}/item.o ${BUILD_DIR}/map.o ${BUILD_DIR}/enemy.o  ${BUILD_DIR}/utilities.o ${BUILD_DIR}/player.o ${BUILD_DIR}/dialogs.o ${BUILD_DIR}/status_effect.o
	$(CC) ${BUILD_DIR}/VnS.o ${BUILD_DIR}/console_handler.o ${BUILD_DIR}/termcolor.o ${BUILD_DIR}/item.o ${BUILD_DIR}/enemy.o ${BUILD_DIR}/kbhit.o ${BUILD_DIR}/game.o ${BUILD_DIR}/block.o ${BUILD_DIR}/map.o ${BUILD_DIR}/utilities.o ${BUILD_DIR}/player.o ${BUILD_DIR}/dialogs.o ${BUILD_DIR}/status_effect.o -o ./${OUTPUT_NAME}

${BUILD_DIR}/VnS.o: ${SRC_DIR}/VnS.cpp
	$(CC) -c ${SRC_DIR}/VnS.cpp -o ${BUILD_DIR}/VnS.o

${BUILD_DIR}/console_handler.o: ${SRC_DIR}/console_handler.cpp
	$(CC) -c ${SRC_DIR}/console_handler.cpp -o ${BUILD_DIR}/console_handler.o

${BUILD_DIR}/termcolor.o: ${SRC_DIR}/termcolor.cpp
	$(CC) -c ${SRC_DIR}/termcolor.cpp -o ${BUILD_DIR}/termcolor.o

${BUILD_DIR}/kbhit.o: ${SRC_DIR}/kbhit.cpp
	$(CC) -c ${SRC_DIR}/kbhit.cpp -o ${BUILD_DIR}/kbhit.o

${BUILD_DIR}/game.o: ${SRC_DIR}/game.cpp
	$(CC) -c ${SRC_DIR}/game.cpp -o ${BUILD_DIR}/game.o

${BUILD_DIR}/block.o: ${SRC_DIR}/block.cpp
	$(CC) -c ${SRC_DIR}/block.cpp -o ${BUILD_DIR}/block.o

${BUILD_DIR}/item.o: ${SRC_DIR}/item.cpp
	$(CC) -c ${SRC_DIR}/item.cpp -o ${BUILD_DIR}/item.o

${BUILD_DIR}/map.o: ${SRC_DIR}/map.cpp
	$(CC) -c ${SRC_DIR}/map.cpp -o ${BUILD_DIR}/map.o

${BUILD_DIR}/enemy.o: ${SRC_DIR}/enemy.cpp
	$(CC) -c ${SRC_DIR}/enemy.cpp -o ${BUILD_DIR}/enemy.o

${BUILD_DIR}/utilities.o: ${SRC_DIR}/utilities.cpp
	$(CC) -c ${SRC_DIR}/utilities.cpp -o ${BUILD_DIR}/utilities.o

${BUILD_DIR}/player.o: ${SRC_DIR}/player.cpp
	$(CC) -c ${SRC_DIR}/player.cpp -o ${BUILD_DIR}/player.o

${BUILD_DIR}/dialogs.o: ${SRC_DIR}/dialogs.cpp
	$(CC) -c ${SRC_DIR}/dialogs.cpp -o ${BUILD_DIR}/dialogs.o

${BUILD_DIR}/status_effect.o: ${SRC_DIR}/status_effect.cpp
	$(CC) -c ${SRC_DIR}/status_effect.cpp -o ${BUILD_DIR}/status_effect.o

mk:
	mkdir ./${BUILD_DIR}

rm:
	rm -rf ${BUILD_DIR}/ ./${OUTPUT_NAME}

.PHONY: clean

clean:
	rm -rf ${BUILD_DIR}/ ./${OUTPUT_NAME}
