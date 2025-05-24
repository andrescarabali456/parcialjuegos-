#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Pokemon {
    string nombre;
    int vida;
    int ataque1_danio;
    int ataque2_danio;
};

void mostrarPokemons() {
    cout << "1. Pikachu\n";
    cout << "2. Charmander\n";
    cout << "3. Bulbasaur\n";
    cout << "4. Squirtle\n";
}

Pokemon elegirPokemon(int eleccion) {
    switch(eleccion) {
        case 1: return {"Pikachu", 100, 20, 25};
        case 2: return {"Charmander", 110, 22, 20};
        case 3: return {"Bulbasaur", 120, 18, 23};
        case 4: return {"Squirtle", 130, 15, 18};
        default: return {"Pikachu", 100, 20, 25}; // Default
    }
}

void ajustarDificultad(Pokemon &enemigo, int dificultad) {
    // Facil: menos vida y danio para la maquina
    if (dificultad == 1) {
        enemigo.vida = int(enemigo.vida * 0.75);
        enemigo.ataque1_danio = int(enemigo.ataque1_danio * 0.75);
        enemigo.ataque2_danio = int(enemigo.ataque2_danio * 0.75);
    }
    // Dificil: mas vida y danio para la maquina
    else if (dificultad == 3) {
        enemigo.vida = int(enemigo.vida * 1.25);
        enemigo.ataque1_danio = int(enemigo.ataque1_danio * 1.25);
        enemigo.ataque2_danio = int(enemigo.ataque2_danio * 1.25);
    }
    // Normal (2): sin cambios
}

int main() {
    srand(time(0));
    int dificultad;

    cout << "Elige dificultad:\n";
    cout << "1. Facil\n2. Normal\n3. Dificil\n";
    while (true) {
        cout << "Opcion: ";
        cin >> dificultad;
        if (dificultad >= 1 && dificultad <= 3) break;
        cout << "Opcion invalida. Intenta de nuevo.\n";
    }

    cout << "\nSelecciona tu Pokemon:\n";
    mostrarPokemons();

    int eleccionJugador;
    while (true) {
        cout << "Elige un numero (1-4): ";
        cin >> eleccionJugador;
        if (eleccionJugador >= 1 && eleccionJugador <= 4) break;
        cout << "Opcion invalida. Intenta de nuevo.\n";
    }

    Pokemon jugador = elegirPokemon(eleccionJugador);

    int eleccionMaquina = rand() % 4 + 1;
    Pokemon maquina = elegirPokemon(eleccionMaquina);

    ajustarDificultad(maquina, dificultad);

    cout << "\nTu eliges a " << jugador.nombre << " con " << jugador.vida << " puntos de vida.\n";
    cout << "La maquina elige a " << maquina.nombre << " con " << maquina.vida << " puntos de vida.\n\n";

    int turno = 1; // 1: jugador, 2: maquina
    while (jugador.vida > 0 && maquina.vida > 0) {
        if (turno == 1) {
            cout << "Turno del jugador.\n";
            cout << "Elige ataque:\n1. Ataque 1 (" << jugador.ataque1_danio << " danio)\n";
            cout << "2. Ataque 2 (" << jugador.ataque2_danio << " danio)\n";

            int ataque;
            while (true) {
                cout << "Opcion: ";
                cin >> ataque;
                if (ataque == 1 || ataque == 2) break;
                cout << "Opcion invalida. Intenta de nuevo.\n";
            }

            int danio = (ataque == 1) ? jugador.ataque1_danio : jugador.ataque2_danio;
            maquina.vida -= danio;
            cout << jugador.nombre << " ataca y causa " << danio << " puntos de danio.\n";
            cout << maquina.nombre << " tiene " << (maquina.vida > 0 ? maquina.vida : 0) << " puntos de vida restantes.\n\n";

            turno = 2;
        } else {
            cout << "Turno de la maquina.\n";
            int ataqueMaquina = rand() % 2 + 1;
            int danio = (ataqueMaquina == 1) ? maquina.ataque1_danio : maquina.ataque2_danio;
            jugador.vida -= danio;
            cout << maquina.nombre << " ataca y causa " << danio << " puntos de danio.\n";
            cout << jugador.nombre << " tiene " << (jugador.vida > 0 ? jugador.vida : 0) << " puntos de vida restantes.\n\n";

            turno = 1;
        }
    }

    if (jugador.vida <= 0)
        cout << "¡Tu Pokémon ha sido derrotado! ¡Perdiste!\n";
    else
        cout << "¡Has ganado la batalla! ¡Felicidades!\n";

    return 0;
}