#include "Brick.h"
#include "TextureManager.h"

Brick::Brick(float x, float y)
{
	TextureManager::Instance()->load("../Assets/textures/Brick.png", "Brick");
	
	setWidth(128);
	setHeight(32);

	m_previousPosition = glm::vec2(x, y);
	getTransform()->position = m_previousPosition;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setWeight(1000);

	setType(BRICK);
}

Brick::~Brick()
= default;

void Brick::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	
	TextureManager::Instance()->drawText("Brick", x, y, 0, 255, true);
}

void Brick::update()
{
	// Position changed, update velocity
	if (getTransform()->position != m_previousPosition)
	{
		float x = getTransform()->position.x - m_previousPosition.x;
		float y = getTransform()->position.y - m_previousPosition.y;
		getRigidBody()->velocity = glm::vec2(x, y);
		m_previousPosition = getTransform()->position;
		//std::cout << "Velocity changed this frame." << std::endl;
	}
	// Position did not changed, velocity is now 0
	else
	{
		//std::cout << "Velocity did not change this frame." << std::endl;
		getRigidBody()->velocity = glm::vec2(0, 0);
	}
}

void Brick::clean()
{
}

void Brick::setWeight(float val)
{
	m_weight = val;
}

float Brick::getWeight()
{
	return m_weight;
}
