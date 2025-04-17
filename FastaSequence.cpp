#include "FastaSequence.hpp"
#include <sstream>  // utile si besoin de traitement de texte plus poussé

/**
 * @brief Constructeur depuis un fichier FASTA : appelle automatiquement la fonction readFromFile().
 */
FastaSequence::FastaSequence(const std::string& filepath) {
    readFromFile(filepath);
}

/**
 * @brief Lecture d’un fichier FASTA ligne par ligne (version simple, une seule séquence)
 */
bool FastaSequence::readFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return false;

    std::string line;
    size_t line_number = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '>') {
            header = line.substr(1); // Enlève le caractère '>'
        } else if (line[0] == ';') {
            comments[line_number] = line; // Enregistre les commentaires
        } else {
            sequence += line; // Concatène les lignes de séquence
        }
        line_number++;
    }

    return true;
}

/**
 * @brief Accesseur : retourne l’en-tête de la séquence
 */
std::string FastaSequence::getHeader() const {
    return header;
}

/**
 * @brief Accesseur : retourne la séquence lue
 */
std::string FastaSequence::getSequence() const {
    return sequence;
}

/**
 * @brief Accesseur : retourne la map des commentaires
 */
std::map<size_t, std::string> FastaSequence::getComments() const {
    return comments;
}

/**
 * @brief Affiche un résumé rapide de la séquence
 */
void FastaSequence::printSummary() const {
    std::cout << "Header: " << header << "\n"
              << "Length: " << sequence.size() << "\n"
              << "Comments: " << comments.size() << std::endl;
}

/**
 * @brief Constructeur manuel depuis header + séquence
 */
FastaSequence::FastaSequence(const std::string& header, const std::string& sequence)
    : header(header), sequence(sequence) {}

/**
 * @brief Lecture de plusieurs séquences FASTA depuis un fichier
 *        Chaque séquence commence par un '>' suivi de lignes de séquence
 */
std::vector<FastaSequence> FastaSequence::fromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    std::vector<FastaSequence> sequences;

    if (!file.is_open()) return sequences;

    std::string line, current_header, current_sequence;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '>') {
            // Si on trouve un nouvel header, on stocke la séquence précédente
            if (!current_header.empty()) {
                sequences.emplace_back(current_header, current_sequence);
                current_sequence.clear();
            }
            current_header = line.substr(1); // enlève le '>'
        } else {
            current_sequence += line; // concatène la séquence sur plusieurs lignes
        }
    }

    // Enregistrement de la dernière séquence
    if (!current_header.empty() && !current_sequence.empty()) {
        sequences.emplace_back(current_header, current_sequence);
    }

    return sequences;
}
