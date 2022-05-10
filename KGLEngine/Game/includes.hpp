//
//  includes.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/29/22.
//

#ifndef includes_hpp
#define includes_hpp
#ifdef MAINPROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif

#include "../KGLEngine/Engine.hpp"
#include "./Character/CharNode.hpp"
#include "./Map/MapBoxObject.hpp"
#include "./Map/MapSystemManager.hpp"
#include "./Hitbox/Hitbox.hpp"
#include "./Hitbox/HitController.hpp"
#include "./Magic/BaseMagic.hpp"
#include "./Magic/Projectile.hpp"
#include "./Shader/AlphaShader.hpp"
class MapSystemManager;
EXTERN MapSystemManager* mapSystemManager;
EXTERN Engine* engine;
#endif /* includes_hpp */
