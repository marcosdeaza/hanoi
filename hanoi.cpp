#include <iostream>
#include <vector>
#include <cmath>    // Para pow
#include <thread>   // Lo pide el enunciado
#include <chrono>   // Lo pide el enunciado

using namespace std;

//La función a dibujar
void dibujarTorres(vector<int> A, vector<int> B, vector<int> C, int n) {
    // Limpiamos un poco la pantalla con saltos de linea
    cout << "\n\n\n\n";

    // Dibujamos de arriba a abajo
    for (int i = n - 1; i >= 0; i--) {
        // Torre A
        if (i < A.size()) cout << "   (" << A[i] << ")   ";
        else cout << "    |    ";

        // Torre B
        if (i < B.size()) cout << "   (" << B[i] << ")   ";
        else cout << "    |    ";

        // Torre C
        if (i < C.size()) cout << "   (" << C[i] << ")   ";
        else cout << "    |    ";
        
        cout << endl;
    }
    cout << "  TORRE A    TORRE B    TORRE C" << endl;
    cout << "-----------------------------------" << endl;
}

// Funcion para mover disco de una torre a otra validando quien es mas pequeño
// Se pasan con & para que los cambios se guarden (paso por referencia)
void moverDisco(vector<int> &origen, vector<int> &destino, string nombreOrigen, string nombreDestino) {
    
    // Sacamos los discos de arriba (si estan vacias ponemos un 0)
    int disco1 = 0;
    if (origen.size() > 0) {
        disco1 = origen.back();
    }

    int disco2 = 0;
    if (destino.size() > 0) {
        disco2 = destino.back();
    }

    // Si la origen esta vacia, toca mover DESDE el destino HACIA el origen
    if (disco1 == 0) {
        origen.push_back(disco2);
        destino.pop_back();
        cout << "Moviendo disco " << disco2 << " de " << nombreDestino << " a " << nombreOrigen << endl;
    }
    // Si la destino esta vacia, movemos normal
    else if (disco2 == 0) {
        destino.push_back(disco1);
        origen.pop_back();
        cout << "Moviendo disco " << disco1 << " de " << nombreOrigen << " a " << nombreDestino << endl;
    }
    // Si ninguna esta vacia, movemos el pequeño sobre el grande
    else if (disco1 < disco2) {
        destino.push_back(disco1);
        origen.pop_back();
        cout << "Moviendo disco " << disco1 << " de " << nombreOrigen << " a " << nombreDestino << endl;
    }
    else {
        // El disco 2 es mas pequeño, asi que movemos el 2 al 1
        origen.push_back(disco2);
        destino.pop_back();
        cout << "Moviendo disco " << disco2 << " de " << nombreDestino << " a " << nombreOrigen << endl;
    }
}

int main() {
    int n;

    // 1. Pedir numero
    cout << "Numero de discos: ";
    cin >> n;

    while (n <= 0) {
        cout << "Error, dame un positivo: ";
        cin >> n;
    }

    // Inicializamos las torres
    vector<int> A;
    vector<int> B;
    vector<int> C;

    // Llenamos la A
    for (int i = n; i >= 1; i--) {
        A.push_back(i);
    }

    // Dibujo inicial
    dibujarTorres(A, B, C, n);
    this_thread::sleep_for(chrono::seconds(2));

    // Calculamos total de movimientos: 2 elevado a n, menos 1
    int total = pow(2, n) - 1;

    // Si par cambia secuencia de movimiento


    if (n % 2 == 0) {
        // --- MODO PAR --- (Secuencia: A-B, A-C, B-C)
        for (int i = 1; i <= total; i++) {
            
            if (i % 3 == 1) {
                moverDisco(A, B, "A", "B");
            }
            else if (i % 3 == 2) {
                moverDisco(A, C, "A", "C");
            }
            else if (i % 3 == 0) {
                moverDisco(B, C, "B", "C");
            }

            dibujarTorres(A, B, C, n);
            this_thread::sleep_for(chrono::seconds(2));
        }
    } 
    else {
        // --- MODO IMPAR --- (Secuencia: A-C, A-B, B-C)
        for (int i = 1; i <= total; i++) {
            
            if (i % 3 == 1) {
                moverDisco(A, C, "A", "C"); // Cambio aqui
            }
            else if (i % 3 == 2) {
                moverDisco(A, B, "A", "B"); // Cambio aqui
            }
            else if (i % 3 == 0) {
                moverDisco(B, C, "B", "C"); // Este se queda igual
            }

            dibujarTorres(A, B, C, n);
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    return 0;
}