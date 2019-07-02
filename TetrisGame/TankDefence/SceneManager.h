#pragma once
#include <map>
#include "Managers.h"

class SceneManager
{
private:
	enum scenename{
		SCENELOGIN = 0, SCENEINGAME = 1,SCENERANK =2
	};
public:
	std::map<int, ManagerInterface*> scene;
	ManagerInterface *activeScene;
	//int index = 0;
	//setindex()
	//activeScene = scene[0];
public:
	SceneManager();
	~SceneManager();

};

