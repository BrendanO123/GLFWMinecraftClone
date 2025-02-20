# Minecraft Clone
An attempt to make a Minecraft clone in C++ with GLFW. Inspired by: https://github.com/EvanatorM/ScuffedMinecraft.git.

## How to Use the Project

### Getting Started
The project comes with a makefile in the root directory for make compatibility. After downloading and unzipping the project (if you have make for C++ installed), simply run ```cd <path_to_root_directory>``` in the terminal and you will be able to use the makfile and its custom commands. 

### Building the Project
To compile the project with makefile run ```make``` in the root directory of the project. Additionally, ```make build``` and ```make ruun``` can be used to compile without .o files, and compile and run, respectively.

### Running the Project
After building the project, the project can be run from the build.out file. In the root directory, run ```make run``` to run the project or ```./build.out``` if you do not want to recompile any changes to the project.

### Disclaimer
This project is still in early development. It may contain bugs, crashes, or even memory leaks. If you find any errors please let me know and I will attempt to fix them; however, I cannot guarantee a timeframe for hotfixes. Please note that some commits may contain compiler warnings that may prevent compilation depending on your compiler and what C and C++ versions you have installed.

#### Controls

This project closely resembles Minecraft spectator mode so the controls are quite simple: Use WASD, Space, and Left Shift to move around, Right Shift to sprint, scroll to zoom, and press V to reset the zoom. Additionally, Escape pauses the game and releases the mouse and Shift + Escape closes the game. 
