//------------------------------
//      ISubject.h
//		10/31/2019       created
//		10/31/2019		 modified
//		by liuxi
//-------------------------------
#pragma once
#ifndef _ISUBJECT_H
#define _ISUBJECT_H
#include "Ilistener.h"


namespace game
{
	class ISubject
	{
	public:
		virtual void add_listener(MessageType mt, IListener* listener) = 0;
		virtual void remove_listener(MessageType mt, IListener* listener) = 0;
		virtual void notify(MessageType mt) = 0;
	};


}
#endif // !_ISUBJECT_H
