//------------------------------
//     ScoreMgr.cpp
//		10/31/2019       created
//		10/31/2019		 modified
//		by liuxi
//-------------------------------
#include "ScoreMgr.h"
#include "ConcreteArguments.hpp"

game::ScoreMgr::ScoreMgr()
{
}

game::ScoreMgr::~ScoreMgr()
{
}

void game::ScoreMgr::on_update(MessageType mt, std::shared_ptr<MsgArgument> args)
{
	if (mt!=MessageType::MT_SCORE)
		return;

	auto score_arg = std::static_pointer_cast<ScoreArg>(args);
	if (!score_arg)
		return;

	if (score_arg->_score_type == ScoreType::ST_Increase)
		_score += 100;
	else
		_score -= 100;
}

bool game::ScoreMgr::initialize(ID2D1HwndRenderTarget * _renderTarget)
{
	IDWriteFactory* dwFactory = nullptr;
	HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&dwFactory));
	if (FAILED(hr))
		return false;

	//创建文本format
	
	hr = dwFactory->CreateTextFormat(L"Cambria",nullptr,
		DWRITE_FONT_WEIGHT_REGULAR,DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,48.0f,L"en-us",&_format);
	if (FAILED(hr))
		return false;

	hr = _renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f,1.0f,0.0f,1.0f)/*D2D1::ColorF(D2D1::ColorF::PaleVioletRed)*/, &_pTextBrush);

	if (FAILED(hr))
		return false;

	dwFactory->Release();

	return true;
}

void game::ScoreMgr::render(ID2D1HwndRenderTarget * _renderTarget)
{
	if (!_renderTarget)
		return;
	D2D1_RECT_F rect;
	rect.left = 0.0f;
	rect.top = 0.0f;
	rect.right = 150.0f;
	rect.bottom = 10.0f;

	auto str_score = std::to_wstring(_score);

	_renderTarget->DrawTextW(str_score.c_str(), str_score.length(), _format, rect, _pTextBrush);

}
