//------------------------------
//      ItemManager.h
//		10/28/2019       created
//		10/29/2019		 modified
//		by liuxi
//-------------------------------
#pragma once
#ifndef _ITEMMANAGER_H
#define _ITEMMANAGER_H

#include <d2d1.h>
#include <wincodec.h>
#include <array>
namespace game
{
	//--------------------
	// type of contect
	//--------------------

	enum class ITemType
	{
		IT_NONE = 0, 
		IT_GOLD,
		IT_STONE
	};
	class ItemManager
	{
	public:
		ItemManager();
		~ItemManager();
		bool initialize(ID2D1HwndRenderTarget* _renderTarget);
		void render(ID2D1HwndRenderTarget* _renderTarget);
		void update(ID2D1HwndRenderTarget* _renderTarget);
		ID2D1Bitmap* getItemBItmap(ITemType type);
		ITemType isInsectWith(int x, int y);
	private:
		IWICImagingFactory* _pWicImgFactory = nullptr;
		ID2D1Bitmap* _gold_bitmap = nullptr;
		std::array<std::array<ITemType, 10>, 3> _Items;
		
	};
}
#endif // !_ITEMMANAGER_H
