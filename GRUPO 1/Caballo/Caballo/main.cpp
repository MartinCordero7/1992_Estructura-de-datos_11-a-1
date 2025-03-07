/**********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Viernes,  Lunes, 17 de Febrero de 2025
 * FECHA MODIFICACION: Lunes, 17 de Febrero de 2025
 * PROYECTO:Caballo
 * Nivel: TERCERO     NRC: 1992
 ***********/
#include <iostream>
#include <iomanip>
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>  // Agregamos windows.h para mejor compatibilidad
#include <fstream>
using namespace std;

class TableroCaballo {
private:
    int tablero[8][8];
    int movFila[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int movColumna[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int pasos;
    const int TAMANO_CELDA = 50;
    const int MARGEN = 50;
    bool posicionesPosibles[8][8];  // Nueva matriz para movimientos posibles

public:
    TableroCaballo() {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                tablero[i][j] = 0;
                posicionesPosibles[i][j] = false;
            }
        }
        pasos = 1;
    }

    bool movimientoValido(int fila, int columna) {
        return (fila >= 0 && fila < 8 && columna >= 0 && columna < 8 && tablero[fila][columna] == 0);
    }

    void marcarMovimientosPosibles(int fila, int columna) {
        for(int i = 0; i < 8; i++) {
            int nuevaFila = fila + movFila[i];
            int nuevaColumna = columna + movColumna[i];
            
            if(movimientoValido(nuevaFila, nuevaColumna)) {
                posicionesPosibles[nuevaFila][nuevaColumna] = true;
            }
        }
    }

