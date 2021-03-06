#pragma once
#include "ResourceManager.h"
#include "GameScene.h"

/**
* Description: This handles setting scenes and swapping between scenes
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update(double dt);
	void draw(sf::RenderWindow& window, float a);
	void handleInput(InputHandler& input);
	void addScene(std::string name, Scene* scene);
	void setCurrentScene(std::string sceneName);
	void setTextures();

	ResourceManager m_resources; //Our resources
private:
	Scene * m_current;
	std::map<std::string, Scene*> m_scenes; //The map of scenes

};

