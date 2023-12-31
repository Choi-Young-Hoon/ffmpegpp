#!/bin/bash

root_path=$(pwd)
root_thirdparty_path=$root_path/thirdparty

function submodule_update {
    git submodule init 
    git submodule update
}

function sample_video_download {
    mkdir build
    cd build
    mkdir test
    cd test
    # sample video download
    wget -O sample.mp4 https://www.dwsamplefiles.com/?dl_id=351
    if [ $? -ne 0 ]; then
        exit -1
    fi
    cd $root_path
}

# submodule update
submodule_update

# sample video download
sample_video_download

