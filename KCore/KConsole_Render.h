#pragma once
#include "KRenderer.h"
#include "KComponent.h"



class KConsole_Render : 
	public KRenderer,
	public KComponent
{
public:
	KConsole_Render();
	~KConsole_Render() override;

public:
	bool init() override;
	void update() override;
	void release() override;
	void render() override;
};