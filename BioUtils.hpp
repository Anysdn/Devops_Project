#ifndef BIOUTILS_HPP
#define BIOUTILS_HPP

#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

/**
 * @brief Enumération définissant le comportement à adopter en cas d'erreur :
 * - ignore : ne rien faire
 * - display : afficher un message d’erreur
 * - raise : lancer une exception 
 */
enum errorMods { ignore, display, raise };

/**
 * @brief Gère les erreurs de type "invalid_argument".
 * Affiche un message d'erreur personnalisé ou lève une exception selon le mode choisi.
 *
 * @param mode Le comportement d'erreur (ignore, display, raise)
 * @param message Le message à afficher ou à inclure dans l'exception
 * @param file Optionnel : nom du fichier source
 * @param func Optionnel : nom de la fonction
 */
inline void displayInvalidArgument(errorMods mode, const std::string& message,
                                   const std::string& file = "", const std::string& func = "") {
    if (mode == ignore) return;
    std::cerr << "[InvalidArgument] " << message;
    if (!file.empty()) std::cerr << " | File: " << file;
    if (!func.empty()) std::cerr << " | Function: " << func;
    std::cerr << std::endl;
    if (mode == raise) throw std::invalid_argument(message);
}

/**
 * @brief Gère les erreurs de type "length_error".
 * Utile si une opération dépasse une taille attendue.
 *
 * @param mode Le comportement à adopter
 * @param message Le message à afficher ou à lancer
 * @param file Nom du fichier (optionnel)
 * @param func Nom de la fonction (optionnel)
 */
inline void displayLengthError(errorMods mode, const std::string& message,
                               const std::string& file = "", const std::string& func = "") {
    if (mode == ignore) return;
    std::cerr << "[LengthError] " << message;
    if (!file.empty()) std::cerr << " | File: " << file;
    if (!func.empty()) std::cerr << " | Function: " << func;
    std::cerr << std::endl;
    if (mode == raise) throw std::length_error(message);
}

/**
 * @brief Gère les erreurs de type "domain_error".
 * Sert quand une valeur ne respecte pas les contraintes du domaine.
 *
 * @param mode Type de réaction à l'erreur
 * @param message Message associé à l'erreur
 * @param file Nom du fichier source (optionnel)
 * @param func Nom de la fonction en cours (optionnel)
 */
inline void displayDomainError(errorMods mode, const std::string& message,
                               const std::string& file = "", const std::string& func = "") {
    if (mode == ignore) return;
    std::cerr << "[DomainError] " << message;
    if (!file.empty()) std::cerr << " | File: " << file;
    if (!func.empty()) std::cerr << " | Function: " << func;
    std::cerr << std::endl;
    if (mode == raise) throw std::domain_error(message);
}

#endif // BIOUTILS_HPP
