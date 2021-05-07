.PHONY: clean
CC = g++-4.8
PLUGIN_DIR ?= `${CC} -print-file-name=plugin`
OBJS = plugin.o cp-parser/parser.o cp-parser/c-pragma.o cp-parser/pt.o cp-parser/decl.o
CFLAGS = -I${PLUGIN_DIR}/include -I${PLUGIN_DIR}/include/cp -I${PLUGIN_DIR}/include/c-family -fno-rtti -fPIC -O2
.c.o:
	${CC} ${CFLAGS} -c $< -o $@

.cpp.o:
	${CC} ${CFLAGS} -c $< -o $@


plugin.so: ${OBJS} link.lds
	${CC} ${CFLAGS} -shared -Wl,--start-group ${OBJS} -Wl,--end-group -o plugin.so -Wl,--version-script=link.lds

clean:
	rm -f plugin.so ${OBJS}
