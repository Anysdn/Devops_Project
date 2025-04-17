#include <iostream>
#include <filesystem> // Permet de vérifier si un fichier existe
#include "FastaSequence.hpp"  // Pour lire les fichiers FASTA
#include "FastqSequence.hpp"  // Pour lire les fichiers FASTQ
#include "BioSequence.hpp"    // Pour analyser les séquences biologiques encodées

int main() {
    std::cout << "=== TEST GLOBAL DU PROJET ===\n\n";

    // === 1. Lecture des fichiers FASTA et FASTQ ===
    std::cout << "[1] Lecture des fichiers FASTA et FASTQ\n";

    // Définition des chemins vers les fichiers
    std::string fastaPath = "mon_fichier.fasta";
    std::string fastqPath = "mon_fichier.fastq";

    // Vérifie si les fichiers existent sur le disque
    if (!std::filesystem::exists(fastaPath) || !std::filesystem::exists(fastqPath)) {
        std::cerr << "Fichier(s) introuvable(s) ! Vérifie les chemins." << std::endl;
        return 1; // On quitte le programme si les fichiers sont manquants
    }

    // Chargement de toutes les séquences FASTA présentes dans le fichier
    auto fastaList = FastaSequence::fromFile(fastaPath);
    if (!fastaList.empty()) {
        std::cout << "- Nombre de séquences FASTA : " << fastaList.size() << "\n";

        // On récupère la première séquence pour l'analyse
        FastaSequence& fasta = fastaList[0];
        std::cout << "- FASTA Header    : " << fasta.getHeader() << "\n";
        std::cout << "- FASTA Séquence  : " << fasta.getSequence() << "\n\n";

        // === 2. Analyse avec BioSequence ===
        std::cout << "[2] Analyse avec BioSequence\n";
        try {
            // Création d’un objet BioSequence à partir de la séquence FASTA
            BioSequence dna_seq(fasta.getSequence(), 'D'); // 'D' pour ADN

            // Affichage du type détecté et de la séquence encodée
            std::cout << "- Type détecté : " << dna_seq.getType() << "\n";
            std::cout << "- Séquence encodée : ";
            for (size_t i = 0; i < dna_seq.size(); ++i) {
                std::cout << dna_seq.get(i);
            }
            std::cout << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Erreur dans BioSequence : " << e.what() << "\n";
        }
    }

    // === 3. Lecture et affichage du fichier FASTQ ===
    std::cout << "\n=== Test de FastqSequence ===\n";
    FastqSequence fastq(fastqPath);
    fastq.printSummary();  // Résumé (entête, taille, qualité)
    std::cout << "- Séquence FASTQ complète :\n";
    fastq.print();         // Affiche tout le contenu du fichier FASTQ

    std::cout << "\n=== Fin des tests ===\n";
    return 0;
}


// pour la compilation: 
//g++ -o mon_programme main.cpp BioSequence.cpp BitSequence.cpp BioUtils.cpp FastqSequence.cpp FastaSequence.cpp

