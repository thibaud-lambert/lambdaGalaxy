#ifndef LAMBDAGALAXY_SHADER_H
#define LAMBDAGALAXY_SHADER_H

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>

class Shader
{
public:
    Shader();

    bool loadFromFiles(const std::string& fileV, const std::string& fileF,
                       const std::string& fileTCS, const std::string& fileTES,
                       const std::string& fileGEO);

    void activate() const;

    int getUniformLocation(const char* name) const;

    int getAttribLocation(const char* name) const;

    int id() const { return m_ProgramID; }
    
    bool valid() const { return m_IsValid; }

protected:
         
    std::string loadSourceFromFile(const std::string& filename);
    bool addShader(int shaderType, const std::string& src);
    bool loadSources(const std::string& vsrc, const std::string& fsrc,
                     const std::string& tcssrc, const std::string& tessrc,
                     const std::string& geosrc);
    static void printProgramInfoLog(GLuint objectID);
    static void printShaderInfoLog(GLuint objectID);

    bool m_IsValid;
    GLuint m_ProgramID;
};

#endif
