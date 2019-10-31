#pragma once
#ifndef _ILISTENER_H
#define  _ILISTENER_H
//------------------------------
//		Ilistener.h
//		10/31/2019       created
//		10/31/2019		 modified
//		by liuxi
//-------------------------------
#include "Types.h"
#include <memory>

namespace game
{
	class IListener
	{
	public:
		virtual void on_update(MessageType mt,std::shared_ptr<MsgArgument> args) = 0;

	private:
		
	};

}


#endif // !_ILISTENER_H
