
#include <Windows.h>
#include <wchar.h>
#include "image.h"
#include "bitmap.h"
#include "resource.h"
#include "Keyboard.h"
#include "D3DGraphics.h"
#include "Mat.h"
#include "unit_test.h"
#include "filter.h"
static KeyboardServer kServ;

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
			switch( wParam )
			{
			case VK_UP:
				kServ.OnUpPressed();
				break;
			case VK_DOWN:
				kServ.OnDownPressed();
				break;
			case VK_LEFT:
				kServ.OnLeftPressed();
				break;
			case VK_RIGHT:
				kServ.OnRightPressed();
				break;
			case VK_SPACE:
                kServ.OnSpacePressed();
				break;
			case VK_RETURN:
				kServ.OnEnterPressed();
				break;
			}
			break;
		case WM_KEYUP:
   			switch( wParam )
			{
			case VK_UP:
				kServ.OnUpReleased();
				break;
			case VK_DOWN:
				kServ.OnDownReleased();
				break;
			case VK_LEFT:
				kServ.OnLeftReleased();
				break;
			case VK_RIGHT:
				kServ.OnRightReleased();
				break;
			case VK_SPACE:
				kServ.OnSpaceReleased();
				break;
			case VK_RETURN:
				kServ.OnEnterReleased();
				break;
			}
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}






int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR,INT )
{
	WNDCLASSEX wc = { sizeof( WNDCLASSEX ),CS_CLASSDC,MsgProc,0,0,
                      GetModuleHandle( NULL ),NULL,NULL,NULL,NULL,
                      "DirectX Framework Window",NULL };
    wc.hIconSm = (HICON)LoadImage( hInst,MAKEINTRESOURCE( IDI_APPICON16 ),IMAGE_ICON,16,16,0 );
	wc.hIcon   = (HICON)LoadImage( hInst,MAKEINTRESOURCE( IDI_APPICON32 ),IMAGE_ICON,32,32,0 );
    RegisterClassEx( &wc );
	
	RECT wr;
	wr.left = 100;
	wr.right = 1000 + wr.left;
	wr.top = 100;
	wr.bottom = 600 + wr.top;
	AdjustWindowRect( &wr,WS_OVERLAPPEDWINDOW,FALSE );
    HWND hWnd = CreateWindow( "DirectX Framework Window","startbmp",
                              WS_OVERLAPPEDWINDOW,wr.left,wr.top,wr.right-wr.left,wr.bottom-wr.top,
                              NULL,NULL,wc.hInstance,NULL );

    ShowWindow( hWnd,SW_SHOWDEFAULT );
    UpdateWindow( hWnd );


	img_config config;
	D3DCOLOR surface[30000];
	LoadBmp(config, surface, "6.bmp");




	D3DGraphics d3d(hWnd);           //初始化D3DGraphics对象

	image img(d3d, surface, config);
    MSG msg;

	img.Grayscale(1);  //1为max法 2为均值法 3为加权均值
   
	//Mat mkk(img.get_img_config(),img.get_final_surface());   //把D3D转换为矩阵
	//filter fi(mkk);
	
	double** test_mat = test::get_mat();
	//test::show_mat(test_mat, 3, 3);
	Mat *t_mat=new Mat(test_mat, 3, 3);
	filter t_fil(t_mat);
	t_fil.boxblur(3, 3);
	kernel *ke = t_fil.get_kernel();
	test::show_mat(ke->kernel_mat, ke->main_config.first, ke->main_config.second);
	/*test::show_mat(t_fil.convolution(),4,4);*/
	
	
	
	//img.ConverTo_Fourier_atlas(m);
	
	//m.dft();
	/*m.get_fourier_surface();*/
	/*m.show_main_mat();*/
	//D3DCOLOR m = D3DCOLOR_ARGB(0, 100, 102, 103);
	//int mm =(int)img.to_matrix_max(m);



    ZeroMemory( &msg,sizeof( msg ) );
    while( msg.message != WM_QUIT )
    {
        if( PeekMessage( &msg,NULL,0,0,PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
		{
			const int constFps = 90;
			float timeInOneFps = 1000.0f / constFps;    // 每秒60帧，则1帧就是约16毫秒
			DWORD timeBegin = GetTickCount();



			d3d.BeginFrame();
			img.show_final_image();
			//img.show_fourier_image();
			d3d.EndFrame();



			DWORD timeTotal = GetTickCount() - timeBegin;
			if (timeTotal < timeInOneFps)
				Sleep(DWORD(timeInOneFps - timeTotal));
		}
	}

    UnregisterClass( "DirectX Framework Window",wc.hInstance );
    return 0;
}