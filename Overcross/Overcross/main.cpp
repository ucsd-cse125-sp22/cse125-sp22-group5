// Developed by Kelin.Lyu.

#include "Engine/engine.hpp"

int main(int argc, char** argv) {
    
    Engine* engine = new Engine("Engine", 1.0f, true, NULL, 1.0f / 60.0f);
    engine->hideMouseCursor();
    
    Node* cameraNode = new Node();
    cameraNode->setCamera(radians(60.0f), 0.1f, 1000.0f);
    cameraNode->position = vec3(5.0f, 1.0f, 5.0f);
    cameraNode->eulerAngles = vec3(0.0f, -90.0f, 0.0f);
    vec3 cameraTargetPosition = cameraNode->position;
    vec3 cameraTargetEulerAngles = cameraNode->eulerAngles;
    engine->addChild(cameraNode);
    engine->cameraNode = cameraNode;
    
    Texture* atlasD = new Texture("/Resources/Map/Textures/Atlas D.png", "diffuse", GL_REPEAT);
    Texture* glowsD = new Texture("/Resources/Map/Textures/Glows D.png", "diffuse", GL_REPEAT);
    Texture* gridsD = new Texture("/Resources/Map/Textures/Grids D.png", "diffuse", GL_REPEAT);
    
    Shader* atlasShader = new Shader("/Resources/Map/Shaders/Shader");
    Shader* glowsShader = new Shader("/Resources/Map/Shaders/Shader");
    Shader* gridsShader = new Shader("/Resources/Map/Shaders/Shader");
    
    atlasShader->addTexture(atlasD);
    glowsShader->addTexture(glowsD);
    gridsShader->addTexture(gridsD);

    Node* map = new Node();
    map->scale = vec3(0.2f);
    map->loadGeometry("/Resources/Map/Map.dae");
    map->geometries[0]->setShader(atlasShader);
    map->geometries[1]->setShader(glowsShader);
    map->geometries[2]->setShader(gridsShader);
    engine->addChild(map);
    
    while(engine->isRunning()) {
        if(engine->shouldUpdate()) {
            
            if(engine->input->wasKeyReleased(GLFW_KEY_ESCAPE)) {
                engine->terminate();
            }
            
            if(engine->input->isPressingKey(KEY_W)) {
                cameraTargetPosition += cameraNode->getFront() * 0.1f;
            }else if(engine->input->isPressingKey(KEY_S)) {
                cameraTargetPosition -= cameraNode->getFront() * 0.1f;
            }
            if(engine->input->isPressingKey(KEY_A)) {
                cameraTargetPosition -= cameraNode->getRight() * 0.1f;
            }else if(engine->input->isPressingKey(KEY_D)) {
                cameraTargetPosition += cameraNode->getRight() * 0.1f;
            }
            if(engine->input->isPressingKey(KEY_E)) {
                cameraTargetPosition += cameraNode->getUp() * 0.1f;
            }else if(engine->input->isPressingKey(KEY_Q)) {
                cameraTargetPosition -= cameraNode->getUp() * 0.1f;
            }
            cameraNode->position += (cameraTargetPosition - cameraNode->position) * 0.1f;
            
            vec2 mouseTranslation = engine->input->getMouseTranslation() * 0.1f;
            cameraTargetEulerAngles.y += mouseTranslation.x;
            cameraTargetEulerAngles.x -= mouseTranslation.y;
            cameraTargetEulerAngles.x = glm::max(-60.0f, glm::min(cameraTargetEulerAngles.x, 60.0f));
            cameraNode->eulerAngles += (cameraTargetEulerAngles - cameraNode->eulerAngles) * 0.2f;
        }
    }
    
    delete(engine);
    return(0);
}
