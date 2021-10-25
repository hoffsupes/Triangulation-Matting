# Triangulation Matting

Does Triangulation matting using blue and green background images. Two images of the same object are taken with different backgrounds, blue and green.
This is used along with two blank images of same background to infer values of the alphamask and foreground which when blended together with the
given background produce the images of the object (on the different backgrounds).

Can be thought of as:

BlueBG_Object_image = alpha * foreground + (1 - alpha)* blank_Blue_Object_background
GreenBG_Object_image = alpha * foreground + (1 - alpha)* blank_Green_Object_background

This produces six equations per pixel (three colors, RGB considered in two images at every pixel), which is formulated as:

 A*X = B

and solution is X = A_inverse*b, where X contains values of alphamask and image

Has capability to process videos (read and write) and to do this matting on every frame of a video.

The original green and blue background video which I originally used a long time ago is sadly lost ( :( ) but I have created two artificial videos
from the still images I had. These artifical videos are simply repitions of the same image over a thirty second period, sampled at 30 frames per second.

To view only matting results, use `make matte_test` after the install procedures below as the `main` app performs the cumulation of everything (Video Matting)

Video files may be very slow to process depending on your system which is why the scale parameter has been provided.

#### Installation

1. Install openCV: `sudo apt install libopencv libopencv-dev`
2. Install dependencies as seen [here](https://linuxize.com/post/how-to-install-opencv-on-ubuntu-18-04/)
3. Windows users see [this])(https://learnopencv.com/install-opencv-on-windows/) or use chocolatey
4. Install ffmpeg: `sudo apt install ffmpeg`
5. Clone this repo: `git clone https://github.com/hoffsupes/Triangulation-Matting.git`


#### Usage

To perform video matting, traverse to the root of the project directory and run:

1. `g++ src/main.cpp src/image.cpp src/video.cpp src/video_matte_applier.cpp src/matte_applier.cpp  -Iinclude -o bin/main `pkg-config --cflags --libs opencv4`;`

2. ```./bin/main path_to_blue_video \

               path_to_green_video \

               path_to_green_still_image \

               path_to_green_still_image \

               path_to_green_foreground_image_folder \

               path_to_green_alpha_image_folder \

               image_scaling_value_for_faster_processing \

               0_or_1_for_video_display_only \

               0_or_1_to_display_output_or_not \

               ```
#### Test Suites

Makefile tests are included, to run them traverse to the root of the directory and execute accordingly as given below:

1. `make test-all`:
    To test everything, all features

2. `make video_matte-test`:
    To test video matting

3. `make video-test`:
    To test video reading and writing

4. `make matte-test`:
    To test video reading writing


There are tests for other capabilities, (please use a shell to do this or look into installing one first) to use them please type make, press space and press tab to see all options available.
