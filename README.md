# The Game
A voxel game made in C++ with GLFW. Inspired by: https://github.com/EvanatorM/ScuffedMinecraft.git.

## How to Use the Project

### Getting Started
The project comes with a Makefile in the root directory for make compatibility. After downloading and unzipping the project (if you have make for C++ installed), simply run ```cd <path_to_root_directory>``` in the terminal, and you will be able to use the Makfile and its custom commands. 

### Building the Project
To compile the project with Makefile, you need to first run ```make DEPENDS``` to construct the dependency files. After running this once, you can quickly run ```make``` in the root directory of the project to compile or recompile the project. Additionally, ```make run``` and ```make build``` can be used to compile and run and compile without .o files, respectively.

### Running the Project
After building the project, the project can be run from the `build.out` file. In the root directory, run ```make run``` to run the project or ```./build.out``` if you do not want to recompile any changes to the project. When started, the program will ask for a name for the save-file (using \"example\" will pull up an example save-file that comes preinstalled). If a save-file with this name is found it will then be loaded, if not, then it will also ask for a seed for the world, which can be left blank, and make a new save.

### Disclaimer
This project is still in early development. It may contain bugs or crash unexpectedly. If you find any errors please let me know, and I will attempt to fix them; however, I cannot guarantee a timeframe for hotfixes. Please note that some commits may contain compiler warnings that may prevent compilation depending on your compiler and what C and C++ versions you have installed.

#### Controls
This project closely resembles an early version of Minecraft creative mode with a free flying camera. The movement controls are quite simple: Use WASD, Space, and Left Shift to move around and Right Shift to sprint. The scroll wheel can be used to zoom in and out and pressing V resets the zoom. For interacting with the world, Left Click breaks a block and Right Click or Tab places the selected block. The selected block defaults to oak planks and can be set to any naturally generating block by looking at the block and pressing M or the Middle Mouse Button. Additionally, the numbers 0-9 can be used to reference the fixed hot-bar of not naturally generated blocks to improve the building experience until a better inventory and crafting system is added. The game can be saved at any time by pressing L, and the game also automatically saves your builds (but not your position) once they pass out of render. Finally, pressing Escape pauses the game and releases the mouse, and pressing Shift + Escape closes the game.

#### Saves
When running the game, you will always create a new save-file or load an existing one. These are located in ```<path_to_root_directory>/MinecraftClone/saves/``` and can be removed from or added into this folder as needed. Because these can build up quickly, there is a Makefile rule to delete a specific save file without opening the folder. To delete a save from the terminal: go to the root directory like normal and run ```make delete_<save_file_name>``` where any space in the save file name is replaced by an underscore (_). For example, ```make delete_example_copy``` would delete \"example copy\" or \"example_copy\". Note, when downloading the project, the `saves` folder will start with a save-file titled \"example\", which can be removed if desired.
