#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Brick.h"
#include "Ball.h"
#include "Button.h"
#include "Label.h"

class PlaySceneB : public Scene
{
public:
	PlaySceneB();
	~PlaySceneB();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void updateMousePosition();
	void checkCollision();
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;

	glm::vec2 m_mousePosition;

	// Objects
	Brick* m_pBrick;
	Ball* m_pBall;


	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
};

#endif /* defined (__PLAY_SCENE__) */