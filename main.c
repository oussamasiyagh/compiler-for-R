#include "analyseur_syntaxique.h"
int dernierIndice = 0;
int ligneNumero = 1;
//semantic rules:
// rule 1 : -all needed variables must have a value !
//          -all numeric terms must use only numeric class !
// rule 2 : -all function calls must be referenced to an existed function
//          -must have the same exact number of arguments
//            -BREAK inside boucle

int dernierIndiceTS = 0;

int dernierIndiceAssignedValuesTable = 0;
int dernierIndiceTermeDeCalcul = 0;

char** assignedValues;
char** termesDeCalculs;

int main() {
    f = fopen("/Users/macbook/Documents/untitled1/test1.r", "r");
    viderMot();
    lire_caractere_suivant();

    //tester l'analyseur lexical:

    /*while (ScannerLeMotSuivant()){
        associerToken();
        printf("-> %s ---> %d \n", mot, codeToken);
        viderMot();
    }
    printf( "FIN !! \n");*/


    //tester l'analyseur syntaxique et sémantique:
    ScannerLeMotSuivant();
    assignedValues = (char**)malloc(sizeof(char**)*10);
    termesDeCalculs = (char**)malloc(sizeof(char**)*10);
    program();
    for (int i = 0; i < dernierIndiceTS; i++) {
        printf("%s--%i--%i \n", tableSymbole[i].nom, tableSymbole[i].valNom, tableSymbole[i].nombreArguments);
    }

    fclose(f);
    return 0;
}



