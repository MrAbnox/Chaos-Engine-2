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

	void setMesh(Mesh& mesh);
	void setMaterial(Material& mat);
	void setCastShadows(bool castShadows);

private:
	
	Mesh* mesh;
	Material mat;
private:
	
	bool castShadows;
};

#endif
