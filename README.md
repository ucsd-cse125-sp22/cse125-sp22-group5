# Overcross - UCSD CSE125 Group5 Project
A 3D multiplayer FPS game...[More details coming soon!]

## Developers
Kelin Lyu (Deze Lyu), Felix Zhang (Futian Zhang), Jackie Li (Mengxuan Li), Kelvin Yu (Kangming Yu), and Zifan Zhang.

## Milestone #1
A simple but powerful OpenGL engine prototype has been developed!
![screenshot1](https://github.com/ucsd-cse125-sp22/cse125-sp22-group5/blob/main/Screenshots/Screenshot1.png?raw=true)
Here is a quick tutorial:
#### Requirements
- First, create a new C++ project. You need to link the GLFW, GLEW, GLM libraries, and the Assimp library for loading models.
- Next, add the Engine folder (Overcross/Overcross/Engine) and all the files inside to your project.
- Then, prepare your game assets. Since our project uses PNG image files and DAE 3D model files, only these formats are tested. After that, you need to put all the assets under the same directory as the executable. You can either do that manually or write a short script that copies the resources before building the executable. **The engine only accepts the relative path of the executable when loading assets! If you use absolute path, the engine cannot find the file!**
- Finally, include the engine. This is probably the only library you need for the project because many system libraries are already included!
```
#include "Engine/engine.hpp"
```
#### Creating a Window
To create a window, you first need to create an engine object:
```
Engine* engine = new Engine("Engine", 1.0f, true, NULL, 1.0f / 60.0f);

// parameters: 
// - the window's title;
// - the resolution scaler based on the screen's resolution
// - whether to use fullscreen
// - relative path to the window icon
// - fps
```
After that, create a render loop:
```
while(engine->isRunning()) {
    if(engine->shouldUpdate()) {
        // all your game logic should be here!
        // coding outside the if statement results in unknown behavior...
    }
}
```
Finally, delete the engine and free up the memory:
```
delete(engine);
```
That's it! There are also plenty of helper functions for hiding and showing the cursor and changing the window's resolution and so on. Please check the Engine.hpp file.
#### Interactions
It is extremely easy to handle user inputs!
