#include<windows.h>
//định nghĩa WndProc
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
    WNDCLASS wndclass; 
    static TCHAR szAppName[] = TEXT("Ví dụ 1");
    //cau hinh lop cua so
    wndclass.style = CS_HREDRAW | CS_VREDRAW; //Ve lai khi thay doi kich thuoc
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance; 
    wndclass.hInstance = hInstance;                  // Ứng dụng hiện tại
    //thay đổi biểu tượng icon
    //wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);// Icon mặc định
    wndclass.hIcon = (HICON)LoadImage(NULL, TEXT("C:\\GTVT\\API_giaotrinh\\baiktra\\317714_video_youtube_icon.ico"),
                IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    //con trỏ chuột tùy ý
    wndclass.hCursor = LoadCursor(NULL, IDC_HAND);   // Con trỏ chuột hình bàn tay

    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Màu nền cửa sổ
    wndclass.lpszMenuName = NULL;                    // Không dùng menu
    wndclass.lpszClassName = szAppName;              // Tên lớp
    //đăng kí lớp cửa sổ 
    if (!RegisterClass(&wndclass)){
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }
    //tạo cửa sổ
     HWND hwnd = CreateWindow(szAppName,  //Tên lớp cửa sổ 
        TEXT("Bài kiểm tra"), //Tiêu đề
        WS_OVERLAPPEDWINDOW, //Kiểu cửa sổ
        CW_USEDEFAULT, CW_USEDEFAULT, //Tọa độ trên bên trái của cửa sổ
        CW_USEDEFAULT, CW_USEDEFAULT, //Kích thước của cửa sổ 
        NULL, NULL, hInstance, NULL); //chỉ số của cửa sổ cha, menu, chỉ số cửa sổ hiện tại
        ShowWindow(hwnd, iCmdShow);
        UpdateWindow(hwnd);
    // Vòng lặp thông điệp
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); // Dịch phím
        DispatchMessage(&msg);  // Gửi đến WndProc
    }

}