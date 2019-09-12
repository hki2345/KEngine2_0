#pragma once
#include "KRenderer.h"
#include "KComponent.h"



class KConsole_Render :  public KRenderer
{
public:
	KConsole_Render();
	~KConsole_Render() override;

public:
	void create() override;
	bool init() override;
	void render() override;
};