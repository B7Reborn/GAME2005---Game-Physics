#include "Background.h"

#include "TextureManager.h"

Background::Background(std::string filestring, std::string id)
{
	m_fileID = id;
	TextureManager::Instance()->load(filestring, m_fileID);

	const auto size = glm::vec2(800, 600);
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(BACKGROUND);
}

Background::~Background()
= default;

void Background::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw(m_fileID, x, y, 0, 255, false);
}

void Background::update()
{
}

void Background::clean()
{
}
