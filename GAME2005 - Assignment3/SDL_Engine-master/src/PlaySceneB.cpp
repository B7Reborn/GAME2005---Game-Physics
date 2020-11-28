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

	drawDisplayList();
	
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlaySceneB::update()
{
	if (m_running)
	{
		updateMousePosition();
		checkCollision();

		m_pBallVelocityX->setText("Ball X-velocity = " + std::to_string(m_pBall->getRigidBody()->velocity.x) + " m/s");
		m_pBallVelocityY->setText("Ball Y-velocity = " + std::to_string(m_pBall->getRigidBody()->velocity.y) + " m/s");
		m_pBrickVelocityX->setText("Brick X-velocity = " + std::to_string(m_pBrick->getRigidBody()->velocity.x) + " m/s");
		m_pBrickVelocityY->setText("Brick Y-velocity = " + std::to_string(m_pBrick->getRigidBody()->velocity.y) + " m/s");
		
		updateDisplayList();
	}
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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_GRAVE))
	{
		if (!m_keyPressed)
		{
			m_running = !m_running;
			m_keyPressed = !m_keyPressed;
		}
	}
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_GRAVE))
	{
		if (m_keyPressed)
		{
			m_keyPressed = !m_keyPressed;
		}
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		reset();
	}
}

void PlaySceneB::start()
{
	const SDL_Color aqua = { 0, 255, 255, 255 };
	m_tempBallWeight = 50.0f;
	m_tempBrickWeight = 1000.0f;

	// Add Background
	m_pBackground = new Background("../Assets/textures/BrickbreakBG.png", "BG2");
	addChild(m_pBackground);

	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Add brick to scene
	updateMousePosition();
	m_pBrick = new Brick(m_mousePosition.x, m_mousePosition.y);
	addChild(m_pBrick);
	
	// Add ball to scene
	m_pBall = new Ball();
	addChild(m_pBall);

	// Info Labels
	m_pBallWeight = new Label("Ball weight = " + std::to_string(m_pBall->getWeight()) + " kg", "Consolas", 16, aqua);
	m_pBallWeight->getTransform()->position = glm::vec2(650.0f, 40.0f);
	addChild(m_pBallWeight);

	m_pBallVelocityX = new Label("Ball X-velocity = " + std::to_string(m_pBall->getRigidBody()->velocity.x) + " m/s", "Consolas", 16, aqua);
	m_pBallVelocityX->getTransform()->position = glm::vec2(650.0f, 60.0f);
	addChild(m_pBallVelocityX);

	m_pBallVelocityY = new Label("Ball Y-velocity = " + std::to_string(m_pBall->getRigidBody()->velocity.y) + " m/s", "Consolas", 16, aqua);
	m_pBallVelocityY->getTransform()->position = glm::vec2(650.0f, 80.0f);
	addChild(m_pBallVelocityY);

	m_pBrickWeight = new Label("Brick weight = " + std::to_string(m_pBrick->getWeight()) + " kg", "Consolas", 16, aqua);
	m_pBrickWeight->getTransform()->position = glm::vec2(650.0f, 100.0f);
	addChild(m_pBrickWeight);
	
	m_pBrickVelocityX = new Label("Brick X-velocity = " + std::to_string(m_pBrick->getRigidBody()->velocity.x) + " m/s", "Consolas", 16, aqua);
	m_pBrickVelocityX->getTransform()->position = glm::vec2(650.0f, 120.0f);
	addChild(m_pBrickVelocityX);

	m_pBrickVelocityY = new Label("Brick Y-velocity = " + std::to_string(m_pBrick->getRigidBody()->velocity.y) + " m/s", "Consolas", 16, aqua);
	m_pBrickVelocityY->getTransform()->position = glm::vec2(650.0f, 140.0f);
	addChild(m_pBrickVelocityY);
	
	/* Instructions Labels */
	m_pInstructionsLabel1 = new Label("Press the backtick (`) character to toggle Debug View", "Consolas", 20, aqua);
	m_pInstructionsLabel1->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);
	addChild(m_pInstructionsLabel1);

	m_pInstructionsLabel2 = new Label("Press the 1 key to return to the start screen", "Consolas", 20, aqua);
	m_pInstructionsLabel2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 530.0f);
	addChild(m_pInstructionsLabel2);

	m_pInstructionsLabel3 = new Label("Press the spacebar to reset the simulation with new parameters", "Consolas", 20, aqua);
	m_pInstructionsLabel3->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 560.0f);
	addChild(m_pInstructionsLabel3);
}

void PlaySceneB::updateMousePosition()
{
	m_mousePosition = EventManager::Instance().getMousePosition();
	if (m_pBrick)
	{
		m_pBrick->getTransform()->position = m_mousePosition;
	}
}

void PlaySceneB::checkCollision()
{
	switch (m_pBall->getShape())
	{
	case CIRCLE:
		circleCollision();
		break;
	case TRIANGLE:
		circleCollision();
		break;
	case SQUARE:
		squareCollision();
		break;
	default:
		circleCollision();
		break;
	}
	
}

void PlaySceneB::reset()
{
	m_pBall->getTransform()->position = glm::vec2(200.0f, 200.0f);
	m_pBall->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	m_pBall->setWeight(m_tempBallWeight);
	m_pBall->setShape(m_tempShape);
	m_pBrick->setWeight(m_tempBrickWeight);
	m_pBallWeight->setText("Ball weight = " + std::to_string(m_pBall->getWeight()) + " kg");
	m_pBrickWeight->setText("Brick weight = " + std::to_string(m_pBrick->getWeight()) + " kg");
}

void PlaySceneB::circleCollision()
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

void PlaySceneB::squareCollision()
{
	if (CollisionManager::AABBCheck(m_pBall, m_pBrick))
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

void PlaySceneB::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Change Parameters", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	
	if(ImGui::Button("Circle"))
	{
		m_tempShape = CIRCLE;
	}
	if (ImGui::Button("Triangle"))
	{
		m_tempShape = TRIANGLE;
	}
	if (ImGui::Button("Square"))
	{
		m_tempShape = SQUARE;
	}

	ImGui::Separator();

	static float BallWeight[1] = { m_tempBallWeight };
	if(ImGui::SliderFloat("Ball Weight", BallWeight, 0.0f, 1000.0f))
	{
		m_tempBallWeight = BallWeight[0];
		/*std::cout << BallWeight[0] << std::endl;
		std::cout << "---------------------------\n";*/
	}
	static float BrickWeight[1] = { m_tempBrickWeight };
	if (ImGui::SliderFloat("Brick Weight", BrickWeight, 0.0f, 1000.0f))
	{
		m_tempBrickWeight = BrickWeight[0];
		/*std::cout << BrickWeight[0] << std::endl;
		std::cout << "---------------------------\n";*/
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
