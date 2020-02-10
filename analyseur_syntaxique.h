//
// Created by  Oussama Siyagh on 09/02/2020.
//

#ifndef UNTITLED1_ANALYSEUR_SYNTAXIQUE_H
#define UNTITLED1_ANALYSEUR_SYNTAXIQUE_H

#include "main.h"
#include "analyseur_lexical.h"


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

#endif //UNTITLED1_ANALYSEUR_SYNTAXIQUE_H
