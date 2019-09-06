#pragma once

class KScene;
class ComPlayer;
class UIManager
{
public:
	UIManager();
	~UIManager();

public:
	void create(KScene* _Scene, ComPlayer* _Player);
};

