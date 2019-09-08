#pragma once

class InGameScene;
class IntroScene;
class GameManager
{
private:
	GameManager();
	GameManager(const GameManager& _Other) = delete;
	GameManager(const GameManager&& _Other) = delete;
	GameManager operator= (const GameManager& _Other) = delete;
	~GameManager();

	static GameManager* pkGameManager;
public:
	static GameManager* instance()
	{
		if (nullptr == pkGameManager)
		{
			pkGameManager = new GameManager();
		}

		return pkGameManager;
	}


private:
	InGameScene* GameScene;
	IntroScene* InScene;

public:
	void init();
	void update();
	void release();

	void reset_game();
	void end_game();
};

