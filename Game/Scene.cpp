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
	
	addObjectToScene(Renderer::instance()->getObject("Camera"));
	addObjectToScene(Renderer::instance()->getObject("Water"));

	//Can Only render one of these at a time
	//______________________________________________________________
	addObjectToScene(Renderer::instance()->getObject("Rock"));
	//addObjectToScene(Renderer::instance()->getObject("Cube"));
	//addObjectToScene(Renderer::instance()->getObject("Nintendo"));
}


void Scene::start()
{
	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].get()->initialize();
	}

	setupDepthBuffer();
}

//Update objects and destroy them later (So it doesn't mess up the for vector)
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

//TODO: Render objects
void Scene::render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (auto& go : sceneObjects)
	{
		if (go->getIsEnabled())
		{
			//render everything but water
			if (go->getName() != "Water")
				go->render();
		}
	}

	//
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
	glBlitFramebuffer(0, 0, Window::instance()->getScreenSize().x, Window::instance()->getScreenSize().y, 0, 0, Window::instance()->getScreenSize().x, Window::instance()->getScreenSize().y, GL_COLOR_BUFFER_BIT , GL_NEAREST);

	sendDepthBuffer();
	//render water
	for (auto& go : sceneObjects)
	{
		if (go->getIsEnabled())
		{
			//render everything but water
			if(go->getName() == "Water")
				go->render();
		}
	}

	glDisable(GL_BLEND);
}

void Scene::setupDepthBuffer()
{
	// configure g-buffer framebuffer
// ------------------------------
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	int width, height;
	glfwGetFramebufferSize(Window::instance()->getWindow(), &width, &height);

	// others color buffer
	glGenTextures(1, &gOthers);
	glBindTexture(GL_TEXTURE_2D, gOthers);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gOthers, 0);



	// depth texture buffer
	glGenTextures(1, &gDepth);
	glBindTexture(GL_TEXTURE_2D, gDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);

	// attach textures to framebuffer

	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
	unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, attachments);
	
	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::sendDepthBuffer()
{
	Renderer::instance()->getShader("Water").Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gDepth);
	Renderer::instance()->getShader("Water").setUniform("depthBuffer", 0);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

std::shared_ptr<GameObject> Scene::createEmpty()
{
	auto obj = std::shared_ptr<GameObject>(new GameObject());

	sceneObjects.push_back(obj);
	return obj;
}

//TODO: Have U.I. able to create and render multiple objects
//ADD Quads as a primitive
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

//TODO: add object duplication with UI
void Scene::duplicateObject()
{
}

//TODO: delete object with UI
void Scene::deleteObject()
{
}

//This adds the object to the scene so it can be rendered
void Scene::addObjectToScene(const std::shared_ptr<GameObject> object)
{
	GameObject* t = object.get();
	auto obj = std::make_shared<GameObject>(*t);
	sceneObjects.push_back(obj);

	//Set components pointer to gameobject they are attached to as the one created.
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
