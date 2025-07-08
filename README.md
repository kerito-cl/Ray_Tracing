
# Ray Tracing Project

## Overview
This project is a CPU-based ray tracer implemented in C, inspired by the ["Ray Tracing in One Weekend"](https://raytracing.github.io/books/RayTracingInOneWeekend.html) book series. The program reads scene descriptions from .rt files and renders them using ray tracing techniques, with real-time display through MLX42 and optional multi-threading support for improved performance.


Here's your refined README.md with all the updated features and scene file format specifications:

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

#ambient light          intensity (0 - 1)       (R,  G,   B)
A                       0.2                     175,175,255


#camera      position(x,y,z)   camera direction       field of view
C            0,2,15             0,-0.1,-1               120

#light      light position(x,y,z)        intensity (0 to 1)       (R,  G,   B)
L           10,10,10                         0.5                     255,225,225

#plane      position(x,y,z)    normalized vector            R,  G,  B         #METAL
pl          0,-5,0               0,1,0                       255,255,255         M

#sphere     position(x,y,z)    diameter         R,  G,  B         #GLASS   
sp          0,-2,-10                6          255,134,10          G           

#cylinder    position(x,y,z)   (normalized vector)        (diameter)  (HEIGHT)       (R,  G,  B)         #DIFFUSE     #TEXTURE IMAGE (needs to start by F:)
cy          -10,-5,0            0,1,0                       6           8               255,134,10          D           F:./scenes/textures/ball2.png


#box       Height position(x,y,z)             width position(x,y,z)       (R,  G,  B)         #DIFFUSE     #TEXTURE IMAGE (needs to start by F:)
bx          10,-5,3                            15,0,-2                     255,255,255          D            F:./scenes/textures/wood.png


#cone       #position(x,y,z)   (normalized vector)        (diameter)  (HEIGHT)       (R,  G,  B)         #DIFFUSE          #TEXTURE IMAGE (needs to start by F:)
cn          2,0,-3           0,-1,0                     6               8            255,134,10         D                   F:./scenes/textures/wall.png


```