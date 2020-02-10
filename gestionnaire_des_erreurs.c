//
// Created by  Oussama Siyagh on 09/02/2020.
//

#include "gestionnaire_des_erreurs.h"

char erreurs[NOMBRES_DES_ERREURS][90] = {
        "'=' or '<-' symbol was expected",
        "Expected an ASSIGNEMENT or a FUNCTION CALL",
        "'}' symbol was expected",
        "'{' symbol was expected",
        "error on CONDITION ",
        "numeric term was expected",
        "A number was expected after ':'",
        "An identifier or a number was expected",
        "identifier was expected",
        "'(' symbol was expected",
        "')' symbol was expected",
        "'in' symbol was expected",
        "IF statement error",
        "ELSE statement error",
        "Loop content error",
        "FUNCTION statement body error",
        "Exepected FACT after '*' or '/'",
        "Exepected TERM after '+' or '-'"};

void afficherErreur(code_erreur erreur) {
    if (erreur >= NOMBRES_DES_ERREURS){
        printf("Error number %i: error without a message yet on line %i \n", erreur);
    }
    else{
        printf("Error number %i: %s on line \n", erreur, erreurs[erreur]);
    }
}