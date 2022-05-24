#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

public:
	void create();
	void update();
	void draw();

public:

	//TODO::Component part 
	void addComponent(); 

public:

	void setIsEnabled(const bool& value);
	bool getIsEnabled() const;

	Transform getTransform() const;

private:

	std::string name;
	bool isEnabled;

};

#endif // !GAMEOBJECT_H
