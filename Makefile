
.PHONY: all build clean

build:
	cmake -B build -S .
	cmake --build build -j

clean:
	rm -rf build
