#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "Component.h"
#include "../Game/Mesh.h"
#include "../Game/Material.h"

class MeshRenderer : public Component
{
public:
	
	explicit MeshRenderer(GameObject* gameObject);
	~MeshRenderer();

public:

	void update() override;
	void render();
	void fixedUpdate(float deltaTime) override;

	void setMesh(std::shared_ptr<Mesh> mesh);
	void setMaterial(std::shared_ptr<Material> mat);
	void setCastShadows(bool castShadows);
	void setShader(std::string shader);

	std::shared_ptr<Material> getMaterial();

private:
	
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> mat;
	
private:
	
	bool castShadows;
	std::string shader;
};

#endif
