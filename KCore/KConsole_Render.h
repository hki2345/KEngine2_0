#pragma once
#include "KRenderer.h"
#include "KComponent.h"



class KConsole_Render :  public KRenderer
{
public:
	KConsole_Render();
	~KConsole_Render() override;

public:
	bool init() override;
	void update() override;
	void render() override;
};