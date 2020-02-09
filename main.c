#include "analyseur_syntaxique.h"
int dernierIndice = 0;

int main() {
    f = fopen("/Users/macbook/Documents/untitled1/code.r", "r");
    viderMot();
    lire_caractere_suivant();

    //tester l'analyseur lexical:

    /*while (ScannerLeMotSuivant()){
        associerToken();
        printf("-> %s ---> %d \n", mot, codeToken);
        viderMot();
    }
    printf( "FIN !! \n");*/


    //tester l'analyseur syntaxique:
    ScannerLeMotSuivant();
    single_input();
    fclose(f);
    return 0;
}
