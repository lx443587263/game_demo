//------------------------------
//      ConcreteArguments.hpp
//		10/31/2019       created
//		10/31/2019		 modified
//		by liuxi
//-------------------------------
#pragma once
#ifndef _CONCRETEARGUMENTS_H
#define _CONCRETEARGUMENTS_H
#include "Types.h"


namespace game
{
	enum class ScoreType
	{
		ST_Increase = 0,
		ST_Decrease
	};

	class ScoreArg : public MsgArgument
	{
	public:
		ScoreType _score_type;
	};
	
}

#endif // !_CONCRETEARGUMENTS_H
