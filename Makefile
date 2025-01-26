GIF_DIR = gif
BUILD_DIR = build
TEST_DIR = test

all: build run

run:
	./3DViewer_v2.0

build: clean build_libgif build_project

build_libgif: build_libgif_without_clean clean_gif

build_project:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make

build_libgif_without_clean:
	cd $(GIF_DIR) && cmake .
	cd $(GIF_DIR) && make

clean_gif:
	rm -rf $(GIF_DIR)/.qt $(GIF_DIR)/CMakeFiles $(GIF_DIR)/cmake_install.cmake $(GIF_DIR)/CMakeCache.txt $(GIF_DIR)/Makefile

clean: clean_gif
	rm -rf $(GIF_DIR)/libgif.a
	rm -rf $(BUILD_DIR) .qt CMakeFiles MyQtProject_autogen cmake_install.cmake CMakeCache.txt 3DViewer_v2.0
	rm -rf .clang-format

check_clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cc *.h */*.cpp */*.c */*.h
	rm -rf .clang-format

format_clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cc *.h */*.cpp */*.c */*.h
	rm -rf .clang-format

test: build_libgif
	cd $(TEST_DIR) && cmake .
	cd $(TEST_DIR) && make
	cd $(TEST_DIR) && ./test_viewer
	make clean_test_all

clean_test:
	rm -rf $(TEST_DIR)/.qt $(TEST_DIR)/CMakeFiles $(TEST_DIR)/test_viewer_autogen $(TEST_DIR)/cmake_install.cmake
	rm -rf $(TEST_DIR)/CMakeCache.txt $(TEST_DIR)/Makefile

clean_test_all: clean_test
	rm -rf $(TEST_DIR)/test_viewer

