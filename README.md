# Monet

Was going to be a a new open-source platform for creating GPU-based image-processing applications. I decided I couldn't be bothered re-inventing several different wheels when what I wanted to do was make a photo editing application to rival Lightroom and Photoshop. 

So, my basic goals for now are:
* Cross-platform
* Non-destructive
* GPU-based
* Extensible / Programmable for power users
* Nice collection of "presets" for the non-techies out there

## Current Status

Brand new, pretty much nothing to see here. Only builds on linux right now. Can demosaic images from Nikon cameras (and maybe others if they have exactly the same bayer filter), has hard-coded white-balance settings.

## Building

### Linux

Get these deps via your package manager:
* GLEW
* GLFW
* GLM
* libjpg
* zlib
* pugixml
* GTKMM 3.0
* meson
* ninja
* CMAKE
* make


Clone the source, then:

```
git submodule update --init
mkdir -p dep/rawspeed/build
pushd dep/rawspeed/build
cmake .. -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=RelWithDebInfo
make
popd

ninja -C build
```

To run:

```
./build/monet-photo
```
