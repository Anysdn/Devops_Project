# Nom de l'exécutable final
EXEC = Devops

# Compilateur
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Tous les fichiers sources .cpp
SRC = main.cpp \
      src/BitSequence.cpp \
      src/BioSequence.cpp \
      src/BioUtils.cpp \
      src/KmerSearch.cpp

# Transformation des .cpp en .o
OBJ = $(SRC:.cpp=.o)

# Cible principale
all: $(EXEC)

# Construction de l'exécutable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Nettoyage des fichiers objets + exécutable
clean:
	rm -f $(OBJ) $(EXEC)

# Recompiler entièrement
re: clean all
