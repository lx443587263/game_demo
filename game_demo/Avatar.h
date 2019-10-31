//------------------------------
//      Avatar.h
//		10/16/2019       created
//		10/31/2019		 modified
//		by liuxi
//-------------------------------
#pragma once

#ifndef _AVATAR_H
#define _AVATAR_H
#include <d2d1.h>
#include <cmath>
#include "ISubject.h"
#include <map>
#include <list>

struct IWICImagingFactory;

namespace game
{
	enum class AvatarState
	{
		AS_normal = 0,
		AS_Launched
	};

	class Listener_Remove
	{
	public:
		Listener_Remove(game::IListener* listener);
		bool operator()(game::IListener* listener);
	private:
		game::IListener* _listener;
	};

	class Avatar : public ISubject
	{
	public:
		Avatar();
		~Avatar();
		bool initialize(ID2D1HwndRenderTarget* _renderTarget);
		void render(ID2D1HwndRenderTarget* _renderTarget);
		void update(ID2D1HwndRenderTarget* _renderTarget);
		void launch();

		/*inherited from ISubject*/
		virtual void add_listener(MessageType mt, IListener* listener) final;
		virtual void remove_listener(MessageType mt, IListener* listener) final;
		virtual void notify(MessageType mt) final;

	private:
		void AS_normal(D2D1_SIZE_F size);
		void AS_Launched(D2D1_SIZE_F size);

	private:
		IWICImagingFactory* _pWicImgFactory = nullptr;
		ID2D1Bitmap* _pBitmap = nullptr;
		ID2D1SolidColorBrush* _pLineBrush = nullptr;
		int _avatar_x = 0;
		/* true :->
			false :<- */
		bool _bOrientation = true;
		/*pi*/
		bool _bAngleOrientation = true;
		/*
			true:down
			false:up
		*/
		bool _bLengthOrientation = true;
		float _fEndLinex = 0.0f;
		float _fEndLiney = 0.0f;
		float _fAngle = 0.0f;		
		const float _fLineLength = 100.0f;

		const float _MaxExtendLength = 450.0f;
		float _extendLength = 0.0f;
		AvatarState _avatar_state = AvatarState::AS_normal;
		/*true : down
		false : up*/
		bool _bLineOrientation = true;
		bool _isComingback = false;
		bool _is_increase = true;


		std::map<MessageType, std::list<IListener*>> _listener;

		
	};

}
#endif // !_AVATAT_H



