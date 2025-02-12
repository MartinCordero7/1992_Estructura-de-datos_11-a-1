#include <iostream>
#include <vector>
#include <windows.h>
#include "reina.cpp"
#include "validacion.cpp"

bool isValidInput(int N) {
    if (N < 1 || N > 8) {
        return false;
    }
    if (N >= 2 && N <= 3) {
        std::cout << "No hay solucion con este numero!" << std::endl;
        return false;
    }
    return true;
}

void drawQueen(HDC hdc, int x, int y, int cellSize) {
    HBRUSH brush = CreateSolidBrush(RGB(169, 169, 169)); // Gray color
    SelectObject(hdc, brush);

    // Draw the base of the queen
    Ellipse(hdc, x - cellSize / 4, y - cellSize / 8, x + cellSize / 4, y + cellSize / 8);

    // Draw the body of the queen
    POINT body[3] = {
        {x, y - cellSize / 4},
        {x - cellSize / 8, y},
        {x + cellSize / 8, y}
    };
    Polygon(hdc, body, 3);

    // Draw the crown of the queen
    Ellipse(hdc, x - cellSize / 16, y - cellSize / 4 - cellSize / 16, x + cellSize / 16, y - cellSize / 4 + cellSize / 16);

    DeleteObject(brush);
}

void drawBoard(HDC hdc, int N, std::vector<int>& reinas) {
    int cellSize = 50;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            RECT rect = { j * cellSize + 50, i * cellSize + 50, (j + 1) * cellSize + 50, (i + 1) * cellSize + 50 };
            HBRUSH brush = CreateSolidBrush((i + j) % 2 == 0 ? RGB(255, 255, 255) : RGB(0, 0, 0));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
        }
    }

    for (int i = 0; i < N; i++) {
        int x = reinas[i] * cellSize + cellSize / 2 + 50;
        int y = i * cellSize + cellSize / 2 + 50;
        drawQueen(hdc, x, y, cellSize);
    }

    // Draw row and column numbers outside the board
    for (int i = 0; i < N; i++) {
        char rowLabel = '1' + i;
        TextOut(hdc, 20, i * cellSize + cellSize / 2 + 50 - 5, &rowLabel, 1);
        char colLabel = 'A' + i;
        TextOut(hdc, i * cellSize + cellSize / 2 + 50 - 5, 20, &colLabel, 1);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static int N;
    static std::vector<int> reinas;

    switch (uMsg) {
    case WM_CREATE:
        N = reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ? *reinterpret_cast<int*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams) : 8;
        reinas.resize(N, -1);
        if (!solveNreinas(reinas, 0, N)) {
            MessageBox(hwnd, "No se encontro una solucion", "Error", MB_OK | MB_ICONERROR);
            PostQuitMessage(1);
        }
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        drawBoard(hdc, N, reinas);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void runProgram() {
    int N;
    std::cout << "Ingrese el tamano del tablero (1-8): ";
    N = getValidInput();

    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "NReinasClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        "NReinasClass",
        "N Reinas",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, N * 50 + 100, N * 50 + 100,
        NULL,
        NULL,
        hInstance,
        &N
    );

    if (hwnd == NULL) {
        return;
    }

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int main() {
    char choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Ingresar tamano del tablero\n";
        std::cout << "2. Salir\n";
        std::cout << "Seleccione una opcion: ";
        choice = _getch();
        std::cout << choice << std::endl;

        switch (choice) {
            case '1':
                runProgram();
                break;
            case '2':
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl;
                break;
        }
    } while (choice != '2');

    return 0;
}
