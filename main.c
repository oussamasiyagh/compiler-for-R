

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
} //analyseur_syntaxique :
// single_input ::= simple_stmt | compound_stmt

bool single_input(){
    if ( !simple_stmt() && !compound_stmt() ) return false;
    return true;
}
// simple_stmt  ::= assign_stmt | lib_stmt | print_stmt
bool simple_stmt() {
    if ( !assign_stmt() && !lib_stmt() && !print_stmt()) return false;
    return true;
}

// assign_stmt ::= exp [=|<-] value

bool assign_stmt(){
    if (!exp()) return false;
    if (codeToken != EQUAL_TOKEN && codeToken != AFF_ND_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (!value()){
        afficherErreur();
    }
}

// Exp  ::= id { [= | <-] id exp1 } *

bool Exp(){
    if (codeToken != ID_TOKEN) return false;
    ScannerLeMotSuivant();
    while(codeToken == EQUAL_TOKEN || codeToken == AFF_ND_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN){
            afficherErreur();
        }
        ScannerLeMotSuivant();
    }
}

//value ::= numeric_term | function_call | other_term | function_stmt

bool value(){
    if (!numeric_term && !function_call && !other_term && !function_stmt) return false;
    return true;
}

// numeric_term ::= term { [ + | - ] term }*

bool numeric_term(){
    if(!term) return false;
    while (codeToken == PLUS_TOKEN || codeToken == MOINS_TOKEN){
        ScannerLeMotSuivant();
        if (!term()){
            afficherErreur();
        }
    }
}

//