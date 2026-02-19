# Variables
BUILD_DIR = build
COUNTER_EXE = $(BUILD_DIR)/counter_bench
LL_EXE = $(BUILD_DIR)/ll_bench

# Shortcuts
.PHONY: all build clean run run_ll help

all: build

# Standard build process
build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && make

# Wipe everything for a fresh start
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Build directory removed."

# Run the counter benchmark
# Note: This passes "4" as a default thread count argument
run: build
	@echo "Running Counter Benchmark..."
	@./$(COUNTER_EXE) 4

# Run the linked list benchmark
run_ll: build
	@echo "Running LinkedList Benchmark..."
	@./$(LL_EXE) 4

# A nice way to see what you can do
help:
	@echo "Available commands:"
	@echo "  make build   - Create build dir and compile"
	@echo "  make run     - Run Counter benchmark (default 4 threads)"
	@echo "  make run_ll  - Run LinkedList benchmark (default 4 threads)"
	@echo "  make clean   - Remove build artifacts"