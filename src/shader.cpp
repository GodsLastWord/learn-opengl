#include "shader.hpp"

#include <print>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmnetShaderPath) {

    std::string vertexShaderCode;
    std::string fragmentShaderCode;

    std::ifstream vertexFile{ vertexShaderPath };
    std::ifstream fragmentFile{ fragmnetShaderPath };

    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::stringstream vertexStream;
        std::stringstream fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexShaderCode = vertexStream.str();
        fragmentShaderCode = fragmentStream.str();
    }

    catch (std::ifstream::failure& e) {
        std::println("Shader: Failed to read files: {}", e.what());
    }

    catch (std::exception& e) {
        std::println("Shader: {}", e.what());
    }

    catch (...) {
        std::println("Shader: Unknown error occurred");
    }

    int success;
    char infoLog[512];

    unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertexCodePointer = vertexShaderCode.c_str();
    const char* fragmentCodePointer = fragmentShaderCode.c_str();

    glShaderSource(vertexShaderId, 1, &vertexCodePointer, nullptr);
    glShaderSource(fragmentShaderId, 1, &fragmentCodePointer, nullptr);

    glCompileShader(vertexShaderId);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderId, sizeof(infoLog), nullptr, infoLog);
        std::println("Shader: Failed to compile a vertex shader\n{}", infoLog);
    }

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), nullptr, infoLog);
        std::println("Shader: Failed to compile a fragment shader\n{}", infoLog);
    }

    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramId, sizeof(infoLog), nullptr, infoLog);
        std::println("Shader: Failed to link a shader program\n{}", infoLog);
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgramId);
}

void Shader::use() {
    glUseProgram(shaderProgramId);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), int(value));
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}
