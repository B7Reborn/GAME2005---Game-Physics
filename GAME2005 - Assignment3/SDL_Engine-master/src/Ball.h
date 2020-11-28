#pragma once
#ifndef __BALL__
#define __BALL__

#include "Sprite.h"
#include "Shapes.h"

class Ball final : public Sprite
{
public:
	Ball();
	~Ball();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setWeight(float val);
	float getWeight();
	void setShape(Shape newShape);
	Shape getShape();
private:
	float m_weight;
	Shape m_currentShape;
};

#endif /* defined (__BALL__) */