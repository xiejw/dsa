BUILD_DIR=.build
CFLAGS:=-std=c99 -O2 -Wall -Werror -pedantic -Wno-c11-extensions

main: compile
	${BUILD_DIR}/main

compile:
	mkdir -p ${BUILD_DIR} && \
		${CC} ${CFLAGS} -o ${BUILD_DIR}/main main.c && \
		echo "run ${BUILD_DIR}/main"
