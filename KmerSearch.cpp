
#include "KmerSearch.hpp"
#include <stdexcept>
#include <iostream>

// Petite fonction pour encoder une base en 2 bits
// A = 00, C = 01, G = 10, T = 11
char encode_base(char base) {
    switch (base) {
        case 'A': return 0b00;
        case 'C': return 0b01;
        case 'G': return 0b10;
        case 'T': return 0b11;
        default:
            throw std::invalid_argument("Base non reconnue : " + std::string(1, base));
    }
}

// Fonction qui donne le complément d'une base 
char complement(char base) {
    switch (base) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'C': return 'G';
        case 'G': return 'C';
        default:
            throw std::invalid_argument("Base non reconnue : " + std::string(1, base));
    }
}

// Fonction pour générer le reverse complement d'un k-mer
std::string reverseComplement(const std::string& kmer) {
    std::string rc;
    for (int i = static_cast<int>(kmer.size()) - 1; i >= 0; --i) {
        rc += complement(kmer[i]);
    }
    return rc;
}

// Encode un k-mer en vecteur de bits (char ici, 2 bits par base)
std::vector<char> encodeKmer(const std::string& kmer) {
    std::vector<char> encoded;
    for (char base : kmer) {
        encoded.push_back(encode_base(base));
    }
    return encoded;
}

// Fonction principale pour chercher les occurrences d'un k-mer dans le génome encodé
std::vector<KmerHit> findOccurrences(const BitSequence& genome, const std::string& kmer) {
    std::vector<KmerHit> results;

    // On encode le k-mer en binaire
    std::vector<char> encoded_kmer = encodeKmer(kmer);
    std::vector<char> encoded_rc = encodeKmer(reverseComplement(kmer));

    size_t genome_len = genome.getElementNumber(); // nombre total de bases
    size_t k = encoded_kmer.size(); // longueur du k-mer

    // On parcourt chaque position possible dans le génome
    for (size_t i = 0; i <= genome_len - k; ++i) {
        bool match_forward = true;
        bool match_reverse = true;

        // Comparaison base par base
        for (size_t j = 0; j < k; ++j) {
            char genome_base = genome[i + j][0]; // base extraite
            if (genome_base != encoded_kmer[j]) {
                match_forward = false;
            }
            if (genome_base != encoded_rc[j]) {
                match_reverse = false;
            }
        }

        if (match_forward) {
            results.emplace_back(i, false); // trouvé en sens direct
        }
        if (match_reverse) {
            results.emplace_back(i, true);  // trouvé en reverse complement
        }
    }

    return results;
}
