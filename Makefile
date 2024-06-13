build/%.o: source/%.asm
	nasm -f elf32 $< -o $@
build/%.o: source/%.c
	gcc -c -g -I include -m32 $< -o $@

build: build/func.o build/root.o build/integral.o build/main.o build/functions.o
	gcc $^ -m32 -g -o build/program -lm

create_build_dir:
	mkdir -p build

all: create_build_dir build

clean:
	rm -r build

test: all
	build/program --test-root 4:6:0.1:1.0:0.0001:0.2654
	build/program --test-root 5:6:1.0:2.0:0.0001:1.3660
	build/program --test-root 4:5:2.0:3.0:0.0001:2.5394

	build/program --test-integral 4:0.0:4.0:0.0001:12.9816
	build/program --test-integral 5:-2.0:2.0:0.0001:-8.0
	build/program --test-integral 6:0.5:2.5:0.0001:1.6094