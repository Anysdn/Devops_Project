#ifndef FASTASEQUENCE_HPP
#define FASTASEQUENCE_HPP

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

/**
 * @brief Cette classe permet de lire et stocker une séquence depuis un fichier FASTA.
 * Elle extrait l'en-tête, la séquence et les commentaires éventuels.
 */
class FastaSequence {
private:
    std::string header;                             // Ligne d'en-tête commençant par > du fichier fasta d'entree
    std::string sequence;                           // Séquence biologique associée
    std::map<size_t, std::string> comments;         // Commentaires, indexés par le numéro de la ligne dans le fichier

public:
    // Constructeurs
    FastaSequence() = default; //cree un objet vide 

    /**
     * @brief Constructeur à partir d’un fichier FASTA (lecture automatique)
     * @param filepath Chemin vers le fichier FASTA
     */
    FastaSequence(const std::string& filepath);

    /**
     * @brief Constructeur (manuel) à partir de l'en-tête et de la séquence 
     */
    FastaSequence(const std::string& header, const std::string& sequence);

    // --- Méthodes principales ---

    /**
     * @brief Lecture du fichier FASTA (1 seule séquence)
     * @param filepath Chemin vers le fichier
     * @return true si lecture réussie, false sinon
     */
    bool readFromFile(const std::string& filepath);

    /**
     * @brief Lecture de plusieurs séquences FASTA dans un fichier
     * @param filepath Chemin du fichier FASTA
     * @return Vecteur d’objets FastaSequence
     */
    static std::vector<FastaSequence> fromFile(const std::string& filepath);

    // --- Accesseurs ---

    std::string getHeader() const;
    std::string getSequence() const;
    std::map<size_t, std::string> getComments() const;

    /**
     * @brief Affiche un résumé de la séquence (header, taille, nbr de commentaires)
     */
    void printSummary() const;
};

#endif // FASTASEQUENCE_HPP
