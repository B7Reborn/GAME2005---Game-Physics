#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE_B);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("GAME2005 - Assignment 3", "Consolas", 60, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Select a scene to begin", "Consolas", 40, blue, glm::vec2(400.0f, 520.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	// Student info labels
	m_pNameLabel1 = new Label("Shane Holloway", "Consolas", 40, blue, glm::vec2(250.0f, 90.0f));
	m_pNameLabel1->setParent(this);
	addChild(m_pNameLabel1);

	m_pNumberLabel1 = new Label("101273911", "Consolas", 40, blue, glm::vec2(650.0f, 90.0f));
	m_pNumberLabel1->setParent(this);
	addChild(m_pNumberLabel1);

	m_pNameLabel2 = new Label("Maddison Folgier", "Consolas", 40, blue, glm::vec2(250.0f, 150.0f));
	m_pNameLabel2->setParent(this);
	addChild(m_pNameLabel2);

	m_pNumberLabel2 = new Label("123456789", "Consolas", 40, blue, glm::vec2(650.0f, 150.0f));
	m_pNumberLabel2->setParent(this);
	addChild(m_pNumberLabel2);

	/*m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f); 
	addChild(m_pShip);*/ 

	// Scene A Button
	m_pSceneAButton = new Button("../Assets/textures/SceneAButton.png", "ButtonA");
	m_pSceneAButton->getTransform()->position = glm::vec2(250.0f, 400.0f); 

	m_pSceneAButton->addEventListener(CLICK, [&]()-> void
	{
		m_pSceneAButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE_B);
	});
	
	m_pSceneAButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pSceneAButton->setAlpha(128);
	});

	m_pSceneAButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pSceneAButton->setAlpha(255);
	});
	addChild(m_pSceneAButton);

	// Scene B Button
	m_pSceneBButton = new Button("../Assets/textures/SceneBButton.png", "ButtonB");
	m_pSceneBButton->getTransform()->position = glm::vec2(550.0f, 400.0f);

	m_pSceneBButton->addEventListener(CLICK, [&]()-> void
		{
			m_pSceneBButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE_B);
		});

	m_pSceneBButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pSceneBButton->setAlpha(128);
		});

	m_pSceneBButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pSceneBButton->setAlpha(255);
		});
	addChild(m_pSceneBButton);
}

