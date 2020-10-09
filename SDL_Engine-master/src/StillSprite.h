#pragma once
#ifndef __STILLSPRITE__
#define __STILLSPRITE__

#include "Sprite.h"

class StillSprite final : public Sprite
{
public:
	StillSprite(std::string spriteLoc, std::string spriteID, int width, int height, bool centered = false);
	~StillSprite();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_buildAnimations();
	std::string m_ID;
	bool m_bCentered;
};

#endif /* defined (__STILLSPRITE__) */
