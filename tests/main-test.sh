#!/bin/bash


echo "cleaning!";   ## Perform cleaning operations

rm bin/*;             ## Delete all binaries
rm data/Alpha/*;      ## Delete all alphamasks
rm data/Foreground/*; ## Delete all foreground images

g++ src/main.cpp src/image.cpp src/video.cpp src/video_matte_applier.cpp src/matte_applier.cpp  -Iinclude -o bin/main `pkg-config --cflags --libs opencv4`;

echo "testing still image matting!" ## self explanatory

./bin/main     image-matte \
               data/b0.png \    ## input various paths to binary!
               data/g0.png \
               data/b0_blank.png \
               data/g0_blank.png  \
               data/mattedImage.png \
               data/finalMask.png;

echo "tested still image matting! TEST SUCCESS IF NO ERRORS!";

echo "outputs written to  data/finalMask.png and data/mattedImage.png";

echo "testing video matting!";  ## self explanatory

./bin/main     video-matte \
               data/Videos/blue_.mp4  \ ## input various paths to binary!
               data/Videos/green_.mp4 \
               data/b0.png   \
               data/g0.png   \
               data/Foreground  \
               data/Alpha    \
               data/Videos/final_matte.avi \
               0.01 0 1;

echo "tested video matting! TEST SUCCESS IF NO ERRORS!";

echo "outputs written to data/Foreground, data/Alpha  and data/Videos/final_matte.avi";
