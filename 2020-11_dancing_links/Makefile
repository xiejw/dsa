BUILD_DIR=.build
CFLAGS:=-std=c99 -O2 -Wall -Werror -pedantic -Wno-c11-extensions

main: compile
	${BUILD_DIR}/main

compile:
	mkdir -p ${BUILD_DIR} && \
		${CC} ${CFLAGS} -o ${BUILD_DIR}/double_links.o -c double_links.c && \
		${CC} ${CFLAGS} -o ${BUILD_DIR}/main main.c ${BUILD_DIR}/double_links.o && \
		echo "run ${BUILD_DIR}/main"

fmt:
	make -C .. fmt
