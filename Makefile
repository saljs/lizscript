CC=gcc
CFLAGS=-Werror
OBJS=build/builtins.o build/ctxstack.o build/errors.o build/lizscript.o \
	 build/namemap.o build/util.o build/eval.o
UNIT_TESTS=build/tests/test_basic_parse build/tests/test_builtins \
	  	   build/tests/test_names build/tests/test_switch \
		   build/tests/test_func build/tests/test_progs 
.SECONDARY: $(OBJS)

build/liz: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) parser.c -lreadline -o build/liz

build:
	mkdir -p build

build/tests: build
	mkdir -p build/tests

build/tests/%: tests/%.c $(OBJS) build/tests
	$(CC) $(CFLAGS) $< $(OBJS) -o $@
	$@

build/lizscript.o: build
	$(CC) $(CFLAGS) -c src/lizscript.c -o build/lizscript.o

build/%.o: src/core/%.c build
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r build

.PHONY: unit-test
unit-test: $(UNIT_TESTS)

.PHONY: integration-test
integration-test: build/liz
	tests/integration/test.sh

.PHONY: test
test: unit-test integration-test
