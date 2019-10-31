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


namespace game
{
	class  ScoreMgr : public IListener
	{
	public:
		 ScoreMgr();
		~ ScoreMgr();
		virtual void on_update(MessageType mt, std::shared_ptr<MsgArgument> args) override;

	private:
		int _score = 0;
	};

}

#endif // !_SCOREMGR_H
