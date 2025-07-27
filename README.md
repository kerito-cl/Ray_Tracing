
# Ray Tracing Project

## Overview
This project is a CPU-based ray tracer implemented in C, inspired by the ["Ray Tracing in One Weekend"](https://raytracing.github.io/books/RayTracingInOneWeekend.html) book series. The program reads scene descriptions from .rt files and renders them using ray tracing techniques, with real-time display through MLX42 and optional multi-threading support for improved performance.


## Features


- **Real-time Display**: Uses MLX42 library for interactive rendering
- **Geometric Primitives**: Spheres, boxes, cones, cylinders, and planes
- **Material Types**: Diffuse, metal, and glass materials
- **Textures**: Support for image-based textures on objects
- **Scene Files**: Custom `.rt` file format for scene description
- **Lighting**: Ambient light and point light sources
- **Parallelization**: Optional multi-threading support (bonus feature)

## Building
```bash
make        # Builds the standard version
make bonus  # Builds the multi-threaded version
```

## Usage
```bash
./miniRT scenes/example.rt
```

## .rt File Format Specification
The scene description file uses the following format:


```

#ambient light          Intensity (0 - 1)       (R,  G,   B)
A                       0.2                     175,175,255


#camera      Position(x,y,z)    Camera Direction        Field of view
C            0,2,15             0,-0.1,-1               120

#light      Position(x,y,z)        Intensity (0 to 1)       (R,  G,   B)
L           10,10,10                      0.5               255,225,225

#plane      Position(x,y,z)      Normalized Vector            R,  G,  B         #Metal
pl          0,-5,0               0,1,0                       255,255,255         M

#sphere     Position(x,y,z)     Diameter         R,  G,  B         #Glass 
sp          0,-2,-10               6             255,134,10          G           

#cylinder   Position(x,y,z)    Normalized Vector        Diameter     Height            (R,  G,  B)         #Diffuse     #Texture Image (needs to start by F:)
cy          -10,-5,0            0,1,0                       6           8               255,134,10          D           F:./scenes/textures/ball2.png


#box        Height position(x,y,z)             Width Position(x,y,z)       (R,  G,  B)         #Diffuse      Texture Image (needs to start by F:)
bx          10,-5,3                            15,0,-2                     255,255,255          D            F:./scenes/textures/wood.png


#cone       position(x,y,z)     normalized vector     Diameter         Height       (R,  G,  B)         Diffuse             TEXTURE IMAGE (needs to start by F:)
cn          2,0,-3              0,-1,0                   6               8           255,134,10          D                   F:./scenes/textures/wall.png





```
---

<p align="center"><strong>Made by Matias Quero & Daniel Xifeng</strong></p>
