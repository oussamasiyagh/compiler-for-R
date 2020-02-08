//
// Created by  Oussama Siyagh on 29/01/2020.
//

#ifndef UNTITLED1_MAIN_H
#define UNTITLED1_MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

typedef enum{
    ID_TOKEN,
    NA_TOKEN,
    TRUE_TOKEN,
    FALSE_TOKEN,
    LIBRARY_TOKEN,
    FOR_TOKEN,
    IN_TOKEN,
    WHILE_TOKEN,
    REPEAT_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    RETURN_TOKEN,
    FUNCTION_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    PT_TOKEN,
    DPT_TOKEN,
    VIR_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    DIFF_TOKEN,
    AFF_FT_TOKEN,
    AFF_ND_TOKEN,
    AFF_TD_TOKEN,
    BACKSLA_TOKEN,
    NEWLINE_TOKEN,
    TAB_TOKEN,
    COM_TOKEN,
    ACCO_TOKEN,
    ACCF_TOKEN,
    LOGNOT_TOKEN,
    ELWOR_TOKEN,
    ELWAND_TOKEN,
    LOGAND_TOKEN,
    LOGOR_TOKEN,
    EQUAL_TOKEN,
    PRINT_TOKEN,
    CURO_TOKEN,
    CURF_TOKEN,
    NUM_TOKEN,
    BREAK_TOKEN,
    DBQOUTE_TOKEN,
    FIN_TOKEN
}CODES_LEX;
typedef enum _bool{
    false, true
}bool;

FILE *f;
char mot[MAX_SIZE];
char caractere_courant;
extern int dernierIndice;
bool nouvLigne;

CODES_LEX codeToken;
#endif //UNTITLED1_MAIN_H
