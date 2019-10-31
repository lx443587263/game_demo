//------------------------------
//      Types.h
//		10/31/2019       created
//		10/31/2019		 modified
//		by liuxi
//-------------------------------
#pragma once
#ifndef _TYPES_H
#define _TYPES_H
namespace game
{
	enum class MessageType
	{
		MT_SCORE = 0,
	};

	class MsgArgument
	{
	public:
		MessageType msg_type;
	};
}
#endif // !_TYPES_H
