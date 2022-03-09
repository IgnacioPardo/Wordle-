#include "funciones.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> cargar_listado(const string & nombre_archivo){
    // completar

    vector<string> listado;

    std::ifstream file(nombre_archivo);
    std::string str; 
    while (std::getline(file, str)) {
      listado.push_back(str);
    }

    return listado;
}

bool intento_valido(const string & intento, const string & palabra_secreta, const vector<string> &listado){
    // completar

    return (intento.size() == palabra_secreta.size()) && (find(listado.begin(), listado.end(), intento) != listado.end());

}

vector<EstadoLetra> evaluar_intento(const string & intento, const string & palabra_secreta){
    // completar

    vector<EstadoLetra> check;

    for (int i = 0; i < palabra_secreta.size(); i++){
        if (intento[i] == palabra_secreta[i]){
            check.push_back(EstadoLetra::LugarCorrecto);
        }
        else if (palabra_secreta.find(intento[i]) != string::npos){
            check.push_back(EstadoLetra::LugarIncorrecto);
        }
        else{
            check.push_back(EstadoLetra::NoPresente);
        }
    }

    return check;
}

string respuesta_en_string(const vector<EstadoLetra> & respuesta){
    // completar
    string out = "";
    for (EstadoLetra s: respuesta){
        switch (s){
            case EstadoLetra::LugarCorrecto:
                out += '+'; 
                break;
            case EstadoLetra::LugarIncorrecto:
                out += '-'; 
                break;
            case EstadoLetra::NoPresente:
                out += 'X'; 
                break;
        }
    }
    return out;
}