// Developed by Kelin.Lyu.
#include "node.hpp"
Node::Node() {
    this->hasCamera = false;
    this->position = vec3(0.0f);
    this->eulerAngles = vec3(0.0f);
    this->scale = vec3(1.0f);
    this->isHidden = false;
}
void Node::loadGeometry(string file) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(Engine::main->programDirectory + file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(scene == NULL || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        assert(false);
        return;
    }
    this->processNode(scene->mRootNode, scene);
}
void Node::setCamera(float field, float near, float far) {
    this->hasCamera = true;
    this->cameraField = field;
    this->cameraNear = near;
    this->cameraFar = far;
}
void Node::render() {
    if(this->isHidden) {
        return;
    }
    for(unsigned int i = 0; i < this->geometries.size(); i = i + 1) {
        this->geometries[i]->render(this->getModelTransform());
    }
}
void Node::processNode(aiNode *node, const aiScene *scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i = i + 1) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->geometries.push_back(this->generateGeometry(mesh, scene));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i = i + 1) {
        this->processNode(node->mChildren[i], scene);
    }
}
Geometry* Node::generateGeometry(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    for(unsigned int i = 0; i < mesh->mNumVertices; i = i + 1) {
        Vertex vertex;
        vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        if(mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        if(mesh->mTextureCoords[0]) {
            vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }else{
            vertex.uv = vec2(0.0f);
        }
        vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; i = i + 1) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j = j + 1) {
            indices.push_back(face.mIndices[j]);
        }
    }
    return(new Geometry(vertices, indices));
}
mat4 Node:: getModelTransform() {
    mat4 translateMatrix = glm::translate(mat4(1.0f), this->position);
    mat4 rotateMatrix = glm::eulerAngleXYX(this->eulerAngles.x, this->eulerAngles.y, this->eulerAngles.z);
    mat4 scaleMatrix = glm::scale(mat4(1.0f), this->scale);
    return(translateMatrix * rotateMatrix * scaleMatrix);
}
vec3 Node::getWorldUp() {
    return(vec3(0.0f, 1.0f, 0.0f));
}
vec3 Node::getFront() {
    vec3 vector;
    vector.x = cos(radians(this->eulerAngles.y)) * cos(radians(this->eulerAngles.x));
    vector.y = sin(radians(this->eulerAngles.x));
    vector.z = sin(radians(this->eulerAngles.y)) * cos(radians(this->eulerAngles.x));
    return(vector);
}
vec3 Node::getRight() {
    return(normalize(cross(this->getFront(), this->getWorldUp())));
}
vec3 Node::getUp() {
    return(normalize(cross(this->getRight(), this->getFront())));
}
mat4 Node::getCameraProjectionTransform() {
    float ratio = (float)Engine::main->screenWidth / (float)Engine::main->screenHeight;
    return(perspective(this->cameraField, ratio, this->cameraNear, this->cameraFar));
}
mat4 Node::getCameraViewTransform() {
    return(lookAt(this->position, this->position + this->getFront(), this->getUp()));
}
Node::~Node() {
    for(unsigned int i = 0; i < this->geometries.size(); i = i + 1) {
        delete(this->geometries[i]);
    }
    this->geometries.clear();
}
