PROJECT_NAME = 3DViewer_v2.0
GIF_DIR = gif
BUILD_DIR = build
TEST_DIR = test
INSTALL_DIR = install

CXXFLAGS = -std=c++17 -Wall -Werror -Wextra $(shell pkg-config --cflags gtest)
LDFLAGS = $(shell pkg-config --libs gtest) -lgtest_main -fprofile-arcs -ftest-coverage

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	OPEN_CMD = xdg-open
	NO_ERR = --ignore-errors mismatch
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	NO_ERR = --ignore-errors inconsistent
endif


all: build run

install: build
	mkdir -p $(INSTALL_DIR)
	cp $(PROJECT_NAME) $(INSTALL_DIR)/


uninstall:
	rm -rf $(INSTALL_DIR)

run:
	./$(PROJECT_NAME)

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

clean: clean_gif uninstall
	rm -rf ./docs
	rm -rf ./tests *gcda *gcno report.info report.html
	rm -rf $(GIF_DIR)/libgif.a *.gz
	rm -rf $(BUILD_DIR) 3DViewer_v2* .qt CMakeFiles MyQtProject_autogen cmake_install.cmake CMakeCache.txt
	rm -rf .clang-format

dvi: clean
	@doxygen
	$(OPEN_CMD) docs/html/index.html

dist: clean
	cp -r ../src ../dist/
	cd ../dist && \
	tar -czvf ../src/$(PROJECT_NAME)-dist.tar.gz * && \
	cd ../src
	rm -rf ../dist 

check_clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cc *.h */*.cpp */*.c */*.h
	rm -rf .clang-format

format_clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cc *.h */*.cpp */*.c */*.h
	rm -rf .clang-format

test: clean
	g++ $(CXXFLAGS) ./*/*.cc model.cc $(LDFLAGS) -o tests
	./tests

gcov_report: test
	lcov --no-external -o report.info -c -d .
	genhtml -o report.html report.info
	rm -rf report.info ./tests *gcda *gcno
	$(OPEN_CMD) report.html/index.html

valgrind_test: clean
	@echo
	@echo Start valgrind
	@echo
	@g++ $(CXXFLAGS) ./*/*.cc model.cc $(LDFLAGS) -o tests
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s ./tests
