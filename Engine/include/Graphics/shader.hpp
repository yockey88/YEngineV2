#ifndef SHADER_HPP
#define SHADER_HPP

#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

namespace Y {
namespace graphics {

    class Shader {
        uint32_t m_ProgramID;
        std::unordered_map<std::string , int> m_UniformLocations;
        std::string m_VShader , m_FShader;

        int GetUniformLocation(const std::string& name);
        public:
            Shader(const std::string& vertex , const std::string& fragment);
            ~Shader();

            void Bind();
            void Unbind();

            void SetUniformInt(const std::string& name , int val);
            void SetUniformFloat(const std::string& name , float val);
            void SetUniformFloat2(const std::string& name , float val1 , float val2);
            void SetUniformFloat2(const std::string& name , const glm::vec2& val);
            void SetUniformFloat3(const std::string& name , float val1 , float val2 , float val3);
            void SetUniformFloat3(const std::string& name , const glm::vec3& val);
            void SetUniformFloat4(const std::string& name , float val1 , float val2 , float val3 , float val4);
            void SetUniformFloat4(const std::string& name , const glm::vec4& val);
            void SetUniformMat3(const std::string& name , const glm::mat3& mat);
            void SetUniformMat4(const std::string& name , const glm::mat4& mat);

            inline const std::string& GetVertShader() { return m_VShader; }
            inline const std::string& GetFragShader() { return m_FShader; }            
    };

}
}

#endif