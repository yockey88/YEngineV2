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
            uint32_t vbo = 0;
            uint32_t vertCount = 0;
            uint32_t stride = 0;
            uint32_t GLType = 0;
            uint32_t size = 0;
            std::vector<uint32_t> layout;
            void* data = nullptr;

            bool uploaded = false;
        public:
            static const uint32_t GLTypeByte;
            static const uint32_t GLTypeUByte;
            static const uint32_t GLTypeShort;
            static const uint32_t GLTypeUShort;
            static const uint32_t GLTypeInt;
            static const uint32_t GLTypeUInt;
            static const uint32_t GLTypeFloat;
            static const uint32_t GLTypeDouble;

            RawVertexBuffer();
            virtual ~RawVertexBuffer();

            void SetLayout(const std::vector<uint32_t>& layout);

            virtual uint32_t GetTypeSize() const = 0;

            virtual void Upload(bool dynamic);

            void Bind();
            void Unbind();

            inline uint32_t GetID() const             { return vbo; }
            inline uint32_t GetVertCount() const      { return vertCount; }
            inline uint32_t GetStride() const         { return stride; }
            inline uint32_t GetSize() const           { return size; }
            inline uint32_t GetGLType() const         { return GLType; }
            inline bool IsUploaded() const            { return uploaded; }
            inline std::vector<uint32_t>& GetLayout() { return layout; }
    };

    template <typename T>
    class VertexBuffer : public RawVertexBuffer {
        static_assert(std::is_same<T , char>()  || std::is_same<T , unsigned char>()  ||
                      std::is_same<T , short>() || std::is_same<T , unsigned short>() ||
                      std::is_same<T , int>()   || std::is_same<T , unsigned int>()   ||
                      std::is_same<T , float>() || std::is_same<T , double>() , 
                      "Vertex data type not suppored");

        uint32_t valueCount;
        std::vector<T> dataVec;
        public:
            VertexBuffer() : valueCount(0) {
                if constexpr (std::is_same<T , char>())           { GLType = RawVertexBuffer::GLTypeByte;   }
                if constexpr (std::is_same<T , unsigned char>())  { GLType = RawVertexBuffer::GLTypeUByte;  }
                if constexpr (std::is_same<T , short>())          { GLType = RawVertexBuffer::GLTypeShort;  }
                if constexpr (std::is_same<T , unsigned short>()) { GLType = RawVertexBuffer::GLTypeUShort; }
                if constexpr (std::is_same<T , int>())            { GLType = RawVertexBuffer::GLTypeInt;    }
                if constexpr (std::is_same<T , unsigned int>())   { GLType = RawVertexBuffer::GLTypeUInt;   }
                if constexpr (std::is_same<T , float>())          { GLType = RawVertexBuffer::GLTypeFloat;  }
                if constexpr (std::is_same<T , double>())         { GLType = RawVertexBuffer::GLTypeDouble; }
            }
            ~VertexBuffer() {}

            inline uint32_t GetTypeSize() const override { return sizeof(T); }

            void PushVertex(const std::vector<T>& vert) {

                uint32_t receivedVals = (uint32_t)vert.size();

                Y_ASSERT(vert.size() > 0 , "Attempting to Push Empty Vertex");
                if (dataVec.size() == 0) {
                    valueCount = (uint32_t)vert.size();
                }

                Y_ASSERT(vert.size() == valueCount , "Attempting to Push an Invalid Vertex");
                if (vert.size() == valueCount) {
                    vertCount++;
                    dataVec.insert(dataVec.end() , vert.begin() , vert.end());
                }

                return;
            } 

            void Upload(bool dynamic = false) override {
                
                stride *= sizeof(T);
                size = sizeof(T) * (uint32_t)dataVec.size();

                Y_ASSERT(size > 0 , "Attempting to Upload Empty Vertex");

                data = &dataVec[0];
                RawVertexBuffer::Upload(dynamic);

                return;
            }
    };

    class VertexArray {
        uint32_t vao , ebo;
        uint32_t vertCount , eltCount;
        uint32_t attribCount;
        bool valid;
        std::vector<std::unique_ptr<RawVertexBuffer>> vbos;
        std::string name;
        public:
            VertexArray();
            ~VertexArray();

            inline uint32_t GetVertCount() const { return vertCount; }
            inline uint32_t GetEltCount() const  { return eltCount; }
            inline bool IsValid() const          { return valid; }

            void PushBuffer(std::unique_ptr<RawVertexBuffer> vbo);
            void SetElements(const std::vector<uint32_t>& elements);

            void Upload();

            void Bind();
            void Unbind();

            inline std::string GetName() const { return name; }
            inline void SetName(const std::string& name) { this->name = name; }

    };

}
}

#endif

