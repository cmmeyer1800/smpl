
.PHONY: all build clean

build:
	cmake -B build -S .
	cd build && make

clean:
	rm -rf build
