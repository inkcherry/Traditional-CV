

#pragma once
#include <d3d9.h>
#define BASEWIDTH 930
#define BASEHEIGHT 530
class D3DGraphics
{
private:
	IDirect3D9*			pDirect3D;     //D3D对象
	IDirect3DDevice9*	pDevice;      //获取设备的行能，硬件设备对象  构造函数中通过version指定了其版本 


public:
	enum DirectionState
	{
		UP,             //0
		DOWN,             //1
		LEFT,           //2
		RIGHT,         //3
	};
	D3DGraphics(HWND hWnd);
	~D3DGraphics();
	void PutPixel(int x, int y, int r, int g, int b);
	void BeginFrame();
	void EndFrame();
	

	void PutPixel(int x, int y, D3DCOLOR c)    //重载PutPixel
	{

		IDirect3DSurface9* pBackBuffer = NULL;
		D3DLOCKED_RECT rect;
		D3DGraphics::pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
		pBackBuffer->LockRect(&rect, NULL, NULL);
		((D3DCOLOR*)rect.pBits)[x + (rect.Pitch >> 2) * y] = c;
		pBackBuffer->UnlockRect();
		pBackBuffer->Release();
	}

};