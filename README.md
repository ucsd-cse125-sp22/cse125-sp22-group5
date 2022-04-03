# Overcross - UCSD CSE125 Group5 Project
A 3D multiplayer FPS game...[More details coming soon!]

## Developers
Kelin Lyu (Deze Lyu), Felix Zhang (Futian Zhang), Jackie Li (Mengxuan Li), Kelvin Yu (Kangming Yu), and Zifan Zhang.

## Milestone #1
A simple but powerful OpenGL engine prototype has been developed!
![screenshot1](https://github.com/ucsd-cse125-sp22/cse125-sp22-group5/blob/main/Screenshots/Screenshot1.png?raw=true)
Here is a quick tutorial:
### Requirements
- First, create a new C++ project. You need to link the GLFW, GLEW, GLM libraries, and the Assimp library for loading models.
- Next, add the Engine folder (Overcross/Overcross/Engine) and all the files inside to your project.
- Then, prepare your game assets. Since our project uses PNG image files and DAE 3D model files, only these formats are tested. After that, you need to put all the assets under the same directory as the executable. You can either do that manually or write a short script that copies the resources before building the executable. **The engine only accepts the relative path of the executable when loading assets! If you use an absolute path, the engine cannot find the file!** For example, in our project, we copy the Resources folder under /Overcross/Overcross/ to the executable's directory, and every time we load a texture or a model, the relative path we use starts with /Resources/.
- Finally, include the engine. This is probably the only library you need for the project because many system libraries are already included!
```
#include "Engine/engine.hpp"
```
### Creating a Window
To create a window, you first need to create an engine object:
```
Engine* engine = new Engine("Engine", 1.0f, true, NULL, 1.0f / 60.0f);

// parameters: 
// - the window's title;
// - the resolution scaler based on the screen's resolution
// - whether to use fullscreen
// - relative path to the window's icon file (for Windows)
// - the desired fps
```
After that, create a render loop:
```
while(engine->isRunning()) {
    if(engine->shouldUpdate()) {
    
        // all your game logic should be here!
        // coding outside the if statement may result in undefined behavior!
        
        // termination:
        if(engine->input->wasKeyReleased(GLFW_KEY_ESCAPE)) {
            engine->terminate();
        }
    }
}
```
Finally, delete the engine and free up the memory:
```
delete(engine);
```
That's it! There are also plenty of helper functions for hiding and showing the cursor and changing the window's resolution, etc. Please check the Engine.hpp file.
### Interactions
It is extremely easy to handle user inputs!
For detecting continuous keyboard inputs, use:
```
if(engine->input->isPressingKey(KEY_W)) {
    // move forward!
}
```
For detecting key press or release only **once**, use:
```
// if(engine->input->wasKeyPressed(KEY_ESCAPE)) {...}
if(engine->input->wasKeyReleased(KEY_ESCAPE)) {
    engine->terminate();
}
```
You can also get the duration since the time when the state of a key changed:
```
// first, you need to get the current time from the engine:
double currentTime = engine->getTime();

// then, let's print out how long the user has been pressing the space bar:
if(engine->input->isPressingKey(KEY_SPACE)) {
    double duration = engine->input->getKeyDuration(KEY_SPACE, currentTime);
    cout << "You have been holding space for " << duration << "s." << endl;
}
```
If you are implementing a text box, using the methods above for text input might be complex. Therefore, you can use the following function that returns the recently pressed key's character. After getting the character, the engine reset it to the empty string. Note that this character will be capitalized if the user is holding shift.
```
string character = engine->input->getLastPressedCharacter();
if(character.length() > 0) {
    cout << "You typed [" << character << "]." << endl;
}
```
Convenient, isn't it? You can also detect mouse clicks just like the keyboard events. You just need to replace the key's name with MOUSE_BUTTON_LEFT, MOUSE_BUTTON_RIGHT, or MOUSE_BUTTON_MIDDLE.
To get the mouse's position and translation after the previous frame, use:
```
vec2 position = engine->input->getMousePosition();
vec2 translation = engine->input->getMouseTranslation();
```
And you can also get the acceleration of the mouse's scroll wheel by using:
```
float acceleration = engine->input->getScrollWheelAcceleration();
```
Currently, these are all the interactions that have been implemented.
### Rendering
Now, you probably want to render something on the screen. First, you need to create an empty node and add it to the engine:
```
Node* node = new Node();
engine->addChild(node);
```
**Make sure to attach the node to the engine using the engine's addChild method.**
Note that currently, I haven't developed the scene graph yet, so all the nodes will be added directly to an array of the engine. After you add the node, you can adjust its position, rotation, and scale:
```
node->position = vec3(5.0f, 1.0f, 5.0f);
node->eulerAngles = vec3(0.0f, -90.0f, 0.0f);
node->scale = vec3(0.5f);
```
If you want to use your node as a camera, write:
```
node->setCamera(radians(60.0f), 0.1f, 1000.0f);
// parameters: 
// - field of view
// - zNear
// - zFar

engine->cameraNode = node;
```
**You must set the engine's cameraNode to activate the camera. Otherwise, nothing will be rendered.**
Now, you probably want to show something on the screen. The structure of the engine is the following:
```
Textures - Shaders - Geometrys - Nodes - Engine
```
So, to load and display a 3D model, you have to do the following. First, prepare all the texture files required by a shader:
```diff
- Texture* texture = new Texture("/Resources/Map/Textures/Atlas D.png", "diffuse", GL_REPEAT);
- // parameters:
- // - path to the file
- // - the name of the uniform variable in the shader
- // - wrap mode
+ Texture* texture = new Texture("/Resources/Map/Textures/Atlas D.png", GL_REPEAT);
+ // parameters:
+ // - path to the file
+ // - wrap mode
```
Then, you can create a shader object and load the shader files:
```
// load the Shader.vs and Shader.fs files under /Resources/Map/Shaders/:
Shader* shader = new Shader("/Resources/Map/Shaders/Shader");
```
Note that the shader object requires the vertex shader and the fragment shader to have the same name and be in the same directory. Then, you can bind some uniform values using the provided helper methods, for example:
```
shader->setFloat("intensity", 0.5f);
shader->setVec3("objectColor", vec3(1.0f, 0.5f, 0.3f));
```
And load the texture objects to the shader object:
```diff
- shader->addTexture(texture);
+ shader->addTexture(texture, "diffuse");
+ // parameters:
+ // - the texture object
+ // - the name of the uniform variable
```
For the next step, you can directly load the 3D model to the node, skipping the step of creating the geometry objects. The reason behind this is that loading a node automatically constructs them for you:
```
node->loadGeometry("/Resources/Map/Map.dae");
```
The next step is the most important. You have to assign the shaders to the geometries created by the node after loading the 3D model. If your 3D model file contains only one node with a single material, then you just need to assign the shader to the first geometry of the node:
```
node->geometries[0]->setShader(shader);
```
Otherwise, if you have multiple nodes or multiple materials, you must assign all the subsequential geometries. The engine ignores the geometries without a shader. After these steps, you should see the model on the screen if it has a proper position. Congrats.
