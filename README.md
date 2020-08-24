# Minantium  
Voxel sandbox game similar to games such as Minetest. Forked from fogleman/craft  
## Building  
**WARNING: Compilation has only been tested on Linux**  

Meson is this project's build system. Dependencies are libcurl, glfw3, and glu.
### Linux:
Installing dependencies for Fedora:  

    dnf install libcurl-devel glfw-devel mesa-libGLU-devel
For Ubuntu/Debian based systems:

    sudo apt install libcurl4-openssl-dev libglfw-dev xorg-dev
Building:

    meson build; cd build; meson compile
The created executable must be placed in the same directory as *textures* and *shaders*.
