## PROJET_DevOps

Ce projet a été réalisé dans le cadre du module de développement opérationnel avancé (Master Bioinformatique 2024/2025).
Il permet de manipuler des séquences d'ADN, ARN ou protéines à partir de fichiers de séquençage (FASTA ou FASTQ), avec un encodage binaire pour optimiser la mémoire et les performances.

## Contenu du projet
- FastaSequence : lecture de fichiers FASTA et récupération des séquences.
- FastqSequence : lecture des fichiers FASTQ (séquences + scores de qualité).
- BioSequence : représente une séquence encodée, avec prise en charge des symboles IUPAC.
- BitSequence : stockage des bases encodées bit à bit (ex : 2 bits/base pour l'ADN).
- BioUtils : fonctions utilitaires (gestion des erreurs, validation, etc.).
- KmerSearch : recherche de k-mers exacts et de leur reverse complement dans le génome encodé.
- 
## Fonctionnalités principales
- Lecture de fichiers FASTA et FASTQ.
- Encodage binaire des séquences.
- Support des symboles IUPAC selon plusieurs modes.
- Ajout et suppression de fragments dans une séquence.
- Itérateurs personnalisés pour parcourir les séquences.
- Recherche de k-mers avec leur support et orientation (brin).
- Gestion des erreurs (ignore, afficher, ou exception).

## Remarque: 
Ce projet pourra être étendu pour inclure une étape de mapping de reads, avec des structures comme les suffix arrays.
