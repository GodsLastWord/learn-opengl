#pragma once

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
public:
    unsigned int shaderProgramId;

    Shader(const std::string&, const std::string&);
    ~Shader();

    void use();

    void setBool(const std::string&, bool) const;
    void setInt(const std::string&, int) const;
    void setFloat(const std::string&, float) const;
};
