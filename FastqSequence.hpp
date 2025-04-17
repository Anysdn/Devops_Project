#ifndef FASTQSEQUENCE_HPP
#define FASTQSEQUENCE_HPP

#include <string>
#include <vector>
#include <fstream>

/**
 * @brief Cette classe gère la lecture et l'analyse des fichiers FASTQ
 */
class FastqSequence {
private:
    std::string header;      // ligne 1
    std::string sequence;    // ligne 2
    std::string plus_line;   // ligne 3 (souvent juste un '+')
    std::string quality;     // ligne 4

public:
    FastqSequence() = default;
    FastqSequence(const std::string& filepath);
    FastqSequence(const std::string& header, const std::string& sequence, const std::string& quality);

    bool readFromFile(const std::string& filepath);
    static std::vector<FastqSequence> fromFile(const std::string& filepath);

    std::string getHeader() const;
    std::string getSequence() const;
    std::string getQuality() const;

    void print() const;
    void printSummary() const;
};

#endif
