#include "FastqSequence.hpp"
#include <iostream> // pour les affichages dans le terminal avec std::cout

// === Constructeur principal ===
// Ce constructeur permet d’instancier un objet FastqSequence
// directement à partir d’un chemin de fichier FASTQ.
FastqSequence::FastqSequence(const std::string& filepath) {
    readFromFile(filepath); // on appelle une méthode pour lire le fichier
}

// === Constructeur alternatif ===
// Permet de construire une séquence FASTQ manuellement
FastqSequence::FastqSequence(const std::string& header, const std::string& sequence, const std::string& quality)
    : header(header), sequence(sequence), plus_line("+"), quality(quality) {}
    // la ligne '+' est fixe dans FASTQ, on l’attribue directement ici

// === Méthode de lecture ===
// Cette fonction lit une séquence FASTQ à partir d’un fichier donné
bool FastqSequence::readFromFile(const std::string& filepath) {
    std::ifstream file(filepath); // ouverture du fichier
    if (!file.is_open()) return false; // vérifie que le fichier s’ouvre bien

    std::getline(file, header);   // ligne 1 : en-tête
    std::getline(file, sequence); // ligne 2 : séquence nucléotidique
    std::getline(file, plus_line);  // ligne 3 : séparateur +
    std::getline(file, quality);  // ligne 4 : séquence de qualité

    if (header[0] == '@') header = header.substr(1); // on enlève le caractère '@'
    return true;
}

// === Lecture de plusieurs séquences FASTQ ===
// Cette méthode permet de lire plusieurs séquences dans un même fichier
std::vector<FastqSequence> FastqSequence::fromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    std::vector<FastqSequence> sequences; // vecteur qui va contenir les séquences lues

    if (!file.is_open()) return sequences;

    std::string header, sequence, plus, quality;
    while (std::getline(file, header)) {
        if (header.empty() || header[0] != '@') continue;

        std::getline(file, sequence); // ligne 2
        std::getline(file, plus);     // ligne 3
        std::getline(file, quality);  // ligne 4

        // on ajoute une nouvelle séquence au vecteur
        sequences.emplace_back(header.substr(1), sequence, quality);
    }

    return sequences;
}

// === Accesseurs ===
std::string FastqSequence::getHeader() const {
    return header;
}

std::string FastqSequence::getSequence() const {
    return sequence;
}

std::string FastqSequence::getQuality() const {
    return quality;
}

// === Méthode d’affichage complète ===
// Affiche les 4 lignes formatées comme dans un vrai fichier FASTQ
void FastqSequence::print() const {
    std::cout << "@" << header << "\n"
              << sequence << "\n"
              << plus_line << "\n"
              << quality << std::endl;
}

// === Résumé de la séquence ===
// Affiche juste un résumé rapide : en-tête, taille de la séquence, taille de la qualité
void FastqSequence::printSummary() const {
    std::cout << "Header: " << header << "\n"
              << "Length: " << sequence.size() << "\n"
              << "Quality: " << quality.size() << std::endl;
}
