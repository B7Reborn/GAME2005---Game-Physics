#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Util.h"
#include "StillSprite.h"
#include <cmath>

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	// Function which solves for the kicking angle, used on initial startup and then whenever the user changes a variable
	void solveForAngle();

	// Function to move "particle" in a parabola towards its destination
	void moveParticle();
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	StillSprite* m_pBackground;
	StillSprite* m_pDetonatorSprite;
	StillSprite* m_pTrooperSprite;
	StillSprite* m_pWookieSprite;
	Player* m_pPlayer;
	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;

	// Math Variables (4) and Labels
	// Variables are set to the values required to "solve" the initial problem given in the assignment
	float m_Distance = 485.0f;
	float m_Speed = 95.0f;
	float m_AngleDeg; // Left blank initially as it must be solved for
	float m_Gravity = 9.8f;
	Label* m_pDistanceLabel;
	Label* m_pSpeedLabel;
	Label* m_pAngleLabel;
	Label* m_pGravityLabel;

	// Additional math variables and labels for parabola making
	float m_Time;
	float m_VelocityX;
	float m_VelocityY;
	Label* m_pTimeLabel;
	Label* m_pVelXLabel;
	Label* m_pVelYLabel;
	float m_TempTime = 0.0f;
	const float m_TimeStep = 0.05f;
	float m_DetonatorYPos = 450.0f;
	bool m_bInMotion = false;
	float m_InitialVelocityY;
	bool m_bLargerAngle = true;
};

#endif /* defined (__PLAY_SCENE__) */