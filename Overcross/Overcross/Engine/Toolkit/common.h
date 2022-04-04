// Developed by Kelin.Lyu.
#ifndef common_h
#define common_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#ifdef _WIN32
	#include <direct.h>
	#define getcwd _getcwd
#elif
	#include <unistd.h>
#endif
#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "keys.h"
using namespace std;
using namespace glm;
#endif
