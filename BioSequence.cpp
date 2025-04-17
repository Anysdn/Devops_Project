#include "BioSequence.hpp"
#include "BitSequence.hpp"
#include "BioUtils.hpp"
#include <string>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <array>

using namespace std;

// Initialisation des tables d'encodage IUPAC (pour ADN, ARN, AA)
const std::map<char, BioSequence::Symbol> BioSequence::legalDNA = BioUtils::buildLegalDNAMap();
const std::map<char, BioSequence::Symbol> BioSequence::legalRNA = BioUtils::buildLegalRNAMap();
const std::map<char, BioSequence::Symbol> BioSequence::legalAA  = BioUtils::buildLegalAAMap();
const std::set<char> BioSequence::allowedTypes = {'P', 'D', 'R', 'N', 'U'};

// Constructeur principal
BioSequence::BioSequence(const std::string& raw_seq, char type, IUPACMode iupac_mode, errorMods mode_err)
    : _bitseq(BitSequence(BioSequence::maxSymbolSize(type, iupac_mode), raw_seq.size())),
      _declared_type(std::toupper(type)), _iupac(iupac_mode)
{
    if (_declared_type == 'U' && iupac_mode < most) {
        throw std::invalid_argument("Type 'U' nécessite un mode IUPAC >= most.");
    }

    _type_flags = BioUtils::parseTypeChar(_declared_type);
    insertBack(raw_seq, mode_err);
    _type_flags[4] = false; // désactiver la recherche de type
}

// Getters
char BioSequence::getType() const {
    return BioUtils::typeArrayToChar(_type_flags, true);
}

BioSequence::IUPACMode BioSequence::getIupac() const {
    return _iupac;
}

size_t BioSequence::size() const {
    return _bitseq.size();
}

const BitSequence& BioSequence::getBitSequence() const {
    return _bitseq;
}

// Insertion de séquences
void BioSequence::insertFront(const std::string& seq, errorMods mod) {
    insert(seq, size(), mod);
}

void BioSequence::insertBack(const std::string& seq, errorMods mod) {
    insert(seq, 0, mod);
}

void BioSequence::insert(const std::string& seq, size_t pos, errorMods mod) {
    _bitseq.makeRoom(pos, seq.size());
    const auto& trans = BioUtils::getTranslationTable(_declared_type, _iupac);

    size_t original_pos = pos;
    try {
        for (char c : seq) {
            char parsed = parse(c, mod);
            if (parsed != '\0') {
                _bitseq.set(pos++, trans.at(parsed));
            }
        }
    } catch (...) {
        _bitseq.remove(pos, seq.size() - (pos - original_pos));
        throw;
    }

    if (pos - original_pos != seq.size()) {
        _bitseq.remove(pos, seq.size() - (pos - original_pos));
    }
}

// Suppression d'une portion de séquence
void BioSequence::erase(size_t pos, size_t len) {
    if (pos >= size()) return;
    _bitseq.remove(pos, len);
}

// Accès à un caractère
char BioSequence::get(size_t index) const {
    char* raw = _bitseq.get(index);
    char val = BioUtils::getReverseTranslation(_declared_type, _iupac).at(raw[0]);
    delete[] raw;
    return val;
}

// Parsing d'un caractère
char BioSequence::parse(char symbol, errorMods mode) {
    symbol = std::toupper(symbol);
    auto flags = BioUtils::identifyCharType(symbol);

    if (!flags[4]) {
        BioUtils::raiseDomainError(mode, "Caractère non autorisé : " + std::string(1, symbol));
        return '\0';
    }

    if (_type_flags[4]) {
        // Mode détection automatique
        for (size_t i = 0; i < 4; ++i) _type_flags[i] |= flags[i];
        return BioUtils::getSymbol(symbol, BioUtils::typeArrayToChar(_type_flags)).get(_iupac);
    } else {
        char type = BioUtils::typeArrayToChar(_type_flags);
        if ((type == 'D' && !BioUtils::canBeDna(symbol, type)) ||
            (type == 'R' && !BioUtils::canBeRna(symbol, type)) ||
            (type == 'P' && !BioUtils::canBeAmino(symbol, type))) {
            BioUtils::raiseDomainError(mode, "Caractère '" + std::string(1, symbol) + "' incompatible avec le type.");
            return '\0';
        }
        return BioUtils::getSymbol(symbol, type).get(_iupac);
    }
}

// Calcul de la taille max selon l'encodage
size_t BioSequence::maxSymbolSize(char encoding_type, IUPACMode iupac) {
    return BioUtils::getTranslationTable(encoding_type, iupac).size();
}

// --- Itérateurs personnalisés ---
BioSequence::Iterator::Iterator(const BioSequence& seq, size_t index) : _seq(seq), _index(index) {}

char BioSequence::Iterator::operator*() const {
    return _seq.get(_index);
}

BioSequence::Iterator& BioSequence::Iterator::operator++() {
    ++_index;
    return *this;
}

bool BioSequence::Iterator::operator!=(const Iterator& other) const {
    return _index != other._index;
}

BioSequence::Iterator BioSequence::begin() const {
    return Iterator(*this, 0);
}

BioSequence::Iterator BioSequence::end() const {
    return Iterator(*this, size());
}

// --- Opérateurs de comparaison ---
bool BioSequence::operator<(const BioSequence& other) const {
    return size() < other.size();
}

bool BioSequence::operator>(const BioSequence& other) const {
    return size() > other.size();
}

bool BioSequence::operator<=(const BioSequence& other) const {
    return size() <= other.size();
}

bool BioSequence::operator>=(const BioSequence& other) const {
    return size() >= other.size();
}

BioSequence::operator bool() const {
    return !_type_flags[4]; // true si le type est fixé
}
