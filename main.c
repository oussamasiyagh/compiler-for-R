

#include "analyseur_lexical.h"

int dernierIndice = 0;

int main() {
    f = fopen("/Users/macbook/Documents/untitled1/code.r", "r");
    viderMot();
    lire_caractere_suivant();
    while (ScannerLeMotSuivant()){
        associerToken();
        printf("-> %s  ---> %d \n", mot, codeToken);
        viderMot();
    }
    printf( "FIN !! \n");
    fclose(f);
    return 0;
}
/* //analyseur_syntaxique :

 bool single_input(){
    if (simple_stmt()){
        if (small_stmt()){
            if (assign_stmt()){
                if (codeToken != ID_TOKEN) return false;
                ScannerLeMotSuivant();
                if (codeToken != AFF_ND_TOKEN) return false;
                if (!val_stmt()) return false;
                if (value()){
                    if(codeToken != NUM_TOKEN) return false;
                }
            }
        }
    }
}


*/

