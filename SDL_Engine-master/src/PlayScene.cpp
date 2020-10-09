#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	if (m_bInMotion)
	{
		moveParticle();
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Background Sprite
	m_pBackground = new StillSprite("../Assets/textures/Hoth.png", "bg", 1200, 600);
	m_pBackground->getTransform()->position = glm::vec2(0.0f, 0.0f);
	addChild(m_pBackground);

	// Wookie Sprite
	m_pWookieSprite = new StillSprite("../Assets/textures/Wookie.png", "wookie", 128, 128, true);
	m_pWookieSprite->getTransform()->position = glm::vec2(100.0f, 450.0f);
	addChild(m_pWookieSprite);

	// Stormtrooper Sprite
	m_pTrooperSprite = new StillSprite("../Assets/textures/Stormtroopers.png", "stormtroopers", 128, 128, true);
	m_pTrooperSprite->getTransform()->position = glm::vec2(100.0f + m_Distance, 450.0f);
	addChild(m_pTrooperSprite);

	// Detonator Sprite
	m_pDetonatorSprite = new StillSprite("../Assets/textures/ThermalDetonator.png", "thermalDetonator", 64, 64, true);
	m_pDetonatorSprite->getTransform()->position = glm::vec2(100.0f, 450.0f);
	addChild(m_pDetonatorSprite);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(600.0f, 300.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		m_TempTime = 0.0f;
		m_pDetonatorSprite->getTransform()->position = m_pWookieSprite->getTransform()->position;
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(800.0f, 300.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		m_bInMotion = true;
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 550.0f);
	addChild(m_pInstructionsLabel);

	// Mathematics Labels
	m_pDistanceLabel = new Label("Distance to Stormtroopers: " + std::to_string(m_Distance) + " meters", "Consolas", 16);
	m_pDistanceLabel->getTransform()->position = glm::vec2(900.0f, 40.0f);
	addChild(m_pDistanceLabel);

	m_pSpeedLabel = new Label("Speed of thermal detonator: " + std::to_string(m_Speed) + " meters per second", "Consolas", 16);
	m_pSpeedLabel->getTransform()->position = glm::vec2(900.0f, 80.0f);
	addChild(m_pSpeedLabel);

	// Before adding the angle label, we must first solve for the angle
	solveForAngle();
	m_pAngleLabel = new Label("Angle thermal detonator is thrown: " + std::to_string(m_AngleDeg) + " degrees", "Consolas", 16);
	m_pAngleLabel->getTransform()->position = glm::vec2(900.0f, 120.0f);
	addChild(m_pAngleLabel);

	m_pGravityLabel = new Label("Gravity of planet: " + std::to_string(m_Gravity) + " meters per second squared", "Consolas", 16);
	m_pGravityLabel->getTransform()->position = glm::vec2(900.0f, 160.0f);
	addChild(m_pGravityLabel);

	m_pTimeLabel = new Label("Total air time: " + std::to_string(m_Time) + " seconds", "Consolas", 16);
	m_pTimeLabel->getTransform()->position = glm::vec2(900.0f, 200.0f);
	addChild(m_pTimeLabel);

	m_pVelXLabel = new Label("Initial X velocity: " + std::to_string(m_VelocityX) + " meters per second", "Consolas", 16);
	m_pVelXLabel->getTransform()->position = glm::vec2(900.0f, 240.0f);
	addChild(m_pVelXLabel);

	m_pVelYLabel = new Label("Initial Y velocity: " + std::to_string(m_VelocityY) + " meters per second", "Consolas", 16);
	m_pVelYLabel->getTransform()->position = glm::vec2(900.0f, 280.0f);
	addChild(m_pVelYLabel);
}

void PlayScene::solveForAngle()
{
	// Solves for the kicking angle based on given variables using a rearranged formula for range
	float numerator = m_Distance * m_Gravity;
	float denominator = m_Speed * m_Speed;
	float fractionResult = numerator / denominator;
	m_AngleDeg = asin(fractionResult) / 2;

	m_VelocityX = cos(m_AngleDeg) * m_Speed;
	m_InitialVelocityY = m_VelocityY = sin(m_AngleDeg) * m_Speed;
	m_Time = (2 * m_VelocityY) / m_Gravity;

	m_AngleDeg = Util::Rad2Deg * m_AngleDeg;

	if (m_bLargerAngle)
	{
		m_AngleDeg = 90 - m_AngleDeg;
		m_VelocityX = cos(Util::Deg2Rad * m_AngleDeg) * m_Speed;
		m_InitialVelocityY = m_VelocityY = sin(Util::Deg2Rad * m_AngleDeg) * m_Speed;
		m_Time = (2 * m_VelocityY) / m_Gravity;
	}
}

void PlayScene::moveParticle()
{
	// Moves the "particle" in steps towards its destination
	if (m_TempTime + m_TimeStep > m_Time)
	{
		// Final step, end detonator sprite on the trooper sprite
		m_TempTime = m_Time;
		m_pDetonatorSprite->getTransform()->position = m_pTrooperSprite->getTransform()->position;
		m_bInMotion = false;
		m_pBackButton->setActive(true);
		m_pNextButton->setActive(true);
		m_DetonatorYPos = m_pWookieSprite->getTransform()->position.y;
		m_VelocityY = m_InitialVelocityY;
	}
	else
	{
		m_TempTime += m_TimeStep;
		m_VelocityY = m_VelocityY - (m_Gravity * m_TimeStep);
		m_DetonatorYPos = m_DetonatorYPos - m_VelocityY * m_TimeStep;
		m_pDetonatorSprite->getTransform()->position.x = 100.0f + m_TempTime * m_VelocityX;
		m_pDetonatorSprite->getTransform()->position.y = m_DetonatorYPos;
	}
	
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
