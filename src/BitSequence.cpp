#include "BitSequence.hpp"
#include "BioUtils.hpp"
#include <string>
#include <cstring>
#include <cstdarg>
#include <stdexcept>
#include <sstream>

// --- Implémentation de BitSequence::Iterator ---

BitSequence::Iterator::Iterator(const BitSequence& parent, size_t index)
    : _parent(parent), _index(index) {}

char* BitSequence::Iterator::operator*() const {
    return _parent.get(_index); // Utilise la méthode get(index)
}

BitSequence::Iterator& BitSequence::Iterator::operator++() {
    _index++;
    return *this;
}

bool BitSequence::Iterator::operator!=(const BitSequence::Iterator& other) const {
    return _index != other._index;
}

size_t BitSequence::Iterator::getIndex() const {
    return _index;
}

BitSequence::Iterator BitSequence::begin() const {
    return Iterator(*this, 0);
}

BitSequence::Iterator BitSequence::end() const {
    return Iterator(*this, this->size()); // size() = nombre d’éléments
}
