# Triangulation Matting

Does triangulation matting using blue and green background images. Two images of the same object are taken with different backgrounds, blue and green.
This is used along with two blank images of same background to infer values of the alphamask and foreground which when blended together with the
given background produce the images of the object (on the different backgrounds).

This can be thought of as:

**BlueBackgroundForegroundImage = alpha * foreground + (1 - alpha)* BlankBlueBackgroundImage**

**GreenBackgroundForegroundImage = alpha * foreground + (1 - alpha)* BlankGreenBackgroundImage**

This produces **six equations per pixel** (three colors, RGB considered in two images at every pixel), which is formulated as a system of linear equations:

**A*X = b**

and solution is

**X = A_inverse * b**

where X contains values of alphamask and image

Has capability to process videos (read and write) and to do this matting on every frame of a video.

The original green and blue background videos which I originally used a long time ago are sadly lost ( :( ) but I have created two artificial videos
from the still images I still had. These artifical videos are simply repitions of the same image over a thirty second period, sampled at 30 frames per second. When matting is run using them though, due to certain discrepencies in image quality when performing that image to video conversion (the background colors end up getting varied and destroyed due to the loss in quality, hence a "mismatch" from the original background images to the original blank images I have, i.e. the equations you see above assume that we're using the same background images at a time, object_on_blue_background-blank_blue_background or object_on_green_background-blank_green_background which is not happening anymore), the actual alpha matte and matted frame from the per frame of the video vary from when those same still images (used to produce the videos) are independently used to create the matte. This is very interesting and you can even see this when you try out the tests.

I've modeled my own very simple `Image` class which is derived by a `Video` class. The ``Video`` class has capabilies to very simply read and write videos all in one place.
That includes releasing the actual object files after use which is very important in a language like C++. I also create a Matting (`Matte`) class which relies on the `Image` class to do the Matting. The Matting class is then extended to a `VideoMatte` class (which inherits all the properties of the Matting class) that adds capability to read the blue and green background videos, and write the result video; all using capabilities of the `Video` class.

To view only matting results, use `make matte_test` after the install procedures below as the `main` app performs the cumulation of everything (Video Matting).

Video files may be very slow to process depending on your system which is why the scale parameter has been provided for testing purposes.

OpenCV is still seemingly limited (or at least is a bit problematic in) writing anything (in terms of the `VideoWriter` object writing the videos) other than ".avi" out of the box (if you install from the repo), so please use avi formats to write output files.

## Installation


1. Install dependencies as seen [here](https://linuxize.com/post/how-to-install-opencv-on-ubuntu-18-04/)
2. Install openCV: `sudo apt install libopencv libopencv-dev`
3. Windows users see [this](https://learnopencv.com/install-opencv-on-windows/) or use chocolatey. Mac users see [this](https://www.pyimagesearch.com/2018/08/17/install-opencv-4-on-macos/).
4. Install ffmpeg: `sudo apt install ffmpeg`. Windows users, please see [this](https://www.wikihow.com/Install-FFmpeg-on-Windows). Mac users, [this](http://jollejolles.com/install-ffmpeg-on-mac-os-x/).
5. Clone this repo: `git clone https://github.com/hoffsupes/Triangulation-Matting.git`


## Usage

1. To perform video matting, traverse to the root of the project directory and run:

```
g++ src/main.cpp src/image.cpp src/video.cpp src/video_matte_applier.cpp src/matte_applier.cpp  -Iinclude -o bin/main `pkg-config --cflags --libs opencv4`;
```

2. Next run the `main` binary which has been created in the `bin/` folder.

```      
./bin/main \
              path_to_blue_video \

               path_to_green_video \

               path_to_blue_still_image \

               path_to_green_still_image \

               path_to_foreground_image_folder \

               path_to_alpha_image_folder \

               image_scaling_value_for_faster_processing \

               0_or_1_for_video_display_only \

               0_or_1_to_display_output_or_not
```

The above options are explained as follows:

**path_to_blue_video**: Relative path to the blue background video

**path_to_green_video**: Relative path to the green background video

**path_to_blue_still_image**: Relative path to the blue still image

**path_to_green_still_image**: Relative path to the green still image

**path_to_foreground_image_folder**: Relative path to the foreground image folder, please dont include a '/' at the end. That is use `data/Foreground` instead of `data/Foregound/`

**path_to_alpha_image_folder**: Relative path to the alpha mask image folder, please dont include a '/' at the end. That is use `data/Alpha` instead of `data/Alpha/`

**image_scaling_value_for_faster_processing**: Image scaling value, since matrix inverse per pixel is very computationally extensive, if you really wanted to test the whole video, or see this in action (!). Please use a lower value (range is 0 - 1 ) e.g. 0.3 and this will scale or resize (downsample) your images down to a smaller size as per the scale given before doing trimat (the image intensity estimation process is even worse for something like Trimatting, which actually needs fine high quality per pixel values to give clean mattes -- you can see this if you try out `make matte-test` in the root directory to run the `matte_test.cpp` or look at the pre-rendered example images in the `data` folder) but this should suffice since a) the video data itself is only for testing b) this is only present should you want to see this thing run to completion.

**0_or_1_for_video_display_only**: `0` or `1` numerical values, denoting `true` or `false` values to denote if you want to output only videos or the intermediate files, foreground and alpha mask as well

**0_or_1_to_display_output_or_not**: `0` or `1` numerical values, denoting `true` or `false` values to denote if you want to display the matte and foreground values or not


## Test Suites

Makefile tests are included, to run them traverse to the root of the directory and execute accordingly as given below:

1. `make test-all`:
    To test everything, all features present within

2. `make video_matte-test`:
    To test the `VideoMatte` capabilties

3. `make video-test`:
    To test `Video` reading and writing

4. `make matte-test`:
    To test `Matte` application on an `Image`

5. `make image-test`:
    To test the capabilies of the `Image` class

6. `make utilities-test`:
    Test capabilites of the `miniUtilities` class

7. `make tester-test`:
    Test capabilites of the `tester` class

8. `make clean`:
    Cleans everything up, deletes content of `Foreground` and `Alpha` folder and even the `bin` folder

## Directory structure

`bin/`: Contains all the binary files

`data/`: Contains image files and subfolders `Videos`, `Foregound`, `Alpha` which contain other image and video files

`include/trimat`: Contains the header (class definition) in `.h` files

`src`: Contains member functions in `.cpp` files

`tests`: Contains all the tests
