#include "Graphics/vertex.hpp"
#include "Graphics/helper.hpp"

namespace Y {
namespace graphics {

    const uint32_t RawVertexBuffer::m_GLTypeByte   = GL_BYTE;
	const uint32_t RawVertexBuffer::m_GLTypeUByte  = GL_UNSIGNED_BYTE;
	const uint32_t RawVertexBuffer::m_GLTypeShort  = GL_SHORT;
	const uint32_t RawVertexBuffer::m_GLTypeUShort = GL_UNSIGNED_SHORT;
	const uint32_t RawVertexBuffer::m_GLTypeInt    = GL_INT;
	const uint32_t RawVertexBuffer::m_GLTypeUInt   = GL_UNSIGNED_INT;
	const uint32_t RawVertexBuffer::m_GLTypeFloat  = GL_FLOAT;
	const uint32_t RawVertexBuffer::m_GLTypeDouble = GL_DOUBLE;

    RawVertexBuffer::RawVertexBuffer() {
        glGenBuffers(1 , &m_Vbo); Y_CHECK_GL_ERROR;
    }

    RawVertexBuffer::~RawVertexBuffer() {
        glDeleteBuffers(1 , &m_Vbo); Y_CHECK_GL_ERROR;
    }

    void RawVertexBuffer::SetLayout(const std::vector<uint32_t>& layout) {
        
        m_Layout = layout;
        m_Stride = 0;

        for (auto& count : layout)
            m_Stride += count;

        return;
    }

    void RawVertexBuffer::Upload(bool dynamic = false) {
        
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo); Y_CHECK_GL_ERROR;
        glBufferData(GL_ARRAY_BUFFER , m_Size , m_Data , (dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW); Y_CHECK_GL_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER , 0);
        m_Uploaded = true;

        return;
    }

    void RawVertexBuffer::Bind() {

        glBindBuffer(GL_ARRAY_BUFFER , m_Vbo);

        return;
    }

    void RawVertexBuffer::Unbind() {

        glBindBuffer(GL_ARRAY_BUFFER , 0);

        return;
    }

    VertexArray::VertexArray() : m_Vao(0) , m_Ebo(0) , m_AttribCount(0) , m_VertCount(0) , m_EltCount(0) , m_Valid(false) { 
        glGenVertexArrays(1 , &m_Vao); Y_CHECK_GL_ERROR;
    }

    VertexArray::~VertexArray() {
        m_Vbos.clear();
        glDeleteVertexArrays(1 , &m_Vao); Y_CHECK_GL_ERROR;
    }

    void VertexArray::PushBuffer(std::unique_ptr<RawVertexBuffer> vbo) {

        if (m_Vbos.size() > 0)
            Y_ASSERT(m_Vbos[0]->GetVertCount() == vbo->GetVertCount() , "Attempting to Push a Vertex Buffer with an Incorrect Number of Elements");

        Y_ASSERT(vbo->GetLayout().size() > 0, "Vertex Buffer Layout is Undefined");
        if (vbo->GetLayout().size() > 0) {
			m_Vbos.push_back(std::move(vbo));
			m_VertCount = (uint32_t)m_Vbos[0]->GetVertCount();
		}

        return;
    }

    void VertexArray::SetElements(const std::vector<uint32_t>& elements) {

        m_EltCount = (uint32_t)elements.size();
		glBindVertexArray(m_Vao); Y_CHECK_GL_ERROR;
		glGenBuffers(1 , &m_Ebo); Y_CHECK_GL_ERROR;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_Ebo); Y_CHECK_GL_ERROR;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER , elements.size() * sizeof(uint32_t) , &elements[0] , GL_STATIC_DRAW); Y_CHECK_GL_ERROR;
		glBindVertexArray(0); Y_CHECK_GL_ERROR;

        return;
    }

    void VertexArray::Upload() {

        Bind();
		uint32_t m_AttributeCount = 0;
		for (auto& vbo : m_Vbos) {
			if (!vbo->IsUploaded())
				vbo->Upload(false);

			vbo->Bind();
			uint32_t offset = 0;
			for (uint32_t count : vbo->GetLayout()) {
				glEnableVertexAttribArray(m_AttributeCount); Y_CHECK_GL_ERROR;
				glVertexAttribPointer(m_AttributeCount , count , static_cast<GLenum>(vbo->GetGLType()) , GL_FALSE , vbo->GetStride() , (void*)(intptr_t)offset); Y_CHECK_GL_ERROR;

				m_AttributeCount++;
				offset += (count * vbo->GetTypeSize());
			}
			vbo->Unbind();
		}
		Unbind();
		m_Valid = true;

        return;
    }

    void VertexArray::Bind() {

        glBindVertexArray(m_Vao); Y_CHECK_GL_ERROR;

        return;
    }

    void VertexArray::Unbind() {

        glBindVertexArray(0); Y_CHECK_GL_ERROR;

        return;
    }

}
}