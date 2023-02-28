PROJECT = sandbox

CC = clang++
SRC_DIR =./src
SRC = $(wildcard ${SRC_DIR}/*.cpp)
INC = ${SRC_DIR}/includes
OUT_DIR = bin
OBJ = ${SRC:.cpp=.o}
OBJ_DIR = ${OUT_DIR}/objects
LIBS = 
CFLAGS = -Wextra -Werror -Wall -std=c++20 -Wc++20-extensions -I ${INC}
BINARY = ${OUT_DIR}/${PROJECT}

main: ${OBJ}
	${CC} -o ${BINARY} ${OBJ_DIR}/*.o ${LIBS}

.cpp.o:
	${CC} -c ${CFLAGS} $<
	@mv ./*.o ${OBJ_DIR}/

run:
	@${BINARY}

gen:
	@bear -- make

clean:
	@rm -v ${OBJ_DIR}/*.o
	@rm -v ${BINARY}
	@rm -v ./compile_commands.json