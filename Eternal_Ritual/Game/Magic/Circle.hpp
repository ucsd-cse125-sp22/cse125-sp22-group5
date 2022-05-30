//
//  Circle.hpp
//  Eternal_Ritual_Offline
//
//  Created by Zifan Zhang on 5/29/22.
//

#ifndef Circle_hpp
#define Circle_hpp

#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"

class Circle: public Node {
private:
    static bool loaded;
    static Node* metaCircle;
    static Texture* circleTexture;
public:
    Node* circle;
    glm::vec3 color;
    PBRShader* shader;
    void load();
    void setColor(glm::vec3 color);
    Circle* copy();
    Circle();
    ~Circle();
};

#endif /* Circle_hpp */
