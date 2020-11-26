#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "Sprite.h"

class Brick final : public Sprite
{
public:
	Brick(float x, float y);
	~Brick();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setWeight(float val);
	float getWeight();
private:
	glm::vec2 m_previousPosition;
	float m_weight;
};

#endif /* defined (__BRICK__) */