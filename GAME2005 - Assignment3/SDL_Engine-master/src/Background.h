#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "DisplayObject.h"

class Background final : public DisplayObject {
public:
	Background(std::string filestring, std::string id);
	~Background();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	std::string m_fileID;
};


#endif /* defined (__BACKGROUND__) */