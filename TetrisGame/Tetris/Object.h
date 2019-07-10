#pragma once
class Object
{
public:
	virtual ~Object() {}
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

