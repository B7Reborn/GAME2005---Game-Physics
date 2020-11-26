#include "PlaySceneB.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlaySceneB::PlaySceneB()
{
	PlaySceneB::start();
}

PlaySceneB::~PlaySceneB()
= default;

void PlaySceneB::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlaySceneB::update()
{
	updateMousePosition();
	checkCollision();
	updateDisplayList();
}

void PlaySceneB::clean()
{
	removeAllChildren();
}

void PlaySceneB::handleEvents()
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

void PlaySceneB::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Add brick to scene
	updateMousePosition();
	m_pBrick = new Brick(m_mousePosition.x, m_mousePosition.y);
	addChild(m_pBrick);
	
	// Add ball to scene
	m_pBall = new Ball();
	addChild(m_pBall);

	// Back Button
	/*m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);*/

	// Next Button
	/*m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);*/

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	addChild(m_pInstructionsLabel);
}

void PlaySceneB::updateMousePosition()
{
	m_mousePosition = EventManager::Instance().getMousePosition();
	//std::cout << m_mousePosition.x << " " << m_mousePosition.y << std::endl;
	if (m_pBrick)
	{
		m_pBrick->getTransform()->position = m_mousePosition;
	}
}

void PlaySceneB::checkCollision()
{
	if (CollisionManager::circleAABBCheck(m_pBall, m_pBrick))
	{
		// v1f = v1i[(m1-m2)/(m1+m2)] + v2i[(2*m2)/(m1+m2)]
		// v2f = v1i[(2*m1)/(m1+m2)] + v2i[(m2-m1)/(m1+m2)]
		const glm::vec2 ballVelInitial = m_pBall->getRigidBody()->velocity;
		const glm::vec2 brickVelInitial = m_pBrick->getRigidBody()->velocity;
		const float ballWeight = m_pBall->getWeight();
		const float brickWeight = m_pBrick->getWeight();
		const float totalWeight = ballWeight + brickWeight;
		// Ball velocity
		m_pBall->getRigidBody()->velocity.x = ballVelInitial.x * ((ballWeight - brickWeight) / totalWeight) +
			brickVelInitial.x * ((2 * brickWeight) / totalWeight);
		m_pBall->getRigidBody()->velocity.y = ballVelInitial.y * ((ballWeight - brickWeight) / totalWeight) +
			brickVelInitial.y * ((2 * brickWeight) / totalWeight);

		// Brick velocity
		m_pBrick->getRigidBody()->velocity.x = ballVelInitial.x * ((2 * ballWeight) / totalWeight) +
			brickVelInitial.x * ((brickWeight - ballWeight) / totalWeight);
		m_pBrick->getRigidBody()->velocity.y = ballVelInitial.y * ((2 * ballWeight) / totalWeight) +
			brickVelInitial.y * ((brickWeight - ballWeight) / totalWeight);

	}
}

void PlaySceneB::GUI_Function() const
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
