#include "funciones.h"
#include <iostream>
#include "colors.h"

using namespace std;

class Wordle {
    private:
        vector<string> words;
        vector<string> prev_words;
        string wordle_otd;
        vector<int> hist;

    public:

        Wordle(string file){
            words = cargar_listado(file);
        }

        void newWordle(){
            srand (time(NULL));
            prev_words = {};
            wordle_otd = words[rand() % words.size()];
            cout << wordle_otd << endl;
        }

        void playGame(){
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
            clear();
            cout << BOLD(FCYN(" - WORDLE - ")) << endl;
        }

        void displayVectorString(vector<string> v){
            for (string e: v){
                cout << e << endl;
            }
            cout << endl;
        }

        void clear(){
            printf("\033[2J");
            printf("\033[%d;%dH", 0, 0);
        }


        string color(string & in, vector<EstadoLetra> ref){
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

    //const string file = "listado.txt"; 
    Wordle w = Wordle("listado.txt");
    string again = "n";
    do{
        w.playGame();
        w.displayStats();
        cout << endl << "Again? (y/n): ";
        cin >> again;
    }while(again != "n");

    return 0;
}