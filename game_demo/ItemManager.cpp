//------------------------------
//      ItemManager.cpp
//		10/28/2019       created
//		10/29/2019		 modified
//		by liuxi
//-------------------------------
#include "ItemManager.h"

using namespace game;

//-------------------------------------------------------------------------
game::ItemManager::ItemManager()
{
}
//-------------------------------------------------------------------------
game::ItemManager::~ItemManager()
{
}
//-------------------------------------------------------------------------
bool game::ItemManager::initialize(ID2D1HwndRenderTarget * _renderTarget)
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


	hResult = pDecoder->GetFrame(0, &pSource);
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
		pConverter, nullptr, &_gold_bitmap);


	if (FAILED(hResult))
		return false;

	pDecoder->Release();
	pConverter->Release();
	_pWicImgFactory->Release();
	pSource->Release();
	/*initalize items*/
	for (auto& line : _Items)
		for (auto& column : line)
			column = ITemType::IT_NONE;

	_Items[0][3] = ITemType::IT_GOLD;
	_Items[1][6] = ITemType::IT_GOLD;
	_Items[2][7] = ITemType::IT_STONE;
	return true;

}
//-------------------------------------------------------------------------
void game::ItemManager::render(ID2D1HwndRenderTarget * _renderTarget)
{
	if (!_renderTarget)
		return;
	for (int i = 0; i < 3; ++i)
	{
		for ( int j = 0; j < 10 ; ++j)
		{
			if (_Items[i][j] == ITemType::IT_GOLD)
			{
				D2D1_RECT_F rect;
				rect.left = j * 128;
				rect.right = rect.left + 128;
				rect.top = i * 128 +250;
				rect.bottom = rect.top + 128;
				_renderTarget->DrawBitmap(_gold_bitmap,&rect,1.0f);
			}
		}

	}
}
//-------------------------------------------------------------------------
void game::ItemManager::update(ID2D1HwndRenderTarget * _renderTarget)
{
}
//-------------------------------------------------------------------------
ID2D1Bitmap * game::ItemManager::getItemBItmap(ITemType type)
{
	return _gold_bitmap;
}
//-------------------------------------------------------------------------
ITemType game::ItemManager::isInsectWith(int x, int y)
{
	if (y < 250)
		return ITemType::IT_NONE;
	
	int index_x = x / 128;
	int index_y = (y - 250) / 128;
	
	if (index_x > 9 || index_y > 2)
		return ITemType::IT_NONE;
	
	if (_Items[index_y][index_x] != ITemType::IT_NONE)
	{
		auto type = _Items[index_y][index_x];
		_Items[index_y][index_x] = ITemType::IT_NONE;
		return type;
	}

	return ITemType::IT_NONE;
}
