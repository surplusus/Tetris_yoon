#pragma once
class Game;
class Block;
class Renderer
{
private:
	Renderer(){}
	Renderer(Renderer& r){}
	~Renderer() {}
	static Renderer* Instance;
public:
	static Renderer* GetInstance() {
		if (!Instance)
			Instance = new Renderer();
		return Instance;
	}
	static void ReleaseInstance() {
		delete Instance->block;
		delete Instance;
	}
private:
	Game* m_GM;
	HDC* hdc;	// internal temporary variable
	Block* block;// internal temporary variable
	void FitInBoard(const Block& block);
	void FitInMiniBoard(const Block& block);
	void FitInBackBoard(const Block& block);
public:
	void Init(Game* GM);
	void Render(HDC& hdc);
public:

	enum FUNC_TYPE{MAIN=0, MINI=1};
	void (Renderer::*FuncPtr)(const Block&);
	void DrawBlock(Block& block);
	void DrawBG();
	void SetFuncPtr(const char* ch);	//"main", "mini"
};

