#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Pokemon {
    string nombre;
    int vida;
    int ataque1_danio;
    int ataque2_danio;
    string ataque1_nombre;
    string ataque2_nombre;
};

void mostrarPokemons() {
    cout << "1. Pikachu\n";
    cout << "2. Charmander\n";
    cout << "3. Bulbasaur\n";
    cout << "4. Squirtle\n";
}

Pokemon elegirPokemon(int eleccion) {
    switch(eleccion) {
        case 1: return {"Pikachu", 100, 20, 25, "Impactrueno", "Rayo"};
        case 2: return {"Charmander", 110, 22, 20, "Ascuas", "Lanzallamas"};
        case 3: return {"Bulbasaur", 120, 18, 23, "Placaje", "Latigazo Cepa"};
        case 4: return {"Squirtle", 130, 15, 18, "Pistola Agua", "Burbuja"};
        default: return {"Pikachu", 100, 20, 25, "Impactrueno", "Rayo"};
    }
}

void ajustarDificultad(Pokemon &enemigo, int dificultad) {
    if (dificultad == 1) {
        enemigo.vida = int(enemigo.vida * 0.75);
        enemigo.ataque1_danio = int(enemigo.ataque1_danio * 0.75);
        enemigo.ataque2_danio = int(enemigo.ataque2_danio * 0.75);
    } else if (dificultad == 3) {
        enemigo.vida = int(enemigo.vida * 1.25);
        enemigo.ataque1_danio = int(enemigo.ataque1_danio * 1.25);
        enemigo.ataque2_danio = int(enemigo.ataque2_danio * 1.25);
    }
}

void pausa() {
    cout << "Presiona Enter para continuar...";
    cin.ignore();
    cin.get();
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
    cin.ignore();

    cout << "\nSelecciona tu Pokemon:\n";
    mostrarPokemons();

    int eleccionJugador;
    while (true) {
        cout << "Elige un numero (1-4): ";
        cin >> eleccionJugador;
        if (eleccionJugador >= 1 && eleccionJugador <= 4) break;
        cout << "Opcion invalida. Intenta de nuevo.\n";
    }
    cin.ignore();

    Pokemon jugador = elegirPokemon(eleccionJugador);
    int eleccionMaquina = rand() % 4 + 1;
    Pokemon maquina = elegirPokemon(eleccionMaquina);
    ajustarDificultad(maquina, dificultad);

    cout << "\nTu eliges a " << jugador.nombre << " con " << jugador.vida << " puntos de vida.\n";
    cout << "La maquina elige a " << maquina.nombre << " con " << maquina.vida << " puntos de vida.\n\n";

    int turno = 1;
    while (jugador.vida > 0 && maquina.vida > 0) {
        if (turno == 1) {
            cout << "----------------------------------------------\n";
            cout << "Turno del jugador.  \"Mijita, con ese poder me desmayo yo solito\"\n";
            cout << "Elige ataque:\n";
            cout << "1. " << jugador.ataque1_nombre << " (" << jugador.ataque1_danio << " daño)\n";
            cout << "2. " << jugador.ataque2_nombre << " (" << jugador.ataque2_danio << " daño)\n";

            int ataque;
            while (true) {
                cout << "Opcion: ";
                cin >> ataque;
                if (ataque == 1 || ataque == 2) break;
                cout << "Opcion invalida. Intenta de nuevo.\n";
            }
            cin.ignore();

            int danio = (ataque == 1) ? jugador.ataque1_danio : jugador.ataque2_danio;
            string nombreAtaque = (ataque == 1) ? jugador.ataque1_nombre : jugador.ataque2_nombre;

            maquina.vida -= danio;
            cout << jugador.nombre << " usa " << nombreAtaque << " y causa " << danio << " puntos de daño.\n";
            cout << maquina.nombre << " tiene " << (maquina.vida > 0 ? maquina.vida : 0) << " puntos de vida restantes.\n\n";

            turno = 2;
            pausa();
        } else {
            cout << "----------------------------------------------\n";
            cout << "Turno de la maquina.  \"Ay papá, si así me pega, que me pegue dos veces\"\n";

            int ataqueMaquina = rand() % 2 + 1;
            int danio = (ataqueMaquina == 1) ? maquina.ataque1_danio : maquina.ataque2_danio;
            string nombreAtaque = (ataqueMaquina == 1) ? maquina.ataque1_nombre : maquina.ataque2_nombre;

            jugador.vida -= danio;
            cout << maquina.nombre << " usa " << nombreAtaque << " y causa " << danio << " puntos de daño.\n";
            cout << jugador.nombre << " tiene " << (jugador.vida > 0 ? jugador.vida : 0) << " puntos de vida restantes.\n\n";

            turno = 1;
            pausa();
        }
    }

    cout << "----------------------------------------------\n";
    if (jugador.vida <= 0)
        cout << "¡Tu Pokémon ha sido derrotado! ¡Perdiste!\n";
    else
        cout << "¡Has ganado la batalla! ¡Felicidades!\n";

    return 0;
}

