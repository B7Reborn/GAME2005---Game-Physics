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
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	// Title Labels
	m_pStartLabel = new Label("GAME 2005", "Consolas", 80, blue, glm::vec2(600.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Assignment 1", "Consolas", 40, blue, glm::vec2(600.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	// Name and Number labels
	m_pNameLabel1 = new Label("Shane Holloway", "Consolas", 40, blue, glm::vec2(400.0f, 160.0f));
	m_pNameLabel1->setParent(this);
	addChild(m_pNameLabel1);

	m_pNameLabel2 = new Label("Maddison Folgier", "Consolas", 40, blue, glm::vec2(400.0f, 200.0f));
	m_pNameLabel2->setParent(this);
	addChild(m_pNameLabel2);

	m_pNumberLabel1 = new Label("101273911", "Consolas", 40, blue, glm::vec2(800.0f, 160.0f));
	m_pNumberLabel1->setParent(this);
	addChild(m_pNumberLabel1);

	m_pNumberLabel2 = new Label("NUMBER HERE", "Consolas", 40, blue, glm::vec2(800.0f, 200.0f));
	m_pNumberLabel2->setParent(this);
	addChild(m_pNumberLabel2);

	// Start Button
	m_pStartButton = new Button("../Assets/textures/StartSimulation.png", "startButton", START_BUTTON);
	m_pStartButton->getTransform()->position = glm::vec2(600.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
		std::cout << "Alpha set to 128" << std::endl;
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

