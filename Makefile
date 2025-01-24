SUBDIR = gif
BUILD_DIR = build

all: clean build run

run:
	./3DViewer_v2.0

build: build_libgif build_project

build_libgif: build_libgif_without_clean clean_gif

build_project:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make

build_libgif_without_clean:
	cd $(SUBDIR) && cmake .
	cd $(SUBDIR) && make

clean_gif:
	rm -rf $(SUBDIR)/.qt $(SUBDIR)/CMakeFiles $(SUBDIR)/cmake_install.cmake $(SUBDIR)/CMakeCache.txt $(SUBDIR)/Makefile

clean: clean_gif
	rm -rf $(SUBDIR)/libgif.a
	rm -rf $(BUILD_DIR) .qt CMakeFiles MyQtProject_autogen cmake_install.cmake CMakeCache.txt 3DViewer_v2.0
