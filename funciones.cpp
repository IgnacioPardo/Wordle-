#include "funciones.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> cargar_listado(const string & nombre_archivo){
	/**
	 * Genera en un vector<string> a partir un listado de palabras separadas por linebreaks en un archivo dado
	 *
	 * @param nombre_archivo Nombre del archivo que contiene las palabras.
	 * @return vector<string> de las palabras del archivo nombre_archivo
	 */

    vector<string> listado;

    ifstream file(nombre_archivo);
    string str; 
    while (getline(file, str)) {
      listado.push_back(str);
    }

    return listado;
}

bool intento_valido(const string & intento, const string & palabra_secreta, const vector<string> &listado){
	/**
	 * Determina si el intento fue uno valido o no
	 *
	 * @param intento Palabra a checkear
	 * @param palabra_secreta Palabra del Wordle
	 * @param listado Lista de palabras validas
	 * @return true si la palabra del intento pertenece al listado y tiene la misma longitud que la palabra del Wordle
	 */

    return (intento.size() == palabra_secreta.size()) && (find(listado.begin(), listado.end(), intento) != listado.end());

}

vector<EstadoLetra> evaluar_intento(const string & intento, const string & palabra_secreta){
	/**
	 * Determina el estado de cada letra de la palabra ingresada contra la palabra del Wordle
	 *
	 * @param intento Palabra a checkear
	 * @param palabra_secreta Palabra del Wordle
	 * @return Un vector conteniendo el estado de cada letra de la palabra ingresada
	 */

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
	/**
	 * Convierte un vector de estados en un string para representar el estado general de la palabra ingresada
	 *
	 * @param respuesta Un vector conteniendo los estados de cada letra
	 * @return Un string conteniendo los estados de cada letra a partir de las siguientes representaciones
	 * 		'X': NoPresente, '+': LugarCorrecto, '-': LugarIncorrecto
	 */

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