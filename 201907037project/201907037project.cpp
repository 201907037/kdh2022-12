// 201907037project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "201907037project.h"
#include <stdlib.h>
#include <time.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY201907037PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY201907037PROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY201907037PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY201907037PROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1300, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 1. 그라운드 2. 시작버튼 3. 정지버튼 4.계속 버튼 5. 마우스 커서 6.배 7.생선
RECT g_ground, g_start, g_stop, g_resume,g_m, g_ship;
RECT fish[6],trash[4];
HANDLE hfish[6],htrash[4];
int g_mx, g_my;
int sflag,ship_flag;
int indexf,indext;


DWORD WINAPI fish1(LPVOID param) {
    HWND hWnd = (HWND)param;
    //srand(time(NULL));
   int n,a,v;
    a = indexf;
   n = rand() % 2+1;
   v = rand() % 10 + 5;
    while (true) {
       if (n == 1) {

            while (fish[a].right <= g_ground.right - 10) {

                fish[a].left += v;
                fish[a].right += v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }

            while (fish[a].left >= g_ground.left + 10)
            {
                fish[a].left -= v;
                fish[a].right -= v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }
       }
       else
        {

            while (fish[a].left >= g_ground.left + 10)
            {

                fish[a].left -= v;
                fish[a].right -= v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }
        
        while (fish[a].right <= g_ground.right - 10) {
            fish[a].left += v;
            fish[a].right += v;
            InvalidateRect(hWnd, NULL, true);
            Sleep(100);
        }
       }
    } 
    return 0;
}
DWORD WINAPI trashT(LPVOID param) {
    HWND hWnd = (HWND)param;
    //srand(time(NULL));
    int n, a, v;
    a = indext;
    n = rand() % 2 + 1;
    v = rand() % 10 + 5;
    while (true) {
        if (n == 1) {

            while (trash[a].right <= g_ground.right - 10) {

                trash[a].left += v;
                trash[a].right += v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }

            while (trash[a].left >= g_ground.left + 10)
            {
                trash[a].left -= v;
                trash[a].right -= v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }
        }
        else
        {

            while (trash[a].left >= g_ground.left + 10)
            {

                trash[a].left -= v;
                trash[a].right -= v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }

            while (trash[a].right <= g_ground.right - 10) {
                trash[a].left += v;
                trash[a].right += v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }
        }
    }
    return 0;
}
//DWORD WINAPI fish2(LPVOID param) {
//    HWND hWnd = (HWND)param;
//    srand(time(NULL));
//    int n;
//    n = rand() % 2+1;
//    while (true) {
//        if (n == 1) {
//            while (g_fish2.right <= g_ground.right - 10) {
//                g_fish2.left += 10;
//                g_fish2.right += 10;
//                InvalidateRect(hWnd, NULL, true);
//                Sleep(100);
//            }
//            while (g_fish2.left >= g_ground.left + 10)
//            {
//                g_fish2.left -= 10;
//                g_fish2.right -= 10;
//                InvalidateRect(hWnd, NULL, true);
//                Sleep(100);
//            }
//        }
//        else
//        {
//            while (g_fish2.left >= g_ground.left + 10)
//            {
//                g_fish2.left -= 10;
//                g_fish2.right -= 10;
//                InvalidateRect(hWnd, NULL, true);
//                Sleep(100);
//                n--;
//            }
//            while (g_fish2.right <= g_ground.right - 10) {
//                g_fish2.left += 10;
//                g_fish2.right += 10;
//                InvalidateRect(hWnd, NULL, true);
//                Sleep(100);
//            }
//        }
//
//    }
//    return 0;
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN:
    {  
        RECT s;
        indexf = 0;
        indext = 0;
        g_mx = LOWORD(lParam);
        g_my = HIWORD(lParam);
        
        g_m.left = g_mx;
        g_m.top = g_my;
        g_m.right = g_mx + 1;
        g_m.bottom = g_my + 1;
        
        if (true == IntersectRect(&s, &g_start, &g_m)) {
            if(0==sflag){
            //MessageBox(hWnd, L"start", L"notice", MB_OK);
                for(int i=0;i<6;i++){
                    hfish[i] = CreateThread(NULL, 0, fish1, hWnd, 0, NULL);
                    indexf = i;
                    Sleep(1);
                }
                for (int i = 0; i < 4; i++) {
                    htrash[i] = CreateThread(NULL, 0, trashT, hWnd, 0, NULL);
                    indext = i;
                    Sleep(1);
                }
           
            sflag = 1;
            ship_flag = 1;
            }
            else {
                MessageBox(hWnd, L"이미 실행 중 입니다.", L"Notice", MB_OK);
            }
        }

        if (true == IntersectRect(&s, &g_stop, &g_m)) {
            //MessageBox(hWnd, L"stop", L"notice", MB_OK);
            for (int i = 0; i < 6; i++) {
            SuspendThread(hfish[i]);
            if (i < 5) {
                SuspendThread(htrash[i]);
            }
            }
            ship_flag = 0;
            
        }

        if (true == IntersectRect(&s, &g_resume, &g_m)) {
            //MessageBox(hWnd, L"재개", L"notice", MB_OK);
            for (int i = 0; i < 6; i++) {
                ResumeThread(hfish[i]);
                if (i < 5) {
                    ResumeThread(htrash[i]);
                }
            }
            ship_flag = 1;
        }
        
    }
        break;
    case WM_CREATE:
    {
        srand(time(NULL));

        g_ship.left = 430;
        g_ship.top = 100;
        g_ship.right = 530;
        g_ship.bottom = 150;

        for (int i = 0; i < 4; i++) {
            trash[i].left = 10 + (rand() % 850);
            trash[i].top = 150 + (rand() % 500);
            trash[i].right = trash[i].left + 50;
            trash[i].bottom = trash[i].top + 50;
        }

        for (int i = 0; i < 6; i++) {
            fish[i].left = 10 + (rand() % 850);
            fish[i].top = 150 + (rand() % 500);
            fish[i].right = fish[i].left + 50;
            fish[i].bottom =fish[i].top + 50;
        }

        g_resume.left = 1150;
        g_resume.top = 230;
        g_resume.right = 1250;
        g_resume.bottom = 330;

        g_stop.left = 1040;
        g_stop.top = 230;
        g_stop.right = 1140;
        g_stop.bottom = 330;

        g_start.left = 930;
        g_start.top = 230;
        g_start.right = 1030;
        g_start.bottom = 330;

        g_ground.left = 10;
        g_ground.top = 10;
        g_ground.right = 910;
        g_ground.bottom = 710;        
    }
        break;
    case WM_KEYDOWN: 
    {   if(1==ship_flag){
        switch (wParam) {
        case VK_RIGHT:
        {
            if (g_ship.right >= g_ground.right) {
                break;
            }
            else {
                g_ship.left += 10;
                g_ship.right += 10;
                InvalidateRect(hWnd, NULL, true);
            }
        }
        break;
        case VK_LEFT:
        {
            if (g_ship.left <= g_ground.left) {
                
                break;
            }
            else {
                g_ship.left -= 10;
                g_ship.right -= 10;
                InvalidateRect(hWnd, NULL, true);
            }
        }
           break;
           }
    }
    else {
        break;
    }

    }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
           
            HDC hdc = BeginPaint(hWnd, &ps);
            HFONT ssf, osf;
            HBRUSH mb, osb;
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            Rectangle(hdc, g_ground.left, g_ground.top, g_ground.right, g_ground.bottom);
            MoveToEx(hdc, 10, 150, NULL);
            LineTo(hdc, 910, 150);
            Rectangle(hdc, g_start.left, g_start.top, g_start.right, g_start.bottom);
            Rectangle(hdc, g_stop.left, g_stop.top, g_stop.right, g_stop.bottom);
            Rectangle(hdc, g_resume.left, g_resume.top, g_resume.right, g_resume.bottom);


            mb = CreateSolidBrush(RGB(125, 125, 125));
            osb = (HBRUSH)SelectObject(hdc, mb);
            Rectangle(hdc, g_ship.left, g_ship.top, g_ship.right, g_ship.bottom);
            SelectObject(hdc, osb);
            DeleteObject(mb);


            mb = CreateSolidBrush(RGB(0, 0, 255));
            osb = (HBRUSH)SelectObject(hdc, mb);
            for(int i =0;i<6;i++){
            Rectangle(hdc, fish[i].left, fish[i].top, fish[i].right, fish[i].bottom);
            }
            SelectObject(hdc, osb);
            DeleteObject(mb);


            mb = CreateSolidBrush(RGB(0, 0, 0));
            osb = (HBRUSH)SelectObject(hdc, mb);
            for (int i = 0; i < 4; i++) {
                Ellipse(hdc, trash[i].left, trash[i].top, trash[i].right, trash[i].bottom);
            }
            SelectObject(hdc, osb);
            DeleteObject(mb);
            

            ssf = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, NULL);
            osf = (HFONT)SelectObject(hdc, ssf);
            TextOut(hdc, 945, 270, L"START", 5);
            TextOut(hdc, 1060, 270, L"STOP", 4);
            TextOut(hdc, 1160, 270, L"RESUME", 6);
            SelectObject(hdc, osf);
            DeleteObject(ssf);


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
