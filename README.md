# Monet

A new open-source platform for creating GPU-based image-processing applications. 

Ultimately I want to build a photo editing application to rival Lightroom and Photoshop. My basic goals for now are:
* Cross-platform
* Non-destructive
* GPU-based
* Extensible / Programmable for power users
* Nice collection of "presets" for the non-techies out there

## Current Status

Brand new, pretty much nothing to see here. Only builds on linux right now.

## Building

### Linux

Get the deps:
* Python
* GLEW
* GLFW
* GLM
* cpp-check
* libpng
* libtga
* BOOST


Clone the source, then:

```
./waf configure
./waf
```

To run:

```
./build/src/app/monet-photo
```
