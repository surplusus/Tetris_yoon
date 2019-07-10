#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();
private:
	Game* m_GM;
public:
	void Init(Game* GM);
	void Render(HDC& hdc);
};

