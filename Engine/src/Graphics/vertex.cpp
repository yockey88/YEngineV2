#include "Graphics/vertex.hpp"
#include "Graphics/GLErrorHelper.hpp"

namespace Y {
namespace graphics {

    const uint32_t RawVertexBuffer::GLTypeByte   = GL_BYTE;
	const uint32_t RawVertexBuffer::GLTypeUByte  = GL_UNSIGNED_BYTE;
	const uint32_t RawVertexBuffer::GLTypeShort  = GL_SHORT;
	const uint32_t RawVertexBuffer::GLTypeUShort = GL_UNSIGNED_SHORT;
	const uint32_t RawVertexBuffer::GLTypeInt    = GL_INT;
	const uint32_t RawVertexBuffer::GLTypeUInt   = GL_UNSIGNED_INT;
	const uint32_t RawVertexBuffer::GLTypeFloat  = GL_FLOAT;
	const uint32_t RawVertexBuffer::GLTypeDouble = GL_DOUBLE;

    RawVertexBuffer::RawVertexBuffer() {
        glGenBuffers(1 , &vbo); Y_CHECK_GL_ERROR;
    }

    RawVertexBuffer::~RawVertexBuffer() {
        glDeleteBuffers(1 , &vbo); Y_CHECK_GL_ERROR;
    }

    void RawVertexBuffer::SetLayout(const std::vector<uint32_t>& layout) {
        
        this->layout = layout;
        stride = 0;
        for (auto& count : layout)
            stride += count;

        return;
    }

    void RawVertexBuffer::Upload(bool dynamic = false) {
Y_CHECK_GL_ERROR
        glBindBuffer(GL_ARRAY_BUFFER, vbo); Y_CHECK_GL_ERROR;
        glBufferData(GL_ARRAY_BUFFER , size , data , (dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW); Y_CHECK_GL_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER , 0);
        uploaded = true;

        return;
    }

    void RawVertexBuffer::Bind() {

        glBindBuffer(GL_ARRAY_BUFFER , vbo);

        return;
    }

    void RawVertexBuffer::Unbind() {

        glBindBuffer(GL_ARRAY_BUFFER , 0);

        return;
    }

    VertexArray::VertexArray() : vao(0) , ebo(0) , attribCount(0) , vertCount(0) , eltCount(0) , valid(false) { 
        glGenVertexArrays(1 , &vao); Y_CHECK_GL_ERROR;
    }

    VertexArray::~VertexArray() {
        vbos.clear();
        glDeleteVertexArrays(1 , &vao); Y_CHECK_GL_ERROR;
    }

    void VertexArray::PushBuffer(std::unique_ptr<RawVertexBuffer> vbo) {

        if (vbos.size() > 0)
            Y_ASSERT(vbos[0]->GetVertCount() == vbo->GetVertCount() , "Attempting to Push a Vertex Buffer with an Incorrect Number of Elements");

        Y_ASSERT(vbo->GetLayout().size() > 0, "Vertex Buffer Layout is Undefined");
        if (vbo->GetLayout().size() > 0) {
			vbos.push_back(std::move(vbo));
			vertCount = (uint32_t)vbos[0]->GetVertCount();
		}

        return;
    }

    void VertexArray::SetElements(const std::vector<uint32_t>& elements) {

        eltCount = (uint32_t)elements.size();
		glBindVertexArray(vao); Y_CHECK_GL_ERROR;
		glGenBuffers(1 , &ebo); Y_CHECK_GL_ERROR;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , ebo); Y_CHECK_GL_ERROR;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER , elements.size() * sizeof(uint32_t) , &elements[0] , GL_STATIC_DRAW); Y_CHECK_GL_ERROR;
		glBindVertexArray(0); Y_CHECK_GL_ERROR;

        return;
    }

    void VertexArray::Upload() {

        Bind();
		uint32_t attributeCount = 0;
		for (auto& vbo : vbos) {
			if (!vbo->IsUploaded())
				vbo->Upload(false);

			vbo->Bind();
			uint32_t offset = 0;
			for (uint32_t count : vbo->GetLayout()) {Y_CHECK_GL_ERROR;
				glVertexAttribPointer(attributeCount , count , static_cast<GLenum>(vbo->GetGLType()) , GL_FALSE , vbo->GetStride() , (void*)(intptr_t)offset); Y_CHECK_GL_ERROR;

				attributeCount++;
				offset += (count * vbo->GetTypeSize());
			}
			vbo->Unbind();
		}
		Unbind();
		valid = true;

        return;
    }

    void VertexArray::Bind() {

        glBindVertexArray(vao); Y_CHECK_GL_ERROR;

        return;
    }

    void VertexArray::Unbind() {

        glBindVertexArray(0); Y_CHECK_GL_ERROR;

        return;
    }

}
}