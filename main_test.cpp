#include <iostream>
#include "FastaSequence.hpp"
#include "FastqSequence.hpp"

int main() {
    std::string fastaPath = "mon_fichier.fasta";
    std::string fastqPath = "mon_fichier.fastq";

    std::cout << "=== Test FastaSequence ===\n";
    FastaSequence fasta(fastaPath);
    fasta.printSummary(); // Affiche le header et la longueur de la séquence

    std::cout << "\n=== Test FastqSequence ===\n";
    FastqSequence fastq(fastqPath);
    fastq.printSummary(); // Affiche le header, la longueur, et la qualité

    return 0;
}
