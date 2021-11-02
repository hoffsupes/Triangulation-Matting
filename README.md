# Triangulation Matting: Foregound and Alphamask extraction for Still Images and Videos

Does triangulation matting using blue and green background images (and videos). Two images of the same object are taken with different backgrounds, blue and green.
This is used along with two blank images of same background to infer values of the alphamask and foreground which when blended together with the
given (blank) background, produce the images of the object (on the different backgrounds). This alphamask and foreground can then be applied to other places or place the foreground in other images as needed. For this excercise, we're only interested in extracting the foreground and alphamask (although they can be used later). All images and videos processed focus on this functionality (alphamask and foreground extraction) and the results reflect as such. This is a rework of some development done for a final course project where my contribution was to obtain foreground and alphamask, another person created the green and blue videos using source filmmaker and one more person used the alphmask to blend them onto a new image(s).

This can be thought of as:

**BlueBackgroundForegroundImage = alpha*foreground + (1 - alpha) * BlankBlueBackgroundImage**

**GreenBackgroundForegroundImage = alpha*foreground + (1 - alpha) * BlankGreenBackgroundImage**

or on being further solved, leads to a set of linear equations which can be represented as:

![matting](https://user-images.githubusercontent.com/28497335/138963602-8a587a14-66e9-44fa-8e72-17e2481bdc2a.png)

(Credit to [brown university](http://cs.brown.edu/courses/cs129/results/final/njooma/) for the above visual)

Has capability to process videos (read and write) and to do this matting on every frame of a video and on still images.

The original green and blue background videos which I originally used a long time ago are sadly lost ( :( ) but I have created two artificial videos
from the still (foreground with relevant, blue or green background color) images I still had. These artificial videos are simply repetitions of the same image over a thirty second period, sampled at 30 frames per second. When matting is run using them though, due to certain discrepancies in image quality when performing that image to video conversion (the background colors end up getting varied and destroyed due to the loss in quality, hence a "mismatch" between the  background values in the video frames to that in the original blank images I have, i.e. the equations you see above assume that we're using the same background values at a time, `object_on_blue_background`-`blank_blue_background` or `object_on_green_background`-`blank_green_background` which is not happening anymore), the actual alpha matte and matted frame from the per frame of the video vary from when those same still images (used to produce the videos) are independently used to create the matte. This is very interesting and you can even see this when you try out the tests.

I've modeled my own very simple `Image` class which is used by a `Video` class. The ``Video`` class has capabilities to very simply read and write videos all in one place.
That includes releasing the actual object files after use which is very important in a language like C++. I also create a Matting (`Matte`) class which relies on the `Image` class to do the Matting. The Matting class is then extended to a `VideoMatte` class (which inherits all the properties of the Matting class) that adds capability to read the blue and green background videos, and write the result video; all using capabilities of the `Video` class. Although point to note, that this is in no way a critique of the openCV library which absolutely amazing and this work only seeks to make the methods which would typically be relevant (or more commonly used in regards to it) to this specific problem(i.e. video matting) simpler to use and encapsulated closely with the data it would work on. The numerosity of OpenCV is what make it quite powerful in terms of the massive number of features it offers.

Supports both `Still Image Matting` as well as `Video Matting`.

Video files may be very slow to process depending on your system which is why the scale parameter has been provided for (faster) testing purposes.

OpenCV is still seemingly limited (or at least is a bit problematic in) writing anything (in terms of the `VideoWriter` object writing the videos) other than ".avi" out of the box (if you install from the repo), so please use avi formats to write output files.

This work was originally done towards a final project in a Computer Vision course. Goal was to take videos generated by another team member (who used team fortress 2 and the source filmmaker) to capture footage. I wrote the code in C++ (I chose C++ since I knew we were processing video files and the speed obtained by it would be helpful vs using something like python; plus I was already doing a lot of my work in C++ for that course already) to do triangulation matting.

## Installation


1. Install dependencies as seen [here](https://linuxize.com/post/how-to-install-opencv-on-ubuntu-18-04/)
2. Install openCV: `sudo apt install libopencv libopencv-dev`, this codebase requires **OpenCV version 4**.
3. Windows users see [this](https://learnopencv.com/install-opencv-on-windows/) or use chocolatey. Mac users see [this](https://www.pyimagesearch.com/2018/08/17/install-opencv-4-on-macos/).
4. Install ffmpeg: `sudo apt install ffmpeg`. Windows users, please see [this](https://www.wikihow.com/Install-FFmpeg-on-Windows). Mac users, [this](http://jollejolles.com/install-ffmpeg-on-mac-os-x/).
5. Clone this repo: `git clone https://github.com/hoffsupes/Triangulation-Matting.git`


## Usage

### Still Image Matting

1. To perform still image matting, traverse to the root of the project directory and run:

```
g++ src/main.cpp src/image.cpp src/video.cpp src/video_matte_applier.cpp src/matte_applier.cpp  -Iinclude -o bin/main `pkg-config --cflags --libs opencv4`;
```
2. Next run the `main` binary which has been created in the `bin/` folder.

```      
./bin/main     image-matte \
               path_to_blue_image \
               path_to_green_image \
               path_to_blue_still_image \
               path_to_green_still_image \
               path_to_foreground_image \
               path_to_alpha_image \
```

The above options are explained as follows:

1. **path_to_blue_image**: Relative path to the blue background image which is input
2. **path_to_green_image**: Relative path to the green background image which is input
3. **path_to_blue_still_image**: Relative path to the blank blue still image which is input
4. **path_to_green_still_image**: Relative path to the blank green still image which is input
5. **path_to_foreground_image**: Relative path to the foreground image to be output
6. **path_to_alpha_image**: Relative path to the alpha mask image to be output

Example:

```
./bin/main     image-matte \
               data/b0.png \
               data/g0.png \
               data/b0_blank.png \
                 data/g0_blank.png  \
               data/mattedImage.png \
               data/finalMask.png
```

### Video Matting

1. To perform video matting, traverse to the root of the project directory and run:

```
g++ src/main.cpp src/image.cpp src/video.cpp src/video_matte_applier.cpp src/matte_applier.cpp  -Iinclude -o bin/main `pkg-config --cflags --libs opencv4`;
```
2. Next run the `main` binary which has been created in the `bin/` folder.

```      
./bin/main     video-matte \
               path_to_blue_video \
               path_to_green_video \
               path_to_blue_still_image \
               path_to_green_still_image \
               path_to_foreground_image_folder \
               path_to_alpha_image_folder \
               mattedvideopath \
               image_scaling_value_for_faster_processing \
               0_or_1_for_video_display_only \
               0_or_1_to_display_output_or_not
```

The above options are explained as follows:

1. **path_to_blue_video**: Relative path to the blue background video which is input
2. **path_to_green_video**: Relative path to the green background video which is input
3. **path_to_blue_still_image**: Relative path to the blank blue still image which is input
4. **path_to_green_still_image**: Relative path to the blank green still image which is input
5. **path_to_foreground_image_folder**: Relative path to the foreground image folder to be output to, please dont include a '/' at the end. That is use `data/Foreground` instead of `data/Foregound/`
6. **path_to_alpha_image_folder**: Relative path to the alpha mask image folder to be output to, please dont include a '/' at the end. That is use `data/Alpha` instead of `data/Alpha/`
7. **mattedvideopath**: Output matted video path
8. **image_scaling_value_for_faster_processing**: Image scaling value, since matrix inverse per pixel is very computationally extensive, if you really wanted to test the whole video, or see this in action (!). Please use a lower value (range is between 0 - 1 ) e.g. 0.3 and this will scale or resize (downsample) your images down to a smaller size as per the scale given before doing trimat (the image intensity estimation process is even worse for something like Trimatting, which actually needs fine high quality per pixel values to give clean mattes -- you can see this if you try out `make matte-test` in the root directory to run the `matte_test.cpp` or look at the pre-rendered example images in the `data` folder) but this should suffice since a) the video data itself is only for testing b) this is only present should you want to see the code run to completion.
9. **0_or_1_for_video_display_only**: `0` or `1` numerical values, denoting `true` or `false` values to denote if you want to output (write output files) only videos or the intermediate files, foreground and alpha mask as well
10. **0_or_1_to_display_output_or_not**: `0` or `1` numerical values, denoting `true` or `false` values to denote if you want to display (i.e. display output of video frames as they are being processed) the matte and foreground images (in concatenated fashion) or not

Example:

```
./bin/main    video-matte \
              data/Videos/blue_.mp4  \
              data/Videos/green_.mp4 \
              data/b0.png   \
              data/g0.png   \
              data/Foreground  \
              data/Alpha    \
              data/Videos/final_matte.avi \
              0.01 0 1
```

## Test Suites

Makefile tests are included, to run them traverse to the root of the directory and execute accordingly as given below:

1. `make test-all`:
    Run complete test suite
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
8. `make main-test`:
    Test main.cpp
9. `make clean`:
    Cleans everything up, deletes content of `Foreground` and `Alpha` folder and even the `bin` folder

## Directory structure

1. `bin/`: Contains all the binary files
2. `data/`: Contains image files and subfolders `Videos`, `Foregound`, `Alpha` which contain other image and video files
3. `include/trimat`: Contains the header (class definition) in `.h` files
4. `src`: Contains member functions in `.cpp` files
5. `tests`: Contains all the tests

## Classes

The following classes were used towards this problem. Attempts have been made to take the most relevant (towards this specific endeavor) capabilities in OpenCV and bring them closer to the data that they would need to operate on. Obviously, OpenCV is much larger and more massive than this (as it covers a lot more immensity in terms of features offered across a wide variety of computer vision and even separate pattern recognition tasks, e.g. means to train classical machine learning models on data which might not have anything to do with computer vision) and these are select few capabilities which seemed most pertinent and also because it seemed that some additional capabilities of simplicity can be brought in for certain methods (i.e. as compared to using them out of the box from OpenCV vs modified here so that repeated use becomes easier).

![VideoMatter(2)](https://user-images.githubusercontent.com/28497335/139788267-1ce5df4d-2b57-46c1-9408-94341650979e.png)

1. `Image`: Creates a simple image class, which provides relatively easier access for commonly used OpenCV image functions, e.g. `imshow` is bundled in with the image container rather than separate, images can be easily allocated from files very simply etc..
2. `Video`: Models OpenCV's `VideoCapture` and `VideoWriter` in one place and simple method calls replace complicated allocation (e.g. `VideoCapture capture;`) and deallocation (`capture.release();`) and take care of some other things behind the scenes as well, to make their use simple and painless (e.g. reading videos is much simpler, at least better than typing in massive OpenCV VideoCapture or VideoWriter Properties like CAP_PROP_WHITE_BALANCE_BLUE_U, to just quickly get a property or read one frame).
3. `Matte`: Does matting using on `Image` objects
4. `VideoMatte`: Extends capabilities of the `Matte` class to handle Videos. Has functionality to contain green, blue (i.e. any background colors one and two relevant towards triangulation matting) and even writing the result videos.
5. `tester`: Provides simple testing capabilities
6. `miniUtilities`: Contains simple string utilities related to filehandling


##### Feedback

###### If you notice any inconsitencies or have any input to provide, feel free to reach out to me at dassgaurav93@gmail.com
