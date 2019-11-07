//------------------------------
//      ScoreMgr.h
//		10/31/2019       created
//		10/31/2019		 modified
//		by liuxi
//-------------------------------
#pragma once
#ifndef _SCOREMGR_H
#define _SCOREMGR_H
#include "Ilistener.h"
#include <d2d1.h>
#include <dwrite.h>
#include <string>


namespace game
{
	class  ScoreMgr : public IListener
	{
	public:
		 ScoreMgr();
		~ ScoreMgr();
		virtual void on_update(MessageType mt, std::shared_ptr<MsgArgument> args) override;
		bool initialize(ID2D1HwndRenderTarget* _renderTarget);
		void render(ID2D1HwndRenderTarget* _renderTarget);

	private:
		int _score = 0;
		IDWriteTextFormat* _format = nullptr;
		ID2D1SolidColorBrush* _pTextBrush = nullptr;
	};

}

#endif // !_SCOREMGR_H
