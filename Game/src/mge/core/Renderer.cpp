#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "World.hpp"
#include "mge/materials/AbstractMaterial.hpp"

Renderer::Renderer():debug(false)
{
    //make sure we test the depthbuffer
	glEnable(GL_DEPTH_TEST);

	//tell opengl which vertex winding is considered to be front facing
	glFrontFace(GL_CCW);

	//tell opengl to enable face culling for the back faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//set the default blend mode aka dark magic:
	//https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml
    //https://www.opengl.org/wiki/Blending
    //http://www.informit.com/articles/article.aspx?p=1616796&seqNum=5
    //http://www.andersriggelsen.dk/glblendfunc.php
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor((float)0x2d / 0xff, (float)0x6b / 0xff, (float)0xce / 0xff, 1.0f);
}

Renderer::~Renderer()
{
}

void Renderer::setClearColor(GLbyte pR, GLbyte pG, GLbyte pB) {
	glClearColor((float)pR / 0xff, (float)pG / 0xff, (float)pB / 0xff, 1.0f);
}

void Renderer::render(int pass, World* pWorld) {
	render(pass, pWorld, pWorld, nullptr, pWorld->getMainCamera(), true);
}

void Renderer::render(int pass, World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, Camera* pCamera, bool pRecursive)
{
	render(pass, pWorld, pGameObject, pMaterial, pGameObject->getWorldTransform(), glm::inverse(pCamera->getWorldTransform()), pCamera->getProjection(), pRecursive);
}

void Renderer::render(int pass, World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix, bool pRecursive) {
	renderSelf(pass, pWorld, pGameObject, pMaterial == nullptr?pGameObject->getMaterial():pMaterial, pModelMatrix, pViewMatrix, pProjectionMatrix);
	if (pRecursive) renderChildren(pass, pWorld, pGameObject, pMaterial, pModelMatrix, pViewMatrix, pProjectionMatrix, pRecursive);
}

void Renderer::renderSelf(int pass, World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	render(pass, pWorld, pGameObject->getMesh(), pMaterial, pModelMatrix, pViewMatrix, pProjectionMatrix);
	if (debug) renderMeshDebugInfo(pass, pGameObject->getMesh(), pModelMatrix, pViewMatrix, pProjectionMatrix);
}

void Renderer::renderChildren(int pass, World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix, bool pRecursive) {
	int childCount = pGameObject->getChildCount();
	if (childCount < 1) return;

	//note that with a loop like this, deleting children during rendering is not a good idea :)
	GameObject* child = 0;
	for (int i = 0; i < childCount; i++) {
		child = pGameObject->getChildAt(i);
		if(child->IsEnabled())
			render(pass, pWorld, child, pMaterial, pModelMatrix * child->getTransform(), pViewMatrix, pProjectionMatrix, pRecursive);
	}
}

void Renderer::render(int pass, World* pWorld, Mesh* pMesh, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (pMesh != nullptr && pMaterial != nullptr) pMaterial->render(pass, pWorld, pMesh, pModelMatrix, pViewMatrix, pProjectionMatrix);
}

void Renderer::renderMeshDebugInfo(int pass, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (pMesh != nullptr) pMesh->drawDebugInfo(pModelMatrix, pViewMatrix, pProjectionMatrix);
}

