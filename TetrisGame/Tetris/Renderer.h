#pragma once
class Game;
class Block;
class Renderer
{
private:
	Renderer() {}
	Renderer(Renderer& r) {}
	~Renderer() {}
	static Renderer* Instance;
public:
	static Renderer* GetInstance() {
		if (!Instance)
			Instance = new Renderer();
		return Instance;
	}
	static void ReleaseInstance() {
		delete Instance;
	}
private:
	Game* m_GM;
	HDC* hdc;	// internal temporary variable
public:
	void Init(Game* GM);
	void Render(HDC& hdc);
public:
	void DrawBlock(Block& block);
	void DrawBG();
};

