#ifndef BITSEQUENCE_HPP
#define BITSEQUENCE_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdarg>
#include "BioUtils.hpp"

/**
 * @brief Classe permettant de manipuler efficacement des données encodées bit à bit dans un tableau de char.
 */
class BitSequence {
private:
    char* _data = nullptr;               ///< Tableau de bits sous forme de char*
    size_t _data_size = 0;               ///< Taille en octets
    size_t _element_number = 0;          ///< Nombre d'éléments stockés
    unsigned short int _element_size = 0;///< Taille d'un élément en bits

    void _killInternalData();// permet de nettoyer et de liberer data correctement

public:
    /**
     * @brief Classe itérateur pour parcourir les éléments du BitSequence.
     */
    class Iterator {
    private:
        const BitSequence& _parent;
        size_t _index; // index de l'élément courant

    public:
        Iterator(const BitSequence& parent, size_t index);
        char* operator*() const;                     // Extraction de l’élément courant
        Iterator& operator++();                      // Pré-incrément
        bool operator!=(const Iterator& other) const;
        size_t getIndex() const;
    };

    // Constructeurs et destructeurs
    BitSequence(unsigned short int block_size, size_t alloc);
    BitSequence(unsigned short int block_size) : BitSequence(block_size, 2) {}
    BitSequence(const BitSequence& other);
    ~BitSequence();// destructeur 

    // Getters
    size_t getDataSize() const; // taille memoire reelle en octet 
    size_t getElementNumber() const;// nbr d'element stockes 
    size_t size() const;
    unsigned short int getElementSize() const;// nbr de bits par élément
    size_t currentElementCapacity() const;// combien on peut stocker sans réallouer 

    // Itérateurs ( permet de parcourir les elements bit a bit )
    Iterator begin() const;
    Iterator end() const;

    // Modifications
    void setElementNumber(size_t number); // fixe le nbr d'elements 
    void doubleSize();// redimensionne le tableau interne 
    void resize(size_t element_capacity);
    void shrink();// reduit la memoire a 'essentiel
    void clear();//vide le bitsequence

    //Opérations sur les donnees 
    char* get(size_t index) const; // lecture ( renvoie un pointeur vers les bits correspondant a un element donné )
    char* operator[](size_t index) const;
    //ecriture de l'element a l'index donné 
    void set(size_t index, char* tab, bool restrictions = true, bool push = true);
    void set(size_t index, char value, bool restrictions = true, bool push = true);
    void append(char* tab); // ajout de nouveaux element a la fin 
    void append(char value);
    void makeRoomForElement(size_t element_position, size_t room_required, bool erase = true);
    //insertion de plsr elemnt a une position donnee 
    void insert(size_t pos, size_t number_of_elements, char* tab...);
    void insert(size_t pos, size_t number_of_elements, char c...);
    void remove(size_t element_position, size_t number_of_element);

    operator bool() const;
};

#endif // BITSEQUENCE_HPP
