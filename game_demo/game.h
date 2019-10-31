//------------------------------
//      game.h
//		10/16/2019       created
//		10/29/2019		 modified
//		by liuxi
//-------------------------------
#pragma once

#ifndef _GAME_H
#define _GAME_H

#include <windows.h>
#include <memory>
#include "Avatar.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <unordered_map>
#include "ItemManager.h"
#include "ScoreMgr.h"

namespace game
{
	enum class INPUTBUTTON
	{
		IB_Space = 0,
	};

	class Game
	{
	public:
		//get myobject
		static Game* getSingleton(void);
		static void destroySingleton(void);
		//initialize
		bool initialize(HWND hWnd);
		LRESULT processEvent(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
		bool frame(void);
		bool checkInput(INPUTBUTTON btn);
		std::shared_ptr<ItemManager> item_mgr(void);
	private:	
		Game();
		~Game();
		Game(Game&) = delete;
		Game(Game&&) = delete;
	private:
		static Game * _Game;
		ID2D1Factory * _direct2dFactory = nullptr;
		std::shared_ptr<Avatar> _avatar;
		std::shared_ptr<ItemManager> _Item_Manager;
		ID2D1HwndRenderTarget * _renderTarget = nullptr;
		unsigned long _ticks = 0ul;
		std::unordered_map<INPUTBUTTON, bool> _inputs;
		std::shared_ptr<ScoreMgr> _score_mgr;
		
	};
}

#endif // !_GAME_H


