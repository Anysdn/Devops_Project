#include "BioUtils.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * @brief Gère les erreurs d'argument invalide.
 * Selon le mode choisi (ignore, display ou raise), l'erreur est soit ignorée,
 * affichée sur la console, soit levée sous forme d'exception std::invalid_argument.
 *
 * @param mod Mode de gestion de l'erreur
 * @param msg Message d'erreur personnalisé
 * @param file Nom du fichier (pour l'affichage, optionnel)
 * @param func Nom de la fonction (pour l'affichage, optionnel)
 */
void displayInvalidArgument(errorMods mod, const string& msg, const string& file, const string& func) {
    string full_msg = "[InvalidArgument] " + msg + " (" + file + "::" + func + ")";
    switch (mod) {
        case ignore: break; // Ne fait rien
        case display: cerr << full_msg << endl; break; // Affiche le message dans la console d'erreur
        case raise: throw invalid_argument(full_msg); // Lève une exception avec le message complet
    }
}

/**
 * @brief Gère les erreurs liées à la longueur (ex. dépassement d'un buffer, taille invalide).
 *
 * @param mod Mode d'affichage ou de gestion de l'erreur
 * @param msg Message à afficher/lancer
 * @param file Fichier dans lequel l'erreur s'est produite
 * @param func Fonction concernée
 */
void displayLengthError(errorMods mod, const string& msg, const string& file, const string& func) {
    string full_msg = "[LengthError] " + msg + " (" + file + "::" + func + ")";
    switch (mod) {
        case ignore: break;
        case display: cerr << full_msg << endl; break;
        case raise: throw length_error(full_msg);
    }
}

/**
 * @brief Gère les erreurs de domaine (valeurs hors des limites acceptables).
 * Utilisée lorsqu'une valeur est "légale" en C++, mais ne correspond pas aux règles
 * définies dans le contexte du projet (par exemple, un caractère invalide dans une séquence).
 *
 * @param mod Niveau d'erreur souhaité
 * @param msg Message à afficher
 * @param file Nom du fichier
 * @param func Nom de la fonction
 */
void displayDomainError(errorMods mod, const string& msg, const string& file, const string& func) {
    string full_msg = "[DomainError] " + msg + " (" + file + "::" + func + ")";
    switch (mod) {
        case ignore: break;
        case display: cerr << full_msg << endl; break;
        case raise: throw domain_error(full_msg);
    }
}
