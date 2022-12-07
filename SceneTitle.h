#pragma once
#include "SceneBase.h"
#include "SelectMenu.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle() 
	{
		m_textPosY = 0;
		m_textVecY = 0;
		m_isEnd = false;
	}
	virtual ~SceneTitle() {}


	virtual void init();
	virtual void end();

	virtual void update();
	virtual void draw();

	virtual bool isEnd() { return m_isEnd; }

	void Fade();

private:
	// テキスト表示位置変更
	int m_textPosY;
	int m_textVecY;

	SelectMenu m_menu;

	bool m_isEnd;
	
	int fadeValue_ = 255;		// 黒矩形とのブレンド具合

};