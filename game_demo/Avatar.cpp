//------------------------------
//      Avatar.cpp
//		10/16/2019       created
//		10/29/2019		 modified
//		by liuxi
//-------------------------------
#include "Avatar.h"
#include "game.h"
#include <wincodec.h>
#include <Windows.h>
#include <float.h>
#include "ItemManager.h"

using namespace game;

//-------------------------------------------------------------------------
game::Avatar::Avatar()
{

}
//-------------------------------------------------------------------------
game::Avatar::~Avatar()
{

}
//-------------------------------------------------------------------------
bool game::Avatar::initialize(ID2D1HwndRenderTarget* _renderTarget)
{
	HRESULT hResult = ::CoCreateInstance
	(CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(void**)&_pWicImgFactory);
	if (FAILED(hResult))
		return false;

	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pSource = nullptr;
	IWICFormatConverter* pConverter = nullptr;
	
	hResult = _pWicImgFactory->CreateDecoderFromFilename(
		L"Flyfish_Logo_Yellow.png",
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder);

	if (FAILED(hResult))
		return false;


	hResult = pDecoder->GetFrame(0,&pSource);
	if (FAILED(hResult))
		return 0;

	hResult = _pWicImgFactory->CreateFormatConverter(&pConverter);

	if (FAILED(hResult))
		return 0;

	hResult = pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeMedianCut);

	if (FAILED(hResult))
		return false;

	hResult = _renderTarget->CreateBitmapFromWicBitmap(
		pConverter, nullptr, &_pBitmap);

	if (FAILED(hResult))
		return false;

	hResult = _renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.0f, 0.0f,0.6f),&_pLineBrush);

	if (FAILED(hResult))
		return false;

	pDecoder->Release();
	pConverter->Release();
	_pWicImgFactory->Release();
	pSource->Release();

	return true;
}
//-------------------------------------------------------------------------
void game::Avatar::update(ID2D1HwndRenderTarget* _renderTarget)
{
	auto size = _renderTarget->GetSize();

	if (_avatar_state == AvatarState::AS_normal)
	{
		AS_normal(size);
	}
	else 
	{
		AS_Launched(size);
	}
	

}
//-------------------------------------------------------------------------
void game::Avatar::render(ID2D1HwndRenderTarget* _renderTarget)
{
	//draw»ñµÃÍ¼°æµÄ³ß´ç
	D2D1_SIZE_F size = _renderTarget->GetSize();
	D2D1_RECT_F rect;
	rect.left = _avatar_x;
	rect.top = 0.0f;
	rect.bottom = _pBitmap->GetSize().height / 2.0f;
	rect.right = _avatar_x+_pBitmap->GetSize().width / 2.0f;
	_renderTarget->DrawBitmap(_pBitmap, &rect, 1.0f);

	//draw gold
	if (_isComingback)
		if (auto gold = Game::getSingleton()->item_mgr()->getItemBItmap(ITemType::IT_GOLD))
		{
			D2D1_RECT_F rect;
			rect.left = _fEndLinex-64;
			rect.top = _fEndLiney-64;
			rect.bottom = rect.top+128;
			rect.right = rect.left+128;
			_renderTarget->DrawBitmap(gold, &rect, 1.0f);
		}

	//draw line
	D2D1_POINT_2F pt1;
	D2D1_POINT_2F pt2;
	pt1.x = rect.left + _pBitmap->GetSize().width / 4.0f;
	pt1.y = rect.top + _pBitmap->GetSize().width / 4.0f;
	pt2.x = _fEndLinex;
	pt2.y = _fEndLiney;

	_renderTarget->DrawLine(pt1,pt2, _pLineBrush,2.0f);
}
//-------------------------------------------------------------------------
void game::Avatar::launch()
{


}
//-------------------------------------------------------------------------
inline
void game::Avatar::AS_normal(D2D1_SIZE_F size)
{
	if (Game::getSingleton()->checkInput(INPUTBUTTON::IB_Space))
	{
		_avatar_state = AvatarState::AS_Launched;
		return;
	}

	if (_bOrientation)
	{
		_avatar_x += 2;
		if (_avatar_x + _pBitmap->GetSize().width / 2 >= size.width)
			_bOrientation = !_bOrientation;
	}
	else
	{
		_avatar_x -= 2;
		if (_avatar_x <= 0)
			_bOrientation = !_bOrientation;
	}

	if (_bAngleOrientation)
	{
		_fAngle += M_PI / 256.0f;
		if (_fAngle >= M_PI_2)
			_bAngleOrientation = !_bAngleOrientation;

	}
	else
	{
		_fAngle -= M_PI / 256.0f;
		if (_fAngle <= -M_PI_2)
			_bAngleOrientation = !_bAngleOrientation;
	}

	//final 
	_fEndLinex = _fLineLength * std::sin(_fAngle) + _avatar_x + _pBitmap->GetSize().width / 4.0f;
	_fEndLiney = _fLineLength * std::cos(_fAngle) + _pBitmap->GetSize().height / 4.0f;
}
//-------------------------------------------------------------------------
void game::Avatar::AS_Launched(D2D1_SIZE_F size)
{
	/*dwon*/
	if (_bLineOrientation)
	{
		_extendLength += 2;
		if (_extendLength >= _MaxExtendLength)
			_bLineOrientation = !_bLineOrientation;

		if (Game::getSingleton()->item_mgr()->isInsectWith(_fEndLinex,_fEndLiney)==ITemType::IT_GOLD)
		{
			_bLineOrientation = !_bLineOrientation;
			_isComingback = true;
		}
	}
	/*up*/
	else
	{
		_extendLength -= 2;
		if (_extendLength <= FLT_MIN)
		{
			_bLineOrientation = true;
			_isComingback = false;
			_avatar_state = AvatarState::AS_normal;
		}
	}	
	_fEndLinex = (_fLineLength + _extendLength) * std::sin(_fAngle) + _avatar_x + _pBitmap->GetSize().width / 4.0f;
	_fEndLiney = (_fLineLength + _extendLength) * std::cos(_fAngle) + _pBitmap->GetSize().height / 4.0f;

}

