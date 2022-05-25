#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "Component.h"
#include "../Game/Mesh.h"
#include "../Game/Material.h"

class MeshRenderer : public Component
{

public:
	
	MeshRenderer();
	~MeshRenderer();

public:

	void update() override;
	void fixedUpdate(float deltaTime) override;

private:
	
	Mesh mesh;
	Material mat;
private:
	
	bool castShadows;
};

#endif
