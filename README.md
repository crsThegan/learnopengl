# Learning OpenGL
----
This is my implementation of a basic renderer, built while reading LearnOpenGL's 'Getting Started' chapter.

It requires following dependencies:
* OpenGL >= 3.3
* GLAD
* GLFW
* stb/stb_image.h

To build, use the following commands *once* in the root directory of the cloned repo:
```bash
mkdir build
cd build
cmake ..
make
```
Now you've got the executable in the *build* directory. 
To run, ensure that it is your working directory and use the following command:
```
./OpenGLTest
```
