#pragma once

class IMap
{
public:
	virtual ~IMap() {}

	virtual void update(float dt) = 0;
	virtual void draw() = 0;
};