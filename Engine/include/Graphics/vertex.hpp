#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "log.hpp"

#include "glad/glad.h"

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>
#include <stdint.h>

#define Y_CREATE_VERTEX_BUFFER(name , type) std::unique_ptr<Y::graphics::VertexBuffer<type>> name = std::make_unique<Y::graphics::VertexBuffer<type>>()

namespace Y {
namespace graphics {

    class RawVertexBuffer {
        protected:
            uint32_t m_Vbo = 0;
            uint32_t m_VertCount = 0;
            uint32_t m_Stride = 0;
            uint32_t m_GLType = 0;
            uint32_t m_Size = 0;
            std::vector<uint32_t> m_Layout;
            void* m_Data = nullptr;

            bool m_Uploaded = false;
        public:
            static const uint32_t m_GLTypeByte;
            static const uint32_t m_GLTypeUByte;
            static const uint32_t m_GLTypeShort;
            static const uint32_t m_GLTypeUShort;
            static const uint32_t m_GLTypeInt;
            static const uint32_t m_GLTypeUInt;
            static const uint32_t m_GLTypeFloat;
            static const uint32_t m_GLTypeDouble;

            RawVertexBuffer();
            virtual ~RawVertexBuffer();

            void SetLayout(const std::vector<uint32_t>& layout);

            virtual uint32_t GetTypeSize() const = 0;

            virtual void Upload(bool dynamic);

            void Bind();
            void Unbind();

            inline uint32_t GetID() const             { return m_Vbo; }
            inline uint32_t GetVertCount() const      { return m_VertCount; }
            inline uint32_t GetStride() const         { return m_Stride; }
            inline uint32_t GetSize() const           { return m_Size; }
            inline uint32_t GetGLType() const         { return m_GLType; }
            inline bool IsUploaded() const            { return m_Uploaded; }
            inline std::vector<uint32_t>& GetLayout() { return m_Layout; }
    };

    template <typename T>
    class VertexBuffer : public RawVertexBuffer {
        static_assert(std::is_same<T , char>()  || std::is_same<T , unsigned char>()  ||
                      std::is_same<T , short>() || std::is_same<T , unsigned short>() ||
                      std::is_same<T , int>()   || std::is_same<T , unsigned int>()   ||
                      std::is_same<T , float>() || std::is_same<T , double>() , 
                      "Vertex data type not suppored");

        uint32_t m_ValueCount;
        std::vector<T> m_DataVec;
        public:
            VertexBuffer() : m_ValueCount(0) {
                if constexpr (std::is_same<T , char>())           { m_GLType = RawVertexBuffer::m_GLTypeByte;   }
                if constexpr (std::is_same<T , unsigned char>())  { m_GLType = RawVertexBuffer::m_GLTypeUByte;  }
                if constexpr (std::is_same<T , short>())          { m_GLType = RawVertexBuffer::m_GLTypeShort;  }
                if constexpr (std::is_same<T , unsigned short>()) { m_GLType = RawVertexBuffer::m_GLTypeUShort; }
                if constexpr (std::is_same<T , int>())            { m_GLType = RawVertexBuffer::m_GLTypeInt;    }
                if constexpr (std::is_same<T , unsigned int>())   { m_GLType = RawVertexBuffer::m_GLTypeUInt;   }
                if constexpr (std::is_same<T , float>())          { m_GLType = RawVertexBuffer::m_GLTypeFloat;  }
                if constexpr (std::is_same<T , double>())         { m_GLType = RawVertexBuffer::m_GLTypeDouble; }
            }
            ~VertexBuffer() {}

            inline uint32_t GetTypeSize() const override { return sizeof(T); }

            void PushVertex(const std::vector<T>& vert) {

                uint32_t receivedVals = (uint32_t)vert.size();

                Y_ASSERT(vert.size() > 0 , "Attempting to Push Empty Vertex");
                if (m_DataVec.size() == 0) {
                    m_ValueCount = (uint32_t)vert.size();
                }

                Y_ASSERT(vert.size() == m_ValueCount , "Attempting to Push an Invalid Vertex");
                if (vert.size() == m_ValueCount) {
                    m_VertCount++;
                    m_DataVec.insert(m_DataVec.end() , vert.begin() , vert.end());
                }

                return;
            } 

            void Upload(bool dynamic = false) override {
                
                m_Stride *= sizeof(T);
                m_Size = sizeof(T) * (uint32_t)m_DataVec.size();

                Y_ASSERT(m_Size > 0 , "Attempting to Upload Empty Vertex");

                m_Data = &m_DataVec[0];
                RawVertexBuffer::Upload(dynamic);

                return;
            }
    };

    class VertexArray {
        uint32_t m_Vao , m_Ebo;
        uint32_t m_VertCount , m_EltCount;
        uint32_t m_AttribCount;
        bool m_Valid;
        std::vector<std::unique_ptr<RawVertexBuffer>> m_Vbos;
        std::string m_Name , m_Path;
        public:
            VertexArray();
            ~VertexArray();

            inline uint32_t GetVertCount() const { return m_VertCount; }
            inline uint32_t GetEltCount() const  { return m_EltCount; }
            inline bool IsValid() const          { return m_Valid; }

            void PushBuffer(std::unique_ptr<RawVertexBuffer> vbo);
            void SetElements(const std::vector<uint32_t>& elements);

            void Upload();

            void Bind();
            void Unbind();

            inline std::string GetName() const { return m_Name; }
            inline void SetName(const std::string& name) { m_Name = name; }
            inline std::string GetPath() const { return m_Path; }
            inline void SetPath(const std::string& path) { m_Path = path; }

    };

} 
}

#endif