//------------------------------
//      Avatar.h
//		10/16/2019       created
//		10/29/2019		 modified
//		by liuxi
//-------------------------------
#pragma once

#ifndef _AVATAR_H
#define _AVATAR_H
#include <d2d1.h>
#include <cmath>

struct IWICImagingFactory;

namespace game
{
	enum class AvatarState
	{
		AS_normal = 0,
		AS_Launched
	};

	class Avatar
	{
	public:
		Avatar();
		~Avatar();
		bool initialize(ID2D1HwndRenderTarget* _renderTarget);
		void render(ID2D1HwndRenderTarget* _renderTarget);
		void update(ID2D1HwndRenderTarget* _renderTarget);
		void launch();
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


		
	};

}
#endif // !_AVATAT_H



