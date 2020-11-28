#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Brick.h"
#include "Ball.h"
#include "Button.h"
#include "Label.h"
#include "Background.h"

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
	void reset();
	void circleCollision();
	void squareCollision();
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;

	glm::vec2 m_mousePosition;
	bool m_running = true;
	bool m_keyPressed = false;

	// Objects
	Brick* m_pBrick;
	Ball* m_pBall;
	Background* m_pBackground;

	// Info Labels
	Label* m_pBallWeight;
	Label* m_pBrickWeight;
	Label* m_pBallVelocityX;
	Label* m_pBallVelocityY;
	Label* m_pBrickVelocityX;
	Label* m_pBrickVelocityY;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel1;
	Label* m_pInstructionsLabel2;
	Label* m_pInstructionsLabel3;

	// Value holders
	// These are used to hold values to be input when the simulation is reset via spacebar
	float m_tempBallWeight;
	float m_tempBrickWeight;
	Shape m_tempShape = CIRCLE;
};

#endif /* defined (__PLAY_SCENE__) */