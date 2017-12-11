# Monet

Was going to be a a new open-source platform for creating GPU-based image-processing applications. I decided I couldn't be bothered re-inventing several different wheels when what I wanted to do was make a photo editing application to rival Lightroom and Photoshop. 

So, my basic goals for now are:
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
* BOOST   (I'm planning on getting rid of this one...)
* GTKMM 3.0


Clone the source, then:

```
./waf configure
./waf
```

To run:

```
./build/src/app/monet-photo
```
