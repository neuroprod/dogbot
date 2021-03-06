//
// Created by kris on 17.08.20.
//

#include "ModelRenderer.h"
#include "MeshDataPool.h"
#include "cinder/gl/GlslProg.h"
using namespace ci;
using namespace ci::app;

void ModelRenderer::setup() {

    fboWindow.setup("ModelRenderer",false);
    MDP()->setup();

    model = std::make_shared<FKModel>();
    model->setup();
    mat4 posM ;
    posM= glm::translate(posM,vec3(0,330,0));
    float F5 =glm::pi<float>()/4;
    std::vector<float > m = {0,-F5 ,F5*2 ,0,F5 ,-F5*2,0,-F5 ,F5*2,0,F5 ,-F5*2};
    model->setPosition(posM,m);
    model->update();
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

    mLightPos = vec3(2000.0f, 2500.0f, 2000.0f);
    mLightCam.setPerspective(50.0f, mFbo->getAspectRatio(), 10.f, 15000.0f);
    mLightCam.lookAt(mLightPos, vec3(0.0f));


}
void ModelRenderer::update() {
    model->update();
}
void ModelRenderer::draw() {
    gl::enableDepthRead();
    gl::enableDepthWrite();


    mLightCam.lookAt(mLightPos+model->bodyPos, vec3(0.0f)+model->bodyPos);
    if(fboWindow.width !=0 || fboWindow.height !=0)
    {
       drawShadow();

    }


    if(  fboWindow.begin())
  {
      camera.aspect = (float)fboWindow.width / (float)fboWindow.height;
      camera.setBodyPos(model->bodyPos);
      camera.update(fboWindow.vMin,fboWindow.vMax);


      if (ImGui::BeginMenuBar())
      {
          if (ImGui::BeginMenu("View Options"))
          {
              //    ImGui::Checkbox(g->gName.c_str(),&g->gVisible);
              if (ImGui::MenuItem("Show Floor", NULL, showFloor)) {showFloor = !showFloor;}
              if (ImGui::MenuItem("Show Mesh", NULL, showMesh)) {showMesh = !showMesh;}
              if (ImGui::MenuItem("Show Wire", NULL, showWire)) {showWire = !showWire;}
              if (ImGui::MenuItem("Show COM", NULL, showCOM)) {showCOM = !showCOM;}
              if (ImGui::MenuItem("Show CollisionShapes", NULL, showCollisionShapes)) {showCollisionShapes= !showCollisionShapes;}
              ImGui::EndMenu();
          }
          ImGui::EndMenuBar();
      }
      if(showFloor)
      {
          gl::clear(Color(0.65, 0.9, 0.98));
      }else{

          gl::clear(Color(0.0, 0.0, 0.0));
      }
      gl::pushMatrices();
      gl::setMatrices(camera.mCam);
      gl::pushMatrices();
      gl::scale(1000,1000,1000);
      SYMBOLBATCHES()->coordinateFrame->draw();
      gl::popMatrices();
    if(showWire)
    {
        for (auto n : model->nodes)
        {
            gl::pushMatrices();
            gl::setModelMatrix(n->globalMatrix);
            SYMBOLBATCHES()->coordinateFrame->draw();
            gl::popMatrices();

        }

        model->drawWire();
    }
      if(showCollisionShapes)
      {
          gl::color(0, 1, 0);
          for (vec3 p:physicsPositions)
          {
              gl::pushMatrices();
              gl::translate(p);
              gl::scale(vec3(20));
              SYMBOLBATCHES()->sphereBatch->draw();
              gl::popMatrices();

          }
      }
      if(showCOM)
      {

          model->drawCOM();
      }

      if (showMesh || showFloor)
      {

          gl::ScopedTextureBind texScope(mShadowMapTex, (uint8_t) 0);
          //	vec3 mvLightPos = vec3(gl::getModelView() * vec4(mLightPos, 1.0f));
          mat4 shadowMatrix = mLightCam.getProjectionMatrix() * mLightCam.getViewMatrix();



          if (showFloor)
          {

              auto glsl = SYMBOLBATCHES()->floorBatch->getGlslProg();
              glsl->uniform("uShadowMap", 0);
              glsl->uniform("uLightPos", mLightPos);
              glsl->uniform("uShadowMatrix", shadowMatrix);
              glsl->uniform("uViewPos", camera.mCam.getEyePoint());
              glsl->uniform("alpha", 1.f);
              glsl->uniform("spec", 0.01f);
              gl::color(Color::gray(0.4));
              SYMBOLBATCHES()->floorBatch->draw();
          }
          if (showMesh)
          {
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

                      gl::setModelMatrix(n->globalMatrix * m->modelMatrix);
                      m->draw();
                  }
                  gl::popMatrices();

              }
          }

      }
      gl::popMatrices();
      fboWindow.end();


  }
    gl::disableDepthRead();
    gl::disableDepthWrite();

}
void ModelRenderer::drawShadow()
{
    if (!showMesh && !showFloor) return;
    gl::pushMatrices();
    gl::enable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.0f, 2.0f);

    gl::ScopedFramebuffer fbo(mFbo);
    gl::ScopedViewport viewport(vec2(0.0f), mFbo->getSize());
    gl::clear(Color::black());

    if (showMesh)
    {
        gl::color(Color::white());
        gl::setMatrices(mLightCam);


        for (auto n : model->nodes)
        {
            gl::pushMatrices();

            for (auto m : n->meshData->meshes)
            {
                gl::setModelMatrix(n->globalMatrix * m->modelMatrix);
                m->drawShadow();
            }
            gl::popMatrices();

        }

    }
    gl::disable(GL_POLYGON_OFFSET_FILL);

    gl::popMatrices();

}