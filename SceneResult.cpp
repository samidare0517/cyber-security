#include "SceneResult.h"
#include "DxLib.h"
#include "Pad.h"

void SceneResult::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;

}

void SceneResult::end()
{

}

void SceneResult::update()
{

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_isEnd = false;
	}
}

void SceneResult::draw()
{

	DrawString(540, 360, "ÉQÅ[ÉÄÉNÉäÉA", GetColor(255, 255, 255));
}