#include "funciones.h"
#include <iostream>
#include "colors.h"

using namespace std;

/**
 * Implementacion de un Wordle
 *
 * Dada una lista de palabras permitidas, genera un juego de Wordle capaz de
 * randomizar una palabra a adivinar, generar multiples partidas y registrar
 * un historial de estadisticas a traves de multiples partidas. Incluye los metodos 
 * para mostrar el Wordle por consola, asi como para resaltar las letras correctas/incorrectas/mal ubicadas.
 * 
 */

class Wordle {
    private:
        vector<string> words; //Palabras permitidas
        vector<string> prev_words; //Palabras ya ingresadas por el usuario en una partida
        string wordle_otd; //Wordle of the Day: Palabra elegida al azar para la partida de Wordle
        vector<int> hist; //Historial de intentos hasta acertar.

    public:

        Wordle(string file){
			/**
			 * Crea un nuevo Wordle a partir de un listado de palabras permitidas
			 *
			 */

            words = cargar_listado(file);
        }

        void newWordle(){
			/**
			 * Crea una nueva partida de Wordle randomizando la palabra seleccionada
			 *
			 */

            srand (time(NULL));
            prev_words = {};
            wordle_otd = words[rand() % words.size()];
            
            //Easter Egg para ver la palabra del WORDLE en debugging.
            //cout << wordle_otd << endl;
        }

        void playGame(){
			/**
			 * Inicializa un nuevo Wordle, y comienza una partida en modo interactivo por consola
			 *
			 */

            newWordle();
            int tries = 0;
            string in;  

            for (int i = 0; i<6; i++){
                do{
                    renderGame();
                    displayVectorString(prev_words);
                    cin >> in;
                    tries = i;
                }
                while((!intento_valido(in, wordle_otd, words)) && (in != wordle_otd));
                renderGame();
                prev_words.push_back(color(in, evaluar_intento(in, wordle_otd)));
                if (in == wordle_otd)
                    break;
            }
            hist.push_back(tries);
            displayVectorString(prev_words);

            cout << wordle_otd << endl;
        }

        void renderGame(){
			/**
			 * Limpia la consola y muestra el header " - WORDLE - "
			 *
			 */

            clear();
            cout << BOLD(FCYN(" - WORDLE - ")) << endl;
        }

        void displayVectorString(vector<string> v){
			/**
			 * Muestra por consola linea por linea los elementos de un vector de strings
			 *
			 *@param v Un vector de strings a printear linea por linea
			 */

            for (string e: v){
                cout << e << endl;
            }
            cout << endl;
        }

        void clear(){
			/**
			 * Limpia la consola
			 *
			 */

            printf("\033[2J");
            printf("\033[%d;%dH", 0, 0);
        }


        string color(string & in, vector<EstadoLetra> ref){
			/**
			 * Retorna un string colorizado a partir de un string y un vector de estados por letra del string in.
			 *
			 * @param in El string a colorear
			 * @param ref Un vector de estados por cada letra de in
			 * @return Un string colorizado a partir de un string y un vector de estados por letra del string in.
			 */

            string out = "";
            for (int i = 0; i < in.size(); i++){
                switch (ref[i]){
                    case EstadoLetra::LugarCorrecto:
                        out += KGRN + in.substr(i, 1) + RST;
                        break;
                    case EstadoLetra::LugarIncorrecto:
                        out += KYEL + in.substr(i, 1) + RST; 
                        break;
                    case EstadoLetra::NoPresente:
                        out += in[i];
                        break;
                }
            }
            return out;
        }

        void displayStats(){
            /**
             * Calcula y muestra por pantalla las estadisticas 
             * a partir de los datos recolectados en cada partida
             * al igual que el WORDLE original.
             * 
             * Cantidad de partidas jugadas
             * Porcentaje de acertados en cada intento
             **/

            vector<int> stats = {0,0,0,0,0,0};
            int count = hist.size();
            cout << "Jugadas: " << count << endl;
            for (int _try: hist){
                stats[_try]++;
            }

            for(int i = 0; i < 6; i++){
                int _try = stats[i];
                int barWidth = 20;
                float p = float(float(_try)/float(count));
                cout << i << ": ";
                for (int i = 0; i < barWidth * p; ++i) {
                    cout << "⬜️";
                }
                cout << "  (" << 100 * p << "%)" << endl;
            }
        }
};

int main(){
    /**
     * Interaccion con la implementacion de WORDLE
     * 
     * Genera una instancia de Wordle a partir de un listado dado
     * Crea una partida inicial para jugar
     * Al finalizar muestra las estadisticas de la instancia de Wordle
     * Posibilidad de jugar multiples partidas para acumular datos de partidas.
     * 
     */


    const string file_path = "listado.txt"; 
    Wordle w = Wordle(file_path);
    string again = "n";
    do{
        w.playGame();
        w.displayStats();
        cout << endl << "Again? (y/n): ";
        cin >> again;
    }while(again != "n");

    return 0;
}