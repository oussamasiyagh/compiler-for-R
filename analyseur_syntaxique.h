//
// Created by  Oussama Siyagh on 09/02/2020.
//

#ifndef UNTITLED1_ANALYSEUR_SYNTAXIQUE_H
#define UNTITLED1_ANALYSEUR_SYNTAXIQUE_H

#include "main.h"
#include "analyseur_lexical.h"

bool program();
bool single_input();
bool simple_stmt();
bool assign_stmt();
bool aff();
bool Exp_prime();
bool numeric_term();
bool term();
bool fact();
bool function_stmt();
bool function_body_stmt();
bool function_call();
bool print_stmt();
bool return_stmt();
bool other_term();
bool lib_stmt();
bool compound_stmt();
bool if_stmt();
bool if_body();
bool else_stmt();
bool repeat_stmt();
bool while_stmt();
bool loop_body();
bool for_stmt();
bool condition_stmt();

//symantic analysis:
typedef enum {
    NULLVAL, //0
    NAVAL, //1
    BOOLVAL, //2
    NUMVAL,//3
    FUNVAL,//4
    BCLVAL,
} TSYM;
void ajouterSymbole();
void changerValSymbole(char[],TSYM);
void mettreajourValSymbole();
void remplirAssignedValuesTable();
void remplirTermesDeCalculs();
TSYM recupererValSymbole(char[]);

extern int dernierIndiceAssignedValuesTable;
extern int dernierIndiceTermeDeCalcul;

struct symbole {
    char nom[MAX_SIZE];
    TSYM valNom;
    int nombreArguments;
};

struct symbole tableSymbole[100];
extern int dernierIndiceTS;

#endif //UNTITLED1_ANALYSEUR_SYNTAXIQUE_H
