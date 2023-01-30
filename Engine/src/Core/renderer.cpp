#include "engine.hpp"

#include "Core/renderer.hpp"
#include "Core/factory.hpp"
#include "Managers/renderManager.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Y {
namespace core {

    void YRenderer2D::RenderPoint(const glm::vec3& color , const glm::vec3& pos , const float& size) {
        
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderPoint , Factory::CreatePoint(color , pos , size) , Factory::LoadBasicCircleCamShader() , size));

    }

    void YRenderer2D::RenderLine(const glm::vec3& color , const glm::vec3& pnt1 , const glm::vec3& pnt2 , const float& width) {
        
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderLine , Factory::CreateLine(color , pnt1 , pnt2) , Factory::LoadBasicCamShader() , width));

    }

    void YRenderer2D::RenderLine(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& pnt1 , const glm::vec3& pnt2 , const float& width) {
        
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderLine , Factory::CreateLine(color1 , color2 , pnt1 , pnt2) , Factory::LoadBasicCamShader() , width));

    }

    void YRenderer2D::RenderTriangle(const glm::vec3& color , const glm::vec3& pos , const glm::vec3& size) {
        
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model , pos) * glm::scale(model , size);
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , Factory::CreateTriangleMesh(color) , Factory::LoadBasicCamShader() , model));

    }

    void YRenderer2D::RenderTriangle(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& pos , const glm::vec3& size) {
        
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model , pos) * glm::scale(model , size);
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , Factory::CreateTriangleMesh(color1 , color2 , color3) ,Factory::LoadBasicCamShader() , model));

    }

    void YRenderer2D::RenderRect(const glm::vec3& color , const glm::vec3& pos , const glm::vec3& size) {
        
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model , pos) * glm::scale(model , size);
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , Factory::CreateSquareMesh(color) , Factory::LoadBasicCamShader() , model));

    }

    void YRenderer2D::RenderRect(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& color4 ,
                                    const glm::vec3& pos , const glm::vec3& size) {
        
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model , pos) * glm::scale(model , size);
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , Factory::CreateSquareMesh(color1 , color2 , color3 , color4) ,Factory::LoadBasicCamShader() , model));

    }

    void YRenderer2D::RenderCube(const glm::vec3& color , const glm::vec3& pos , const glm::vec3& size) {
        
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model , pos) * glm::scale(model , size);
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , Factory::CreateCubeMesh(color) , Factory::LoadBasicCamShader() , model));

    }

    void YRenderer2D::RenderCube(const glm::vec3& color1 , const glm::vec3& color2 , const glm::vec3& color3 , const glm::vec3& color4 , 
                                    const glm::vec3& pos , const glm::vec3& size) {
        
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model , pos) * glm::scale(model , size);
        Y_RENDERER.Submit(Y_SUBMIT_RENDER_CMND(RenderVertexArray , Factory::CreateCubeMesh(color1 , color2 , color3 , color4) , Factory::LoadBasicCamShader() , model));
        

    }

}
}