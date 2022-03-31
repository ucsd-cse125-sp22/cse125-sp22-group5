# Overcross - UCSD CSE125 Group5 Project
A 3D multiplayer FPS game that gives players the ability to open portals and manipulate gravity.

## Group Members
Kelin Lyu (Deze Lyu), Felix Zhang (Futian Zhang), Jackie Li (Mengxuan Li), Kelvin Yu (Kangming Yu), and Zifan Zhang.

## Project Description
We are developing a 3D multiplayer FPS game, similar to CSGO and Overwatch. The game is team-based and round-based. The players must cooperate with their teammates and eliminate the entire enemy team to win in every round. The team that wins the most rounds wins the game, and the other side loses. The most exciting part of our game is that each player can shoot both bullets and portals. Each player can create up to two portals. Players can see through the portals to observe the other side of the map. Then, they can shoot or move through the portals created by themselves, their teammates, and even their enemies. In addition to the portals, each player is equipped with a pair of gravity boots, allowing them to walk on any surface and change their orientation after moving from one surface to another. For a complete list of the game’s features, please see the Development logs below, which sorts the features we are about to make with priority from high to low.

## Group Management
We want every group member to contribute ideas and creativity to this project. Together, we decide which functionality we need to implement next, and when disagreements arise, we will resolve them through voting. We will discuss who should take a task depending on each member's schedule to make the work flexible for everyone. And finally, we will write on a google doc first to keep track of our progress during the week and then generate a weekly report from that document on the weekend.

## Project Development
For our group, there is no specific role assignment because we want everyone to be able to contribute. So, for example, after we decide on a new goal, everyone can volunteer to take the task depending on one's understanding of the work and one's schedule. And after finishing a task, one should update the project document as soon as possible following the format we discussed.

## Development Tools
- Xcode and Visual Studio: We will first finish the project using Xcode, and then migrate it to Visual Studio.
- Unity: We will mainly use Unity as a map creation tool. Also, we will take advantage of the Unity Asset Store to purchase 3D models.
- Maya, Photoshop, Animate, and Logic: These programs are for artwork and music.

## Development Logs

### Progress #1
#### Task
Create a new Xcode project and include the OpenGL libraries. Silence the OpenGL warnings and write a script that copies the Resources folder to the build directory upon running the project so that the program can locate the assets of the game. Finally, write a simple OpenGL program that displays a rotating cube.
#### Author
Kelin
#### Requirements
The following steps are needed before you run the code.
1. Google and install Homebrew.
2. Open the terminal - brew install glfw3 - brew install glew - brew install glm.
3. Open Xcode. File - New - Project - macOS - Command Line Tool - Name: "Overcross", Team: "None", Organization: "UCSD-CSE125-Group5", Language: "C++" - Next - Select and open the master folder - Uncheck "Create Git Repo..." - Close the project - Rename the project to "Overcross[Xcode]" in finder - Open the project again.
4. Click the project in the project navigator - Build Settings - Click "All" and "Combined" on the top - Search Paths - Header Search Paths: "/opt/homebrew/include/" (non-recursive) - Library Search Paths: first add "/opt/homebrew/Cellar/glfw/3.3.6/lib", then "/opt/homebrew/Cellar/glew/2.2.0_1/lib", and finally "/opt/homebrew/Cellar/glm/0.9.9.8/lib" (non-recursive)
5. Click the project in the project navigator - Build Options - Validate Workspace - Ignored Frameworks: "OpenGL".
6. Click the project in the project navigator - Apple Clang - Language - Modules - Documentation Comments (search "Documentation" if you cannot find it) - No.
7. Click the project in the project navigator - Build Phases - Link Binary With Libraries - Add: "OpenGL.framework" - Then continue to add the other frameworks through "Add Other..." - "libglfw.3.3.dylib" (located in /opt/homebrew/Cellar/glfw/3.3.6/lib) - "libGLEW.2.2.0.dylib" (located in /opt/homebrew/Cellar/glew/2.2.0_1/lib).
8. Click the project in the project navigator - Build Phase - Click the + icon - New Run Script Phase - Drag the new phase to the top - Write code: "cp -R XXX ${BUILT_PRODUCTS_DIR}" (where XXX is the absolute path to the "Resources" folder).
