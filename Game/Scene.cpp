#include "Scene.h"
#include "../Components/MeshRenderer.h"
#include "../Application/Renderer.h"
#include "../Application/Window.h"

Scene::Scene()
{
}

void Scene::load()
{
	Renderer::instance();
	//TODO: Read from file and pass string
	;
	addObjectToScene(Renderer::instance()->getObject("Camera"));
	addObjectToScene(Renderer::instance()->getObject("Nintendo"));
	addObjectToScene(Renderer::instance()->getObject("Water"));

	//TEMP
	//createPrimitive(CUBE);
}

void Scene::start()
{
	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].get()->initialize();
	}

	setupDepthBuffer();
}

void Scene::update()
{
	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].get()->update();
	}

	for (int i = 0; i < sceneObjects.size(); i++) 
	{
		if (sceneObjects[i]->getShouldDestroy())
		{
			sceneObjects.erase(sceneObjects.begin() + i);
		}
	}
}

void Scene::render()
{
	for (auto& go : sceneObjects)
	{
		if (go->getIsEnabled())
		{
			if (go->getName() == "Water")
			{
				
				//glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
				sendDepthBuffer();
			}
			
			go->render();

			if (go->getName() == "Water")
			{
				restorePass();
				//glBindFramebuffer(GL_FRAMEBUFFER, 0);
				
			}
		}
	}
}

void Scene::setupDepthBuffer()
{
	// configure g-buffer framebuffer
// ------------------------------
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	int width, height;
	glfwGetFramebufferSize(Window::instance()->getWindow(), &width, &height);

	// accumulation buffer
	// TODO 9.1 : Change the format of the accumulation buffer to 16bit floating point (4 components)
	glGenTextures(1, &gAccum);
	glBindTexture(GL_TEXTURE_2D, gAccum);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// depth texture buffer
	glGenTextures(1, &gDepth);
	glBindTexture(GL_TEXTURE_2D, gDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

	// attach textures to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gAccum, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);

	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
	unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, attachments);
	
	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;

	
	// configure accumulation buffer framebuffer
	// ------------------------------
	glGenFramebuffers(1, &accumBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, accumBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::sendDepthBuffer()
{
	Renderer::instance()->getShader("Water").Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gDepth);
	Renderer::instance()->getShader("Water").setUniform("DepthBuffer", 0);

	// Depth clamp ignores clipping with near and far planes
	glEnable(GL_DEPTH_CLAMP);
	
	// Disable depth write
	glDepthMask(false);

	// Disable depth test
	glDisable(GL_DEPTH_TEST);
}

void Scene::restorePass()
{
	// Restore values
	glDisable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	glDisable(GL_DEPTH_CLAMP);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	glDepthMask(true);
	glEnable(GL_DEPTH_TEST);
}

void Scene::saveScene()
{
}

void Scene::unload()
{
}

std::shared_ptr<GameObject> Scene::createEmpty()
{
	auto obj = std::shared_ptr<GameObject>(new GameObject());

	sceneObjects.push_back(obj);
	return obj;
}

void Scene::createPrimitive(Prim primitive, glm::vec3& pos)
{
	std::string temp = "";
	
	switch (primitive)
	{
	case CUBE:

		temp = "Cube";
		break;
		
	case QUAD:

		
		break;
		
	default:
		break;
	}

	addObjectToScene(Renderer::instance()->getObject(temp));
}

void Scene::duplicateObject()
{
}

void Scene::deleteObject()
{
}

void Scene::addObjectToScene(const std::shared_ptr<GameObject> object)
{
	GameObject* t = object.get();
	auto obj = std::make_shared<GameObject>(*t);
	sceneObjects.push_back(obj);

	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		for (size_t j = 0; j < sceneObjects[i]->getComponents().size(); j++)
		{
			sceneObjects[i]->getComponents()[j]->setGameObject(*sceneObjects[i].get());
		}
	}
}

//TODO: Make sure this doesn't create another copy in memory and just passes the reference
std::vector<std::shared_ptr<GameObject>> Scene::getSceneObjects()
{
	return sceneObjects;
}
