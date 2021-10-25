######################################
######################################
######################################
### Very Simple makefile
######################################
######################################
######################################

video_matte-test:
	rm bin/video_matte_test; g++ tests/video_matte-test.cpp src/image.cpp src/video.cpp src/video_matte_applier.cpp src/matte_applier.cpp  -Iinclude -o bin/video_matte_test `pkg-config --cflags --libs opencv4`;./bin/video_matte_test

video-test:
	rm bin/video_test; g++ tests/video-test.cpp src/image.cpp src/video.cpp -Iinclude -o bin/video_test `pkg-config --cflags --libs opencv4`;./bin/video_test

matte-test:
	rm bin/matte_test; g++ tests/matte-test.cpp src/image.cpp src/matte_applier.cpp  -Iinclude -o bin/matte_test `pkg-config --cflags --libs opencv4`;./bin/matte_test

image-test:
	rm bin/image_test; g++ tests/image-test.cpp src/image.cpp  -Iinclude -o bin/image_test `pkg-config --cflags --libs opencv4`;./bin/image_test

utilities-test:
	rm bin/utility_test; g++ tests/mini_utilities-test.cpp -Iinclude -o bin/utility_test `pkg-config --cflags --libs opencv4`;./bin/utility_test

tester-test:
	rm bin/tester_test; g++ tests/tester-test.cpp -Iinclude -o bin/tester_test `pkg-config --cflags --libs opencv4`;./bin/tester_test

test-all: tester-test utilities-test image-test matte-test video-test video_matte-test ## run complete test suite

clean:
	rm bin/*;
	rm data/Alpha/*;
	rm data/Foreground/*;