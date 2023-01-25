#include "log.hpp"

#include "Graphics/shader.hpp"
#include "Graphics/GLErrorHelper.hpp"

namespace Y {
namespace graphics {

    int Shader::GetUniformLocation(const std::string& name) {

        auto itr = uniformLocations.find(name);
        if (itr == uniformLocations.end()) {
            uniformLocations[name] = glGetUniformLocation(programID , name.c_str()); Y_CHECK_GL_ERROR;
        }
        return uniformLocations[name];
    }

    Shader::Shader(const std::string& vertex , const std::string& fragment) : vShader(vertex) , fShader(fragment) {
        programID = glCreateProgram(); Y_CHECK_GL_ERROR;

        int status = GL_FALSE;
        char errorLog[512];

        uint32_t vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        {
            const GLchar* glSource = vertex.c_str();
            glShaderSource(vertexShaderID , 1 , &glSource , nullptr); Y_CHECK_GL_ERROR;
            glCompileShader(vertexShaderID); Y_CHECK_GL_ERROR;
            glGetShaderiv(vertexShaderID , GL_COMPILE_STATUS , &status); Y_CHECK_GL_ERROR;
            if (status != GL_TRUE) {
                glGetShaderInfoLog(vertexShaderID , sizeof(errorLog) , nullptr , errorLog); Y_CHECK_GL_ERROR;
                Y_ERROR("Vertex Shader Compilation Error -> {}" , errorLog);
            } else {
                glAttachShader(programID , vertexShaderID); Y_CHECK_GL_ERROR;
                glGetShaderInfoLog(vertexShaderID , sizeof(errorLog) , nullptr , errorLog); Y_CHECK_GL_ERROR;
            }
        }

        uint32_t fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); 
        if (status == GL_TRUE) {
            const GLchar* glSource = fragment.c_str();
            glShaderSource(fragmentShaderID , 1 , &glSource , nullptr); Y_CHECK_GL_ERROR;
            glCompileShader(fragmentShaderID); Y_CHECK_GL_ERROR;
            glGetShaderiv(fragmentShaderID , GL_COMPILE_STATUS , &status); Y_CHECK_GL_ERROR;
            if (status != GL_TRUE) {
                glGetShaderInfoLog(fragmentShaderID , sizeof(errorLog) , nullptr , errorLog); Y_CHECK_GL_ERROR;
                Y_ERROR("Fragment Shader Compilation Error -> {}" , errorLog);
            } else {
                glAttachShader(programID , fragmentShaderID); Y_CHECK_GL_ERROR;
            }
        }

        Y_ASSERT(status == GL_TRUE , "Error Compiling Shader");
        if (status == GL_TRUE) {
            glLinkProgram(programID); Y_CHECK_GL_ERROR;
            glValidateProgram(programID); Y_CHECK_GL_ERROR;
            glGetProgramiv(programID , GL_LINK_STATUS , &status); 
            if (status != GL_TRUE) {
                glGetProgramInfoLog(programID , sizeof(errorLog) , nullptr , errorLog); Y_CHECK_GL_ERROR;
                Y_ERROR("Shader Link Error -> {}" , errorLog); 
                glDeleteProgram(programID); Y_CHECK_GL_ERROR;
                programID = -1;
            }
        }

        glDeleteShader(vertexShaderID); Y_CHECK_GL_ERROR;
        glDeleteShader(fragmentShaderID); Y_CHECK_GL_ERROR;
    }
    
    Shader::~Shader() {
        glUseProgram(0); Y_CHECK_GL_ERROR;
        glDeleteProgram(programID); Y_CHECK_GL_ERROR;
    }

    void Shader::Bind() {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        return;
    }
    
    void Shader::Unbind() {
        glUseProgram(0); Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformInt(const std::string& name , int val) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniform1i(GetUniformLocation(name) , val); Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformFloat(const std::string& name , float val) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniform1f(GetUniformLocation(name) , val); Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformFloat2(const std::string& name , float val1 , float val2) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniform2f(GetUniformLocation(name) , val1 , val2);Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformFloat2(const std::string& name , const glm::vec2& val) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniform2f(GetUniformLocation(name) , val.x , val.y);Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformFloat3(const std::string& name , float val1 , float val2 , float val3) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniform3f(GetUniformLocation(name) , val1 , val2 , val3); Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformFloat3(const std::string& name , const glm::vec3& val) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniform3f(GetUniformLocation(name) , val.x , val.y , val.z); Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformFloat4(const std::string& name , float val1 , float val2 , float val3 , float val4) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniform4f(GetUniformLocation(name) , val1 , val2 , val3 , val4); Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformFloat4(const std::string& name , const glm::vec4& val) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniform4f(GetUniformLocation(name) , val.x , val.y , val.z , val.w); Y_CHECK_GL_ERROR;
        return;
    }

    void Shader::SetUniformMat3(const std::string& name , const glm::mat3& mat) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniformMatrix3fv(GetUniformLocation(name) , 1 , GL_FALSE , glm::value_ptr(mat)); Y_CHECK_GL_ERROR;
        return;
    }
    
    void Shader::SetUniformMat4(const std::string& name , const glm::mat4& mat) {
        glUseProgram(programID); Y_CHECK_GL_ERROR;
        glUniformMatrix4fv(GetUniformLocation(name) , 1 , GL_FALSE , glm::value_ptr(mat)); Y_CHECK_GL_ERROR;
        return;
    }

}
}