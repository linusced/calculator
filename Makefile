setup:
	rm -rf build
	mkdir build
	cd build && conan install .. & cd ..
