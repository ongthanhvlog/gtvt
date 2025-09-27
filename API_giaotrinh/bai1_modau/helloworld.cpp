#include <windows.h>
// Hàm xử lý thông điệp của cửa sổ
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message)
    {
    case WM_PAINT: // Khi cần vẽ lại cửa sổ
        hdc = BeginPaint(hwnd, &ps); // Bắt đầu vẽ
        GetClientRect(hwnd, &rect);  // Lấy kích thước vùng vẽ

        // Vẽ dòng chữ "Hello World" ở giữa cửa sổ
        DrawText(hdc, TEXT("Hello World"), -1, &rect,
                 DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        EndPaint(hwnd, &ps); // Kết thúc vẽ
        return 0;

    case WM_CLOSE: // Khi người dùng bấm nút X
        if (MessageBox(hwnd, TEXT("Bạn có muốn thoát không?"), TEXT("Xác nhận"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK) {
            DestroyWindow(hwnd); // Đóng cửa sổ
        }
        return 0;

    case WM_DESTROY: // Khi cửa sổ bị hủy
        PostQuitMessage(0); // Thoát chương trình
        return 0;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam); // Xử lý mặc định
    }
}

// Hàm chính - điểm khởi đầu chương trình Win32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("HelloApp"); // Tên lớp cửa sổ
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    // Cấu hình lớp cửa sổ
    wndclass.style = CS_HREDRAW | CS_VREDRAW;        // Vẽ lại khi thay đổi kích thước
    wndclass.lpfnWndProc = WndProc;                  // Hàm xử lý thông điệp
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;                  // Ứng dụng hiện tại
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);// Icon mặc định
    wndclass.hCursor = LoadCursor(NULL, IDC_HAND);   // Con trỏ chuột hình bàn tay
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Màu nền cửa sổ
    wndclass.lpszMenuName = NULL;                    // Không dùng menu
    wndclass.lpszClassName = szAppName;              // Tên lớp

    // Đăng ký lớp cửa sổ
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Lỗi khi đăng ký lớp cửa sổ!"), szAppName, MB_ICONERROR);
        return 0;
    }

    // Tạo cửa sổ
    hwnd = CreateWindow(szAppName,                // Tên lớp
                        TEXT("Chương trình Hello World"), // Tiêu đề cửa sổ
                        WS_OVERLAPPEDWINDOW,      // Kiểu cửa sổ
                        CW_USEDEFAULT,            // Vị trí X
                        CW_USEDEFAULT,            // Vị trí Y
                        CW_USEDEFAULT,            // Chiều rộng
                        CW_USEDEFAULT,            // Chiều cao
                        NULL, NULL, hInstance, NULL);

    // Hiển thị và cập nhật cửa sổ
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    // Vòng lặp thông điệp
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); // Dịch phím
        DispatchMessage(&msg);  // Gửi đến WndProc
    }

    return (int)msg.wParam; // Kết thúc chương trình
}
