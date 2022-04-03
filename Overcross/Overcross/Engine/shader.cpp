// Developed by Kelin.Lyu.
#include "shader.hpp"
Shader::Shader(string shaderFile) {
    // read the files:
    string vertexShaderCode;
    string fragmentShaderCode;
    ifstream vertexShaderStream;
    ifstream fragmentShaderStream;
    vertexShaderStream.exceptions(ifstream::failbit | ifstream::badbit);
    fragmentShaderStream.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        string vertexShaderFile = Engine::main->programDirectory + shaderFile + ".vs";
        string fragmentShaderFile = Engine::main->programDirectory + shaderFile + ".fs";
        vertexShaderStream.open(vertexShaderFile.c_str());
        fragmentShaderStream.open(fragmentShaderFile.c_str());
        stringstream vertexShader, fragmentShader;
        vertexShader << vertexShaderStream.rdbuf();
        fragmentShader << fragmentShaderStream.rdbuf();
        vertexShaderStream.close();
        fragmentShaderStream.close();
        vertexShaderCode = vertexShader.str();
        fragmentShaderCode = fragmentShader.str();
    }catch(ifstream::failure error) {
        cout << "\nFailed to load the shaders " << shaderFile << "!" << endl;
        exit(1);
    }
    const char* vertexShader = vertexShaderCode.c_str();
    const char* fragmentShader = fragmentShaderCode.c_str();
    // compile the vertex shader:
    unsigned int vertex;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShader, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // compile the fragment shader:
    unsigned int fragment;
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShader, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // create the shader Program:
    this->programID = glCreateProgram();
    glAttachShader(this->programID, vertex);
    glAttachShader(this->programID, fragment);
    glLinkProgram(this->programID);
    checkCompileErrors(this->programID, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::addTexture(Texture* texture, string uniformName) {
    this->textures.push_back(texture);
    this->uniformNames.push_back(uniformName);
}
void Shader::render(mat4 modelTransform) {
    this->setActivate();
    this->setMat4("frame.projectionTransform", Engine::main->cameraNode->getCameraProjectionTransform());
    this->setMat4("frame.viewTransform", Engine::main->cameraNode->getCameraViewTransform());
    this->setMat4("node.modelTransform", modelTransform);
    for(unsigned int i = 0; i < this->textures.size(); i = i + 1) {
        glActiveTexture(GL_TEXTURE0 + i);
        this->setInt(this->uniformNames[i], i);
        glBindTexture(GL_TEXTURE_2D, textures[i]->data);
    }
}
void Shader::setActivate() {
    glUseProgram(this->programID);
}
void Shader::setInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value);
}
void Shader::setFloat(const string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value);
}
void Shader::setVec2(const std::string &name, const vec2 &value) const {
    glUniform2fv(glGetUniformLocation(this->programID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, const vec3 &value) const {
    glUniform3fv(glGetUniformLocation(this->programID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, const vec4 &value) const {
    glUniform4fv(glGetUniformLocation(this->programID, name.c_str()), 1, &value[0]);
}
void Shader::setMat2(const std::string &name, const mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const std::string &name, const mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string &name, const mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::checkCompileErrors(unsigned int shader, string type) {
    int success;
    char info[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, NULL, info);
            cout << "\nShader compilation error!\n"
                 << "Type: " << type << "\n" << info << endl;
        }
    }else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, NULL, info);
            cout << "\nProgram linking error!\n"
                 << "Type: " << type << "\n" << info << endl;
        }
    }
}
Shader::~Shader() {
    glDeleteProgram(this->programID);
    this->textures.clear();
    this->uniformNames.clear();
}
