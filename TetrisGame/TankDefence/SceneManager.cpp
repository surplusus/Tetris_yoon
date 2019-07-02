#include "SceneManager.h"
#include <algorithm>


SceneManager::SceneManager()
{
	ManagerInterface *mi;
	mi = new LoginManager;
	scene.insert(std::make_pair(SCENELOGIN, mi));
	mi = new InGameManager;
	scene.insert(std::make_pair(SCENEINGAME, mi));
	mi = new RankManager;
	scene.insert(std::make_pair(SCENERANK, mi));

	activeScene = scene[SCENEINGAME];
}


SceneManager::~SceneManager()
{
	ManagerInterface *mi;
	for (auto iter : scene)
	{
		mi = &(*iter.second);
		delete mi;
	}
	scene.clear();
}
