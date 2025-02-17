#include "CuadradoMagico.h"

// Variable global para la suma mágica en 3x3
int targetSum3x3;

// ----------------------------------------------------------
// Funciones para la resolución manual del cuadrado 3x3
// ----------------------------------------------------------

bool solve3x3(vector<int>& nums, vector<bool>& used, int idx, int square[3][3]) {
    if(idx == 9) {
        int diag1 = square[0][0] + square[1][1] + square[2][2];
        int diag2 = square[0][2] + square[1][1] + square[2][0];
        return (diag1 == targetSum3x3 && diag2 == targetSum3x3);
    }
    int i = idx / 3, j = idx % 3;
    for (int k = 0; k < 9; k++) {
        if (!used[k]) {
            square[i][j] = nums[k];
            used[k] = true;
            if(j == 2) {
                int rowSum = square[i][0] + square[i][1] + square[i][2];
                if(rowSum != targetSum3x3) { 
                    used[k] = false; 
                    continue; 
                }
            }
            if(i == 2) {
                int colSum = square[0][j] + square[1][j] + square[2][j];
                if(colSum != targetSum3x3) {
                    used[k] = false;
                    continue;
                }
            }
            if(solve3x3(nums, used, idx+1, square))
                return true;
            used[k] = false;
        }
    }
    return false;
}

bool solveManual3x3(int square[3][3]) {
    vector<int> nums(9);
    cout << "Ingrese 9 numeros (separados por espacio o enter): ";
    for(int i = 0; i < 9; i++)
        cin >> nums[i];
    int total = 0;
    for (int num : nums) total += num;
    if(total % 3 != 0) {
        cout << "La suma total (" << total << ") no es divisible por 3, no se puede formar un cuadrado magico.\n";
        return false;
    }
    if(total % 9 != 0) {
        cout << "La suma total (" << total << ") no es divisible por 9.\n";
        cout << "En un cuadrado 3x3 el valor central debe ser (suma total)/9.\n";
        return false;
    }
    int centerValue = total / 9;
    if(find(nums.begin(), nums.end(), centerValue) == nums.end()){
        cout << "El valor central (" << centerValue << ") no se encuentra entre los numeros ingresados.\n";
        return false;
    }
    targetSum3x3 = total / 3;
    vector<bool> used(9, false);
    return solve3x3(nums, used, 0, square);
}

// ----------------------------------------------------------
// Funciones para la resolución manual del cuadrado 4x4
// ----------------------------------------------------------

bool isArithmeticProgression(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int d = nums[1] - nums[0];
    for (size_t i = 2; i < nums.size(); i++) {
        if (nums[i] - nums[i-1] != d)
            return false;
    }
    return true;
}

void generar4x4Template(int cuadrado[4][4]) {
    int num = 1;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            cuadrado[i][j] = num++;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(i == j || i + j == 3)
                cuadrado[i][j] = 17 - cuadrado[i][j];
}

bool solveManual4x4(int square[4][4]) {
    vector<int> nums(16);
    cout << "Ingrese 16 numeros (separados por espacio o enter): ";
    for (int i = 0; i < 16; i++)
        cin >> nums[i];
    vector<int> sortedNums = nums;
    sort(sortedNums.begin(), sortedNums.end());
    if (!isArithmeticProgression(sortedNums)) {
        cout << "Los numeros ingresados no forman una progresion aritmetica.\n";
        return false;
    }
    int templateSquare[4][4];
    generar4x4Template(templateSquare);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            int k = templateSquare[i][j];
            square[i][j] = sortedNums[k - 1];
        }
    return true;
}

// ----------------------------------------------------------
// Funciones para generar automaticamente los cuadrados
// ----------------------------------------------------------

void generar3x3(int cuadrado[3][3]) {
    int n = 3, num = 1, fila = 0, col = 1;
    // ...existing code...
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cuadrado[i][j] = 0;
    while(num <= n*n) {
        if(cuadrado[fila][col] == 0) {
            cuadrado[fila][col] = num++;
            int nuevaFila = (fila - 1 + n) % n, nuevaCol = (col + 1) % n;
            if(cuadrado[nuevaFila][nuevaCol] != 0)
                fila = (fila + 1) % n;
            else {
                fila = nuevaFila;
                col = nuevaCol;
            }
        } else {
            fila = (fila + 1) % n;
        }
    }
}

void generar4x4(int cuadrado[4][4]) {
    int num = 1;
    // ...existing code...
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            cuadrado[i][j] = num++;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(i == j || i + j == 3)
                cuadrado[i][j] = 17 - cuadrado[i][j];
}

// ----------------------------------------------------------
// Funciones para mostrar los cuadrados (consola y grafico)
// ----------------------------------------------------------

void imprimir3x3(int cuadrado[3][3]) {
    cout << "\nCuadrado 3x3:\n";
    // ...existing code...
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            cout << cuadrado[i][j] << "\t";
        cout << "\n";
    }
}

void imprimir4x4(int cuadrado[4][4]) {
    cout << "\nCuadrado 4x4:\n";
    // ...existing code...
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
            cout << cuadrado[i][j] << "\t";
        cout << "\n";
    }
}

void mostrarGrafico3x3(int cuadrado[3][3]) {
    int gd = DETECT, gm;
    initwindow(600, 600, "Cuadrado Magico 3x3");
    int cell = 200;
    // ...existing code para dibujar lineas y numeros...
    for(int i = 0; i <= 3; i++){
        line(0, i * cell, 600, i * cell);
        line(i * cell, 0, i * cell, 600);
    }
    settextstyle(4, 0, 3);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            stringstream ss; ss << cuadrado[i][j];
            string numStr = ss.str();
            char buffer[10]; strcpy(buffer, numStr.c_str());
            outtextxy(j * cell + 80, i * cell + 80, buffer);
        }
    }
    getch();
    closegraph();
}

void mostrarGrafico4x4(int cuadrado[4][4]) {
    int gd = DETECT, gm;
    initwindow(800, 800, "Cuadrado Magico 4x4");
    int cell = 200;
    // ...existing code para dibujar lineas y numeros...
    for(int i = 0; i <= 4; i++){
        line(0, i * cell, 800, i * cell);
        line(i * cell, 0, i * cell, 800);
    }
    settextstyle(4, 0, 3);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            stringstream ss; ss << cuadrado[i][j];
            string numStr = ss.str();
            char buffer[10]; strcpy(buffer, numStr.c_str());
            outtextxy(j * cell + 80, i * cell + 80, buffer);
        }
    }
    getch();
    closegraph();
}
