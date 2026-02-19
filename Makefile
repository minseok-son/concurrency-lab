# Shortcuts for common tasks
.PHONY: all build clean run

all: build

build:
	@mkdir -p build
	@cd build && cmake .. && make

clean:
	@rm -rf build
	@echo "Build directory removed."

run: build
	@./build/counter_bench