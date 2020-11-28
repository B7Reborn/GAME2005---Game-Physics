#include "Ball.h"
#include "TextureManager.h"

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/Ball.png", "Ball");
	TextureManager::Instance()->load("../Assets/textures/Square.png", "Square");
	TextureManager::Instance()->load("../Assets/textures/Triangle.png", "Triangle");

	setWidth(32);
	setHeight(32);

	getTransform()->position = glm::vec2(200.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setWeight(50);

	setType(BALL);
	setShape(CIRCLE);
}

Ball::~Ball()
= default;

void Ball::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (getShape())
	{
	case CIRCLE:
		TextureManager::Instance()->drawText("Ball", x, y, 0, 255, true);
		break;
	case SQUARE:
		TextureManager::Instance()->drawText("Square", x, y, 0, 255, true);
		break;
	case TRIANGLE:
		TextureManager::Instance()->drawText("Triangle", x, y, 0, 255, true);
		break;
	default:
		break;
	}
	
}

void Ball::update()
{
	// Initial bound check (prevents ball from clipping into screen edges)
	// X-Bounds
	if ((getTransform()->position.x - getWidth() / 2) < 0.0f)
	{
		getTransform()->position.x = getWidth() / 2;
	}
	if ((getTransform()->position.x + getWidth() / 2) > 800.0f)
	{
		getTransform()->position.x = 800.0f - getWidth() / 2;
	}
	// Y-Bounds
	if ((getTransform()->position.y - getHeight() / 2) < 0.0f)
	{
		getTransform()->position.y = getHeight() / 2;
	}
	if ((getTransform()->position.y + getHeight() / 2) > 600.0f)
	{
		getTransform()->position.y = 600 - getHeight() / 2;
	}
	
	// Move every frame
	getTransform()->position += getRigidBody()->velocity;

	// Check bounds, 800x600 screen
	// X-Bounds
	if ((getTransform()->position.x - getWidth() / 2) <= 0.0f || (getTransform()->position.x + getWidth() / 2) >= 800.0f)
	{
		getRigidBody()->velocity.x *= -0.95f;
	}
	// Y-Bounds
	if ((getTransform()->position.y - getHeight() / 2) <= 0.0f || (getTransform()->position.y + getHeight() / 2) >= 600.0f)
	{
		getRigidBody()->velocity.y *= -0.95f;
	}
	
	// Reduce velocity every frame
	getRigidBody()->velocity *= 0.99f;

	// If velocity is too low, stop moving
	// XVelocity
	if (abs(getRigidBody()->velocity.x) < 0.05f)
	{
		getRigidBody()->velocity.x = 0.0f;
	}
	// YVelocity
	if (abs(getRigidBody()->velocity.y) < 0.05f)
	{
		getRigidBody()->velocity.y = 0.0f;
	}
}

void Ball::clean()
{
}

void Ball::setWeight(float val)
{
	m_weight = val;
}

float Ball::getWeight()
{
	return m_weight;
}

void Ball::setShape(Shape newShape)
{
	m_currentShape = newShape;
}

Shape Ball::getShape()
{
	return m_currentShape;
}
