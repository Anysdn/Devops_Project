EXEC = Devops
# compilateur
CXX = g++ 
CXXFLAGS = -Wall -Wextra -std=c++17

# Fichiers sources du projet
SRC = main.cpp \
      BioSequence.cpp \
      BitSequence.cpp \
      BioUtils.cpp \
      FastaSequence.cpp \
      FastqSequence.cpp \
      KmerSearch.cpp   

# transformation des fichiers cpp en .o (objets compilés)
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

# Règle pour créer l'exécutable à partir des fichiers objets
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f *.o $(EXEC)

# Recompiler à partir de zéro
re: clean all