    void limpiarPosicionesPosibles() {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                posicionesPosibles[i][j] = false;
            }
        }
    }

    bool hayMovimientosValidos(int fila, int columna) {
        for(int i = 0; i < 8; i++) {
            int nuevaFila = fila + movFila[i];
            int nuevaColumna = columna + movColumna[i];
            if(movimientoValido(nuevaFila, nuevaColumna)) {
                return true;
            }
        }
        return false;
    }

    pair<int, int> seleccionarSiguienteMovimiento(int filaActual, int columnaActual) {
        limpiarPosicionesPosibles();
        marcarMovimientosPosibles(filaActual, columnaActual);
        dibujarTablero();
        dibujarCaballo(filaActual, columnaActual);
        
        pair<int, int> seleccion = obtenerCasillaDelMouse();
        while(seleccion.first != -1 && !posicionesPosibles[seleccion.first][seleccion.second]) {
            seleccion = obtenerCasillaDelMouse();
        }
        return seleccion;
    }

    void jugarInteractivo(int filaInicial, int columnaInicial) {
        int filaActual = filaInicial;
        int columnaActual = columnaInicial;
        tablero[filaActual][columnaActual] = pasos++;
        
        while(hayMovimientosValidos(filaActual, columnaActual)) {
            pair<int, int> siguiente = seleccionarSiguienteMovimiento(filaActual, columnaActual);
            if(siguiente.first == -2) { // Si se presionó ESC
                closegraph();
                exit(0);
            }
            if(siguiente.first == -1) break;
            
            filaActual = siguiente.first;
            columnaActual = siguiente.second;
            tablero[filaActual][columnaActual] = pasos++;
            guardarMovimientos();
        }
        
        dibujarTablero();
        dibujarCaballo(filaActual, columnaActual);
        if(!hayMovimientosValidos(filaActual, columnaActual)) {
            setcolor(RED);
            outtextxy(10, 500, "No hay mas movimientos posibles!");
        }
    }

    void dibujarTablero() {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                int x = MARGEN + j * TAMANO_CELDA;
                int y = MARGEN + i * TAMANO_CELDA;
                
                // Alternar colores del tablero
                if((i + j) % 2 == 0)
                    setfillstyle(SOLID_FILL, WHITE);
                else
                    setfillstyle(SOLID_FILL, DARKGRAY);
                
                bar(x, y, x + TAMANO_CELDA, y + TAMANO_CELDA);
                rectangle(x, y, x + TAMANO_CELDA, y + TAMANO_CELDA);

                // Dibujar número si la casilla fue visitada
                if(tablero[i][j] > 0) {
                    char numero[3];
                    sprintf(numero, "%d", tablero[i][j]);
                    setcolor(RED);
                    outtextxy(x + TAMANO_CELDA/3, y + TAMANO_CELDA/3, numero);
                }

                // Agregar marcadores para movimientos posibles
                if(posicionesPosibles[i][j]) {
                    setcolor(GREEN);
                    circle(x + TAMANO_CELDA/2, y + TAMANO_CELDA/2, 5);
                }
            }
        }
    }

    void dibujarCaballo(int fila, int columna) {
        int x = MARGEN + columna * TAMANO_CELDA + TAMANO_CELDA/4;
        int y = MARGEN + fila * TAMANO_CELDA + TAMANO_CELDA/4;
        
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        circle(x, y, 10);
        floodfill(x, y, BLUE);
    }

    void moverCaballo(int fila, int columna) {
        tablero[fila][columna] = pasos++;
        dibujarTablero();
        dibujarCaballo(fila, columna);
        delay(500); // Pausa para ver el movimiento
        
        for(int i = 0; i < 8; i++) {
            int nuevaFila = fila + movFila[i];
            int nuevaColumna = columna + movColumna[i];
            
            if(movimientoValido(nuevaFila, nuevaColumna)) {
                moverCaballo(nuevaFila, nuevaColumna);
            }
        }
    }

    void guardarMovimientos() {
        ofstream archivo("movimientos.txt");
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                archivo << (tablero[i][j] > 0 ? "1" : "0") << " ";
            }
            archivo << endl;
        }
        archivo.close();
    }

    pair<int, int> obtenerCasillaDelMouse() {
        int x, y;
        while(!ismouseclick(WM_LBUTTONDOWN)) {
            if(kbhit() && getch() == 27) { // 27 es el código ASCII para ESC
                return make_pair(-2, -2); // Código especial para ESC
            }
            delay(100);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);

        int fila = (y - MARGEN) / TAMANO_CELDA;
        int columna = (x - MARGEN) / TAMANO_CELDA;

        if(fila >= 0 && fila < 8 && columna >= 0 && columna < 8) {
            return make_pair(fila, columna);
        }
        return make_pair(-1, -1);
    }

    void mostrarTablero() {
        cout << "   ";
        for(int i = 0; i < 8; i++) {
            cout << setw(4) << i;
        }
        cout << endl;

        for(int i = 0; i < 8; i++) {
            cout << setw(2) << i << " ";
            for(int j = 0; j < 8; j++) {
                cout << setw(4) << tablero[i][j];
            }
            cout << endl;
        }
    }
};

int main() {
    // Inicialización mejorada de gráficos
    int gd = DETECT, gm;
    char driver[] = "";  // Path vacío para auto-detección
    
    // Inicializar gráficos con manejo de errores
    initwindow(600, 600, "Recorrido del Caballo");  // Ventana de 600x600 píxeles
    
    if (graphresult() != grOk) {
        cout << "Error al inicializar modo grafico: " << grapherrormsg(graphresult()) << endl;
        return 1;
    }

    // Establecer color de fondo
    setbkcolor(LIGHTGRAY);
    cleardevice();

    // registermouse(); // Registrar el mouse

    TableroCaballo juego;
    int fila, columna;

    // Mostrar instrucciones en la ventana gráfica
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(BLUE);
    outtextxy(10, 10, "Haga clic en una casilla para seleccionar la posicion inicial del caballo");

    cout << "Haga clic en una casilla para seleccionar la posicion inicial del caballo" << endl;

    juego.dibujarTablero();
    
    pair<int, int> posicion = juego.obtenerCasillaDelMouse();
    
    if(posicion.first == -2) { // Si se presionó ESC
        closegraph();
        return 0;
    } else if(posicion.first != -1) {
        juego.jugarInteractivo(posicion.first, posicion.second);
        getch();
    } else {
        outtextxy(100, 100, "Posicion invalida!");
        delay(2000);
    }

    closegraph();
    return 0;
}
