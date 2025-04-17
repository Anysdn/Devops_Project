
#ifndef KMERSEARCH_HPP
#define KMERSEARCH_HPP

#include <vector>
#include <string>
#include "BitSequence.hpp"

// Structure pour représenter une position d'occurrence
struct KmerHit {
    size_t position;            // position dans le génome
    bool reverse_complement;    // il me renvoie true si trouvé sur le brin complémentaire

    KmerHit(size_t pos, bool is_rc) : position(pos), reverse_complement(is_rc) {}
};

// Déclaration des fonctions
std::vector<KmerHit> findOccurrences(const BitSequence& genome, const std::string& kmer);
std::string reverseComplement(const std::string& kmer);

#endif


/*
ce que je dois ajouter :
-   La fonction qui retourne le kmer à la position i
-   une classe SuffixArray pour integrer la recherche dichotomique, puis prevoir une une recherche binaire(log(n)) 
sur ce tableau de suff, pour integrer la recherche de motifs dans un grand genome (n>10^9)
*/