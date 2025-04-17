#ifndef BIOSEQUENCE_HPP
#define BIOSEQUENCE_HPP

#include <string>
#include <array>
#include <map>
#include <set>
#include "BitSequence.hpp"    // Pour la représentation binaire des séquences
#include "BioUtils.hpp"       // Fonctions utilitaires (IUPAC, erreurs, etc.)

/**
 * @brief Classe principale qui gère les séquences biologiques (ADN, ARN, protéines)
 */
class BioSequence {
public:
    enum IUPACMode { basic = 0, most = 1, all = 2 };
    enum SeqType { UNKNOWN, DNA, RNA, PROTEIN, NUCLEIC };

    class Symbol { // represente un symbol IUPAC
    private:
        char _symbol;       // le symbol iupac lui mm 
        std::string _replacement;// les bases possibles 
        IUPACMode _min_mode;// le niveau IUPAC min requis pour l'accepter

    public:
        Symbol(char symbol, const std::string& replacement, IUPACMode mode);
        bool matches(char target, bool useReplacement = true) const; //verifie si ce symbole peut correspondre a un symbole donné 
        bool usableIn(IUPACMode mode) const;
        char get(IUPACMode mode) const;
        char value() const;// retourne la caract brut sans modif 
    };
/*explication: 
dans le mapping, on veux savoir si deux lettres sont compatibles.
Exemple : 'N' dans une séquence peut matcher 'A' 
dans une autre, car 'N' = ACGT.*/


private:
    BitSequence _bitseq;                   // attribut qui stock l'encodage binaire de la séquence
    std::array<bool, 5> _type_flags;       // Flags du type de séquence
    char _declared_type;                   // 'D', 'R', 'P', 'N', 'U'
    IUPACMode _iupac;                      // Niveau IUPAC utilisé

    // Dictionnaires d'IUPAC ( liste les symboles autorisés pour chaque ty pe de seq)
    static const std::map<char, Symbol> legalDNA;
    static const std::map<char, Symbol> legalRNA;
    static const std::map<char, Symbol> legalAA;
    static const std::set<char> allowedTypes;

    // Méthodes utilitaires internes
    static std::array<bool, 5> readDeclaredType(char type);
    static char readTypeArray(std::array<bool, 5> flags, bool safe = false);
    static std::array<bool, 5> getSymbolFlags(char symbol);
    static bool canBeDna(char type);
    static bool canBeRna(char type);
    static bool canBeAmino(char type);
    static bool canBeNucleic(char type);

    char parse(char symbol, errorMods mode);
    const Symbol& getSymbol(char symbol, char type) const;

public:
    // Constructeur principal
    BioSequence(const std::string& sequence, char type = 'U', IUPACMode iupac = all, errorMods mod = ignore);

    // Méthodes de manipulation
    void insertFront(const std::string& sequence, errorMods mod = ignore);
    void insertBack(const std::string& sequence, errorMods mod = ignore);
    void insert(const std::string& sequence, size_t pos, errorMods mod = ignore);
    void erase(size_t pos, size_t len);

    // Getters
    size_t size() const;
    char get(size_t index) const;
    char getType() const;
    IUPACMode getIupac() const;
    const BitSequence& getBitSequence() const;

    // Itérateur personnalisé pour parcourir la séquence ( comme les stl )
    class Iterator {
    private:
        const BioSequence& _seq;
        size_t _index;
    public:
        Iterator(const BioSequence& seq, size_t index);
        char operator*() const;
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin() const;
    Iterator end() const;

    // operateurs de comparaison
    bool operator<(const BioSequence& other) const;
    bool operator>(const BioSequence& other) const;
    bool operator<=(const BioSequence& other) const;
    bool operator>=(const BioSequence& other) const;

    // Vérifie si la séquence est vide
    operator bool() const;
};

#endif // BIOSEQUENCE_HPP


/** exemple d'affichage pour le bool matches
Symbol N('N', "ACGT", all);
N.matches('G') → true
N.matches('Z') → false
 */