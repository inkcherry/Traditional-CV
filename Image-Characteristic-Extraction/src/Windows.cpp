
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
#include "morph.h"
static KeyboardServer kServ;
D3DGraphics* gobal_d3d;


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
	LoadBmp(config, surface, "line.bmp");




	D3DGraphics d3d(hWnd);           //初始化D3DGraphics对象
	gobal_d3d = &d3d;                //unit_test的d3d指针



	

	image img(d3d, surface, config);
	/*test::show_d3dmat(surface, 55, 29);*/
    MSG msg;







	//img.Grayscale(1);  //1为max法 2为均值法 3为加权均值

	/*unit::test_init_kernel();*/   //核生成测试

	//unit::test_bliateralblur();  //双边滤波测试
	/*unit::test_medianblur();*/   //中值滤波测试
	/*double ** after=unit::test_conv();*/
	/*Mat w(after, 3, 3);*/

	/*unit::test_morph();*/
	//unit::test_morph2();
	/*unit::test_morph3();*/
	/*unit::test_sobel();*/
	/*unit::test_laplace();*/

	Mat *mkk = new Mat(img.get_img_config(),img.get_inital_surface());   //把D3D转换为矩阵





	//mkk.show_main_mat();
	//mkk.show_ascii_art();
															 
															 //
						//Mat* pmk[3];
						//pmk[0] = &mkk;  //0是原始的
						//filter fi(pmk[0]);


					 //   pmk[1]=fi.bliateralblur(60,100,100);
					 //   pmk[2]=fi.medianblur();
						///*fi.GaussianBlur(3, 1);*/

						//pmk[0]->show_main_mat();


						//shared_ptr<D3DCOLOR>sp_temp_d3d_mat[3];

						//image* pimage[3];

						//for (int i = 0; i < 3; i++)  // 玩点为数组转换提供一个接口
						//{
						//	sp_temp_d3d_mat[i] = pmk[i]->conver_to_d3dmat();
						//	pimage[i]=new image(d3d, sp_temp_d3d_mat[i].get(), pmk[i]->get_img_config());
						//}

						//pmk[1]->show_main_mat();

						//shared_ptr<D3DCOLOR>test_c=mkk.conver_to_d3dmat();
						//image test(d3d,test_c.get(), mkk.get_img_config());
						////filter fi(mkk);
						//



						//int test_width = mkk.get_img_config().first;
						//int test_height = mkk.get_img_config().second;


						//D3DCOLOR *temp = test.get_inital_surface();






	/*test::show_d3dmat(temp, test_width, test_height);
*/

	
	/*test::show_mat(t_fil.convolution(),4,4);*/
	
	
	
	//img.ConverTo_Fourier_atlas(m);
	
	//m.dft();
	/*m.get_fourier_surface();*/  //傅里叶变换测试
	/*m.show_main_mat();*/
	//D3DCOLOR m = D3DCOLOR_ARGB(0, 100, 102, 103);
	//int mm =(int)img.to_matrix_max(m);

	//test::show_d3dmat(img.get_inital_surface(), config.first, config.second);



	image* res_img ;
	//image** after_threshold_mat;

	res_img=unit::test_hough(mkk);

	//调试内容
	//int a = (int)res_img[0];
	//int b = (int)res_img[1];
	//res_img[0]->show_digital_mat();

	//调试内容
	//Mat test123(res_img[0]->get_img_config(), res_img[0]->get_inital_surface());



	/*test123.show_main_mat();*/


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
			img.s_show_initial_image(300, 300);
			res_img->show_initial_image(100, 100);
		
			
		/*	for (int i = 0; i < 3; i++)
			{
				pimage[i]->show_initial_image((i + 1) * 100, (i + 1) * 100);
			}
			*/
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