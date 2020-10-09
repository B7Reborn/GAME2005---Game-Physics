#include "StillSprite.h"
#include "TextureManager.h"

StillSprite::StillSprite(std::string spriteLoc, std::string spriteID, int width, int height, bool centered)
{
	TextureManager::Instance()->load(spriteLoc, spriteID);
	m_ID = spriteID;

	setWidth(width);
	setHeight(height);

	m_bCentered = centered;

	setType(STILL_SPRITE);
}

StillSprite::~StillSprite()
= default;

void StillSprite::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->drawTextCustom(m_ID, x, y, getWidth(), getHeight(), 0.0, 255, m_bCentered);
}

void StillSprite::update()
{
}

void StillSprite::clean()
{
}
