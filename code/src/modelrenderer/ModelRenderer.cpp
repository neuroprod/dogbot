//
// Created by kris on 17.08.20.
//

#include "ModelRenderer.h"
#include "MeshDataPool.h"
using namespace ci;
using namespace ci::app;

void ModelRenderer::setup() {
    fboWindow.setup("ModelRenderer");
    MDP()->setup();
    model = std::make_shared<FKModel>();
    model->setup();

    gl::Texture2d::Format depthFormat;
    depthFormat.setInternalFormat(GL_DEPTH_COMPONENT32F);
    depthFormat.setCompareMode(GL_COMPARE_REF_TO_TEXTURE);
    depthFormat.setMagFilter(GL_LINEAR);
    depthFormat.setMinFilter(GL_LINEAR);
    depthFormat.setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    depthFormat.setCompareFunc(GL_LEQUAL);
    mShadowMapTex = gl::Texture2d::create(fboSize, fboSize, depthFormat);

    gl::Fbo::Format fboFormat;
    fboFormat.attachment(GL_DEPTH_ATTACHMENT, mShadowMapTex);
    mFbo = gl::Fbo::create(fboSize, fboSize, fboFormat);

    mLightPos = vec3(1000.0f, 2500.0f, 1500.0f);
    mLightCam.setPerspective(50.0f, mFbo->getAspectRatio(), 10.f, 15000.0f);
    mLightCam.lookAt(mLightPos, vec3(0.0f));


}
void ModelRenderer::update() {

}
void ModelRenderer::draw() {
    gl::enableDepthRead();
    gl::enableDepthWrite();

    if(fboWindow.width !=0 || fboWindow.height !=0)
    {
      //  drawShadow();

    }


    if(  fboWindow.begin())
  {
      camera.aspect = (float)fboWindow.width / (float)fboWindow.height;

      camera.update(fboWindow.vMin,fboWindow.vMax);


      if (ImGui::BeginMenuBar())
      {
          if (ImGui::BeginMenu("Items"))
          {
              //    ImGui::Checkbox(g->gName.c_str(),&g->gVisible);
              ImGui::EndMenu();
          }
          ImGui::EndMenuBar();
      }
      gl::clear(Color::gray(0.5));

      gl::pushMatrices();
      gl::setMatrices(camera.mCam);
      gl::drawCoordinateFrame(1000);

      gl::ScopedTextureBind texScope(mShadowMapTex, (uint8_t)0);
      //	vec3 mvLightPos = vec3(gl::getModelView() * vec4(mLightPos, 1.0f));
      mat4 shadowMatrix = mLightCam.getProjectionMatrix() * mLightCam.getViewMatrix();


      MDP()->mGlsl->uniform("uShadowMap", 0);
      MDP()->mGlsl->uniform("uLightPos", mLightPos);
      MDP()->mGlsl->uniform("uShadowMatrix", shadowMatrix);
      MDP()->mGlsl->uniform("uViewPos", camera.mCam.getEyePoint());
      MDP()->mGlsl->uniform("alpha", 1.f);



      for (auto n : model->nodes)
      {
          gl::pushMatrices();

          for (auto m : n->meshData->meshes)
          {

              gl::setModelMatrix(n->globalMatrix *m->modelMatrix);
              m->draw();
          }
          gl::popMatrices();

      }

      gl::popMatrices();
      fboWindow.end();


  }
    gl::disableDepthRead();
    gl::disableDepthWrite();

}
void ModelRenderer::drawShadow()
{
    gl::pushMatrices();
    gl::enable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.0f, 2.0f);

    gl::ScopedFramebuffer fbo(mFbo);
    gl::ScopedViewport viewport(vec2(0.0f), mFbo->getSize());
    gl::clear(Color::black());


        gl::color(Color::white());
        gl::setMatrices(mLightCam);



        for (auto n : model->nodes)
        {
            gl::pushMatrices();
            gl::setModelMatrix(n->globalMatrix);
            for (auto m : n->meshData->meshes)
            {
                m->drawShadow();
            }
            gl::popMatrices();

        }


    gl::disable(GL_POLYGON_OFFSET_FILL);

    gl::popMatrices();

}