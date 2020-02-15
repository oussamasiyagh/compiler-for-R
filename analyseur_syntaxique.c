
#include "analyseur_syntaxique.h"
//analyseur sémantique :

extern char** assignedValues;
extern char** termesDeCalculs;

char functionName[MAX_SIZE];
char variablePrint[MAX_SIZE];
int nombreArguments = 1;
int nombreArgumentsCall =1;
bool insideLoop = false;
void ajouterSymbole() {
    bool trouve = false;
    for (int i = 0; i < dernierIndiceTS; i++) {
        if (strcmp(mot, tableSymbole[i].nom) == 0) {
            trouve = true;
        }
    }
    if (!trouve) {
        strcpy(tableSymbole[dernierIndiceTS].nom, mot);
        tableSymbole[dernierIndiceTS].valNom = NULLVAL;
        dernierIndiceTS++;
    }
}
void changerValSymbole(char name[MAX_SIZE],TSYM class) {
    for (int i = 0; i < dernierIndiceTS; i++) {
        if (strcmp(tableSymbole[i].nom, name) == 0){
            tableSymbole[i].valNom = class;
        }
    }
}
void mettreajourValSymbole() {
    if (strcmp(assignedValues[dernierIndiceAssignedValuesTable-1], "TRUE") == 0 || strcmp(assignedValues[dernierIndiceAssignedValuesTable-1], "FALSE") == 0){

        for (int i = 0; i < dernierIndiceAssignedValuesTable; i++) {
            changerValSymbole(assignedValues[i], BOOLVAL);
        }
    } else if (strcmp(assignedValues[dernierIndiceAssignedValuesTable-1], "NA") == 0){
        for (int i = 0; i < dernierIndiceAssignedValuesTable; i++) {
            changerValSymbole(assignedValues[i], NAVAL);
        }
    } else if (assignedValues[dernierIndiceAssignedValuesTable-1][0] <= '9' && assignedValues[dernierIndiceAssignedValuesTable-1][0] >= '0') {
        for (int i = 0; i < dernierIndiceAssignedValuesTable; i++) {
            //printf("%s--lol \n", assignedValues[dernierIndiceAssignedValuesTable-1]);
            changerValSymbole(assignedValues[i], NUMVAL);
        }
    } else if (strcmp(assignedValues[dernierIndiceAssignedValuesTable-1], "function") == 0){
        for (int i = 0; i < dernierIndiceAssignedValuesTable; i++) {
            //printf("%s--lol \n", assignedValues[dernierIndiceAssignedValuesTable-1]);
            changerValSymbole(assignedValues[i], FUNVAL);
        }
    }
/*
    for (int i = 0; i < dernierIndiceTS; i++) {
        printf("%s--%i--%i \n", tableSymbole[i].nom, tableSymbole[i].valNom, dernierIndiceTS);
    }
*/
    //free pointers:
    for (int i = 0; i < dernierIndiceAssignedValuesTable; i++) {
        printf("%s------------%d \n", assignedValues[i], i);
        free(assignedValues[i]);
    }
    free(assignedValues);
    dernierIndiceAssignedValuesTable = 0;
    assignedValues = (char**)malloc(sizeof(char**)*10);
}
void remplirAssignedValuesTable(){
    assignedValues[dernierIndiceAssignedValuesTable] = (char*)malloc(sizeof(mot));
    strcpy(assignedValues[dernierIndiceAssignedValuesTable], mot);
    //printf("%s--%i \n", assignedValues[dernierIndiceAssignedValuesTable], dernierIndiceAssignedValuesTable);
    dernierIndiceAssignedValuesTable++;
}

void remplirTermesDeCalculs(){
    termesDeCalculs[dernierIndiceTermeDeCalcul] = (char*)malloc(sizeof(mot));
    strcpy(termesDeCalculs[dernierIndiceTermeDeCalcul], mot);
    //printf("%s--%i \n", assignedValues[dernierIndiceAssignedValuesTable], dernierIndiceAssignedValuesTable);
    dernierIndiceTermeDeCalcul++;
}
bool verifierNumericTermes(){
    for (int i = 0; i < dernierIndiceTermeDeCalcul; i++) {
        if(recupererValSymbole(termesDeCalculs[i]) != NUMVAL){
            return false;
        }
    }
    return true;
}
TSYM recupererValSymbole(char s[MAX_SIZE]){
    for (int i = 0; i <dernierIndiceTS ; i++) {
        if (strcmp(s, tableSymbole[i].nom) == 0){
            return tableSymbole[i].valNom;
        }
    }
    return -1;
}


//analyseur_syntaxique :

//program ::= single_input {'\n' {single_input|break}}*
bool program(){
    if (!single_input() && codeToken != BREAK_TOKEN) return false;
    do{
        ScannerLeMotSuivant();
        // printf("%s", mot);
        if (codeToken == BREAK_TOKEN){
            for (int i = 0; i < dernierIndiceTS ; i++) {
                if (tableSymbole[i].valNom == BCLVAL){
                    insideLoop = true;
                }
            }
            if (insideLoop == false){
                afficherErreur(BREAK_ERROR);
            }
            ScannerLeMotSuivant();
        }
        if (single_input()){
            printf("it was another statement\n");
        }
        if (caractere_courant == EOF){
            printf("---> program\n");
            return true;
        }
    }while (codeToken == NEWLINE_TOKEN);
    printf("---> program\n");
    return true;
}


// single_input ::= simple_stmt | compound_stmt

bool single_input(){
    if ( !simple_stmt() && !compound_stmt() ) return false;
    else if (!compound_stmt()){
        printf("---> single_input\n");
    }
    /*
    for (int i = 0; i < dernierIndiceTS; i++) {
        printf("----------------------->%s--%i--%i \n", tableSymbole[i].nom, tableSymbole[i].valNom, i);
    }
*/
    //printf("%s-%i", mot, codeToken);
    return true;
}
// simple_stmt  ::= assign_stmt | lib_stmt | print_stmt
bool simple_stmt() {
    if ( !assign_stmt() && !lib_stmt() && !print_stmt()) return false;
    printf("---> simple_stmt\n");
    return true;
}
//version1.0
// assign_stmt  ::= id Exp_prime
// Exp_prime    ::= [=|<-] aff
// aff          ::= value | assign_stmt

//version 1.1
//assign_stmt ::= id {exp_prime}
//exp_prime   ::= [= |<-] aff
//aff         ::= id {numeric_term | function_call |ex_prime} |num {numeric_term}  | function_stmt  | other_term


bool assign_stmt(){
    if (codeToken != ID_TOKEN) return false;
    ajouterSymbole();
    remplirAssignedValuesTable();
    strcpy(variablePrint, mot);
    ScannerLeMotSuivant();
    if(Exp_prime()){
        printf("il y a une affectation après \n");
    } else{
        if(recupererValSymbole(variablePrint) == NULLVAL){
            afficherErreur(NO_VALUE_ERROR);
        }
    }
    printf("--->assign_stmt\n");
    //free(assignedValues);
    return true;
}
bool Exp_prime(){
    if (codeToken != AFF_FT_TOKEN && codeToken != AFF_ND_TOKEN) return false;
    ScannerLeMotSuivant();
    if (!aff()){
        afficherErreur(ASSIGNEMENT_OR_FUNCTION_CALL_END_STATEMENT_ERROR);
    }
    printf("---> Exp_prime\n");
    return true;
}
bool aff(){
    if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN  && !function_stmt() && !other_term()) return false;
    else if (codeToken == ID_TOKEN){
        remplirTermesDeCalculs();
        //printf("%s\n", mot);
        ajouterSymbole();
        remplirAssignedValuesTable();
        //printf("%s\n", mot);
        strcpy(functionName, mot);
        ScannerLeMotSuivant();
        if (numeric_term()){
            if(verifierNumericTermes() == false){
                afficherErreur(EXPECTED_NUMBER_TYPE);
            }else{
                changerValSymbole(tableSymbole[dernierIndiceTS-1].nom, NUMVAL);
            }
            printf("un simple calcul :) \n");
        }
        if (Exp_prime()){
            printf(" affectation  ? encore -_- \n");
        }
        if (function_call()){
            if(recupererValSymbole(functionName) != FUNVAL){
                afficherErreur(FUNCTION_CALL_ERROR);
            }
            changerValSymbole(variablePrint, NUMVAL);
            printf("c'est un appel à une fonction\n");
        }
       // printf("%s - %d\n", mot, codeToken);
        // case : id <- id
        if(!numeric_term() && !Exp_prime() && !function_call()){
            if (codeToken == ID_TOKEN){
                if(verifierNumericTermes() == false){
                    afficherErreur(EXPECTED_NUMBER_TYPE);
                }else{
                    changerValSymbole(tableSymbole[dernierIndiceTS-1].nom, NUMVAL);
                }
            }
        }
    } else if (codeToken == NUM_TOKEN){
        remplirAssignedValuesTable();
        mettreajourValSymbole();
        ScannerLeMotSuivant();
        if (numeric_term()){
            printf("un simple calcul :) \n");
        }
    }
    printf("--->aff\n");
    return true;
}

// numeric_term ::= [+|-] term { [ + | - ] term }*

bool numeric_term(){
    if(codeToken != PLUS_TOKEN && codeToken != MOINS_TOKEN) return false;
    ScannerLeMotSuivant();
    if(!term()){
        afficherErreur(TERM_ERROR);
    }
    while (codeToken == PLUS_TOKEN || codeToken == MOINS_TOKEN){
        ScannerLeMotSuivant();
        if (!term()){
            afficherErreur(TERM_ERROR);
        }
    }
    printf("---> numeric_term\n");
    return true;
}

// term ::= fact { [ * | / ] fact}*

bool term(){
    if (!fact())return false;
    while( codeToken == MULT_TOKEN || codeToken == DIV_TOKEN){
        ScannerLeMotSuivant();
        if (!fact()){
            afficherErreur(FACT_ERROR);
        }
    }
    printf("---> term\n");
    return true;
}

// fact ::= id | num | '(' numeric_term ')'

bool fact(){
    if ( codeToken != ID_TOKEN && codeToken != NUM_TOKEN && codeToken != PO_TOKEN) return false;
    else if (codeToken == PO_TOKEN) {
        ScannerLeMotSuivant();
        if (!numeric_term()) {
            afficherErreur(NUMBER_EXPECTED_ERROR);
        }
        if (codeToken != PF_TOKEN) {
            //printf("%s", mot);
            afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
        }
    } else if (codeToken == ID_TOKEN || codeToken == NUM_TOKEN){
        if (codeToken == ID_TOKEN){
            remplirTermesDeCalculs();
        }
        ScannerLeMotSuivant();
    }
    printf("---> fact\n");
    return true;
}

// function_stmt ::= 'function' '(' id { , id }* ')' function_body_stmt

bool function_stmt(){
    if ( codeToken != FUNCTION_TOKEN) return false;
    remplirAssignedValuesTable();
    mettreajourValSymbole();
    ScannerLeMotSuivant();
    if ( codeToken != PO_TOKEN) {
        afficherErreur(OPEN_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur(IDENTIFIER_EXPECTED_ERROR);
    }
    ScannerLeMotSuivant();
    while (codeToken == VIR_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN){
            afficherErreur(IDENTIFIER_EXPECTED_ERROR);
        } else {
            nombreArguments++;
        }
        ScannerLeMotSuivant();
    }
    if (codeToken != PF_TOKEN){
        afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (!function_body_stmt()){
        afficherErreur(FUNCTION_BODY_ERROR);
    }
    //enregistrer le nombre d'arguments
    for (int i = 0; i < dernierIndiceTS ; i++) {
        if( tableSymbole[i].valNom == FUNVAL){
            tableSymbole[i].nombreArguments = nombreArguments;
        }
    }
    printf("---> function_stmt\n");
    return true;
}

// function_body_stmt := '{' {\n}* [single_input|return_stmt]  {'\n' {single_input | return_stmt }}*  '}' | simple_stmt | return_stmt

bool function_body_stmt(){
    if ( codeToken != CURO_TOKEN && !simple_stmt() && !return_stmt() ) return false;
    else {
        if (codeToken == CURO_TOKEN){
            ScannerLeMotSuivant();
            while (codeToken == NEWLINE_TOKEN){
                ScannerLeMotSuivant();
            }

            if (!single_input()){
                if (!return_stmt()){
                    //
                    afficherErreur(FUNCTION_BODY_ERROR);
                    //here is the problem
                }
            }

            while(codeToken == NEWLINE_TOKEN){
                ScannerLeMotSuivant();
                if (codeToken == CURF_TOKEN){
                    printf("---> function_body_stmt\n");
                    return true;
                }
                if (!single_input()){
                    if (!return_stmt()){
                       // printf("%d - %s", codeToken, mot);
                        afficherErreur(FUNCTION_BODY_ERROR);
                        //here is the problem
                    }
                }
               // printf("%d - %s\n", codeToken, mot);
            }
            //printf("%d - %s", codeToken, mot);
            if (codeToken == NEWLINE_TOKEN){
                ScannerLeMotSuivant();
            }
            if (codeToken != CURF_TOKEN){
                //printf("%d - %s", codeToken, mot);
                afficherErreur(CLOSE_CURLY_BRACKET_TOKEN_ERROR);
            }
        }
        printf("---> function_body_stmt\n");
    }

    return true;
}

// return_stmt ::= 'return' '(' id ')'

bool return_stmt(){
    if (codeToken != RETURN_TOKEN) return false;
  //  printf("%d - %s", codeToken, mot);
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur(OPEN_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur(IDENTIFIER_EXPECTED_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken != PF_TOKEN){
        afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    printf("---> return_stmt\n");
    return true;
}

// print_stmt ::= 'print' '('[id {nmueric_term} | numeric_term]')'

bool print_stmt() {
    if ( codeToken != PRINT_TOKEN ) return false;
    else {
        ScannerLeMotSuivant();
        if (codeToken != PO_TOKEN) {
            afficherErreur(OPEN_PARENTHESIS_TOKEN_ERROR);
        }
        ScannerLeMotSuivant();
        if (codeToken == ID_TOKEN){
            //printf("%s\n",mot);
            if(recupererValSymbole(mot) != NUMVAL){
                afficherErreur(EXPECTED_NUMBER_TYPE);
            }
            ScannerLeMotSuivant();
            if (numeric_term()){
                //printf("%s", mot);
            }
        }else{
            if(!numeric_term()){
                afficherErreur(NO_ARGUMENT_PRINT_ERROR);
            }
        }
        if (numeric_term()) {
            printf("afficher un calcul 2");
        }

        //printf("%d - %s", codeToken, mot);
        if (codeToken != PF_TOKEN) {
            afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
        }
        ScannerLeMotSuivant();
        printf("---> print_stmt\n");
    }
    return true;
}

// function_call ::= '(' id {, id}* ')'

bool function_call(){
   // printf("%s", mot);
    if (codeToken != PO_TOKEN)return false;
    ScannerLeMotSuivant();
    //printf("%s\n", mot);
    if (codeToken != ID_TOKEN){
        afficherErreur(IDENTIFIER_EXPECTED_ERROR);
    }else{
        if(recupererValSymbole(mot) != NUMVAL){
            afficherErreur(EXPECTED_NUMBER_TYPE);
        }
    }
    ScannerLeMotSuivant();
    while( codeToken == VIR_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN){
            afficherErreur(IDENTIFIER_EXPECTED_ERROR);
        } else {
            nombreArgumentsCall++;
        }
        ScannerLeMotSuivant();
    }
    if (codeToken != PF_TOKEN){
        afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
    }

    for (int i = 0; i < dernierIndiceTS ; i++) {
        if( tableSymbole[i].valNom == FUNVAL){
            if (tableSymbole[i].nombreArguments != nombreArgumentsCall){
                afficherErreur(ARGUMENT_NUMBER_ERROR);
            }
        }
    }
    ScannerLeMotSuivant();
    printf("---> function_call\n");
    return true;
}

// other_term ::= NA | TRUE | FALSE
bool other_term(){
    if (codeToken != TRUE_TOKEN && codeToken != FALSE_TOKEN && codeToken != NA_TOKEN) return false;
    remplirAssignedValuesTable();
    mettreajourValSymbole();
    return true;
}

//lib_stmt ::= 'library' '(' ID ')'
bool lib_stmt(){
    if(codeToken != LIBRARY_TOKEN) return false;
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur(OPEN_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur(IDENTIFIER_EXPECTED_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken != PF_TOKEN){
        afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
    }
    return true;
}
//compound_stmt ::= if_stmt | repeat_stmt | while_stmt | for_stmt
bool compound_stmt(){
    if(!if_stmt() && !repeat_stmt() && !while_stmt() && !for_stmt()) return false;
    printf("---> compund_stmt\n");
    return true;
}

//if_stmt ::= 'if' '(' condition_stmt ')' if_body
//if_body ::= '{' {\n}* program '}' {else_stmt} |simple_stmt {else_stmt} | BREAK {else_stmt}
//else_stmt ::= else [ '{' {\n}* program '}' | {if_stmt} | simple_stmt | BREAK ]
bool if_stmt(){

    if (codeToken != IF_TOKEN)return false;
    ScannerLeMotSuivant();
    //printf("%d - %s", codeToken, mot);
    if (codeToken != PO_TOKEN){
        afficherErreur(OPEN_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();

    if (!condition_stmt()){
        afficherErreur(CONDITION_ERROR);
    }

    if (codeToken != PF_TOKEN){
  //      printf("%d - %s", codeToken, mot);
        afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (!if_body()){
        afficherErreur(IF_BODY_ERROR);
    }
    printf("---> if_stmt\n");
    return true;
}
bool if_body(){
    if ( codeToken != CURO_TOKEN && !simple_stmt() && codeToken != BREAK_TOKEN) return false;
    if (codeToken == CURO_TOKEN){
        ScannerLeMotSuivant();
        //------------------------------------------------
        while (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }
        if (!program()){
            afficherErreur(IF_BODY_ERROR);
        }
        /*
        if (!single_input()){
            if (codeToken != BREAK_TOKEN){
                afficherErreur(IF_BODY_ERROR);
                //here is the problem
            }
            ScannerLeMotSuivant();
        }

        //------------------------------------------------
        while(codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
            if (codeToken == CURF_TOKEN){
                printf("---> if_body\n");
                ScannerLeMotSuivant();
                if (else_stmt()){
                    printf("there is an ELSE\n");
                }
                return true;
            }
            if (!single_input()){
                if (codeToken != BREAK_TOKEN){
                    afficherErreur(IF_BODY_ERROR);
                    //here is the problem
                }
                ScannerLeMotSuivant();
            }

            //printf("%d - %s\n", codeToken, mot);
        }
        //------------------------------------------------

         */

        if (codeToken != CURF_TOKEN){
            //printf("%d - %s", codeToken, mot);
            afficherErreur(CLOSE_CURLY_BRACKET_TOKEN_ERROR);
        }
        //printf("%d - %s", codeToken, mot);
        ScannerLeMotSuivant();
        //printf("%d - %s", codeToken, mot);
        /*while (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }*/
        printf("---> if_body\n");
        //printf("%d - %s", codeToken, mot);
        if (else_stmt()){
            printf("there is an ELSE\n");
        }
        return true;
    }
    if (codeToken == BREAK_TOKEN){
        ScannerLeMotSuivant();
        printf("---> if_body\n");
        if (else_stmt()){
            printf("there is an ELSE\n");
        }
    }
    printf("---> if_body\n");
    if (else_stmt()){
        printf("it was an else_stmt\n");
    }

    return true;
}
bool else_stmt(){
    if (codeToken != ELSE_TOKEN) return false;
    ScannerLeMotSuivant();
    if (codeToken == CURO_TOKEN){
        ScannerLeMotSuivant();
        //------------------------------------------------
        while (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }
        if (!program()){
            afficherErreur(ELSE_STATEMENT_BODY);
        }
        /*
        if (!single_input()){
            if (codeToken != BREAK_TOKEN){

                afficherErreur(ELSE_STATEMENT_BODY);
                //here is the problem
            }
            ScannerLeMotSuivant();
        }
        //------------------------------------------------
        while(codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
            if (codeToken == CURF_TOKEN){
                printf("---> else_body\n");
                ScannerLeMotSuivant();
                if (else_stmt()){
                    printf("there is an ELSE\n");
                }
                return true;
            }
            if (!single_input()){
                if (codeToken != BREAK_TOKEN){
                    //printf("%d - %s", codeToken, mot);
                    afficherErreur(ELSE_STATEMENT_BODY);
                    //here is the problem
                }
                ScannerLeMotSuivant();
            }

            //printf("%d - %s\n", codeToken, mot);
        }
        */
        //------------------------------------------------
        /*
        while (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }*/
        if (codeToken != CURF_TOKEN){
            //printf("%d - %s", codeToken, mot);
            afficherErreur(CLOSE_CURLY_BRACKET_TOKEN_ERROR);
        }
        ScannerLeMotSuivant();
        printf("---> else_body\n");
        return true;
    }
    if (if_stmt()){
        printf("another if_stmt\n");
        return true;
    }
    if (simple_stmt()){
        return true;
    }
    if (codeToken == BREAK_TOKEN){
        printf("---> break\n");
        //printf("%d - %s", codeToken, mot);
        return true;
    }
}

//while_stmt ::= 'while' '(' condition_stmt ')' loop_body

//version 1.0
//loop_body ::= '{' {\n}* {single_input|BREAK} {'\n' {single_input |BREAK} }* '}' | simple_stmt | BREAK

//version 1.1
//loop_body ::= '{' {\n}* program '}' | simple_stmt | BREAK
bool while_stmt(){
    if (codeToken != WHILE_TOKEN) return false;
    ajouterSymbole();
    changerValSymbole(mot, BCLVAL);
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur(OPEN_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (!condition_stmt()){
        afficherErreur(CONDITION_ERROR);
    }

    if (codeToken != PF_TOKEN){
        afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (!loop_body()){
        afficherErreur(LOOP_BODY_ERROR);
    }
    //ScannerLeMotSuivant();
    printf("---> while_stmt\n");
    return true;
}
bool loop_body(){
    if (codeToken != CURO_TOKEN && codeToken != BREAK_TOKEN && !simple_stmt()) return false;
    if (codeToken == CURO_TOKEN){
        ScannerLeMotSuivant();
        //------------------------------------------------
        while (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }

        if (!program()){
            afficherErreur(LOOP_BODY_ERROR);
        }
        /*
        if (!single_input()){
            if (codeToken != BREAK_TOKEN){
                afficherErreur(LOOP_BODY_ERROR);
                //here is the problem
            }
            ScannerLeMotSuivant();
        }*/
        //------------------------------------------------
        /*
        do{
            ScannerLeMotSuivant();
            if(codeToken != NEWLINE_TOKEN && codeToken != CURF_TOKEN){
                if (!single_input()){
                    if (codeToken != BREAK_TOKEN){
                        //printf("%d - %s", codeToken, mot);
                        afficherErreur(LOOP_BODY_ERROR);
                        //here is the problem
                    }
                    //printf("%d - %s-", codeToken, mot);
                }
            }
        }while (codeToken != CURF_TOKEN);

         */
        /*while(codeToken == NEWLINE_TOKEN ){


            if (codeToken == CURF_TOKEN){
                printf("---> loop_body\n");
                ScannerLeMotSuivant();
                return true;
            }
            if (!single_input()){
                if (codeToken != BREAK_TOKEN){
                    //printf("%d - %s", codeToken, mot);
                    afficherErreur(LOOP_BODY_ERROR);
                    //here is the problem
                }
                //printf("%d - %s-", codeToken, mot);
            }

        }*/
        //------------------------------------------------
        if (codeToken != CURF_TOKEN){
            afficherErreur(CLOSE_CURLY_BRACKET_TOKEN_ERROR);
          //  printf("%d - %s", codeToken, mot);
        }
        ScannerLeMotSuivant();

        printf("---> loop_body\n");
  //      printf("%d - %s-", codeToken, mot);
        return true;
    }
    printf("---> loop_body\n");
    return true;
}

//repeat_stmt ::= 'repeat' loop_body
bool repeat_stmt(){
    if (codeToken != REPEAT_TOKEN) return false;
    ajouterSymbole();
    changerValSymbole(mot, BCLVAL);
    ScannerLeMotSuivant();
    if (!loop_body()){
        afficherErreur(LOOP_BODY_ERROR);
    }
    //ScannerLeMotSuivant();
    printf("---> repeat_stmt\n");
    return true;
}

//for_stmt ::= 'for' '(' id 'in' [id|num] {:[id|num]} ')' loop_body
bool for_stmt(){
    if (codeToken != FOR_TOKEN) return false;
    ajouterSymbole();
    changerValSymbole(mot, BCLVAL);
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur(OPEN_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur(IDENTIFIER_EXPECTED_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken != IN_TOKEN){
        afficherErreur(IN_EXPECTED_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN){
        afficherErreur(NUMBER_ID_EXPECTED_ERROR);
    }
    ScannerLeMotSuivant();
    if (codeToken == DPT_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN){
            afficherErreur(NUMBER_ID_EXPECTED_ERROR);
        }
        ScannerLeMotSuivant();
    }
    if (codeToken != PF_TOKEN){
        afficherErreur(CLOSE_PARENTHESIS_TOKEN_ERROR);
    }
    ScannerLeMotSuivant();
    if (!loop_body()){
        afficherErreur(LOOP_BODY_ERROR);
    }
    //ScannerLeMotSuivant();
    printf("---> for_stmt\n");
    return true;
}

//condition_stmt ::= [id|num] { [== | !=] [id|num]} {[&&| ||] conditon_stmt} || '!' [id|num] {[&&| ||] conditon_stmt}
bool condition_stmt(){
    if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN && codeToken != LOGNOT_TOKEN) return false;

    else if (codeToken != LOGNOT_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken == EQUAL_TOKEN || codeToken == DIFF_TOKEN){
            ScannerLeMotSuivant();
            if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN){
                afficherErreur(NUMBER_ID_EXPECTED_ERROR);
            }
            ScannerLeMotSuivant();
        }
        while (codeToken == LOGAND_TOKEN || codeToken == LOGOR_TOKEN){
            ScannerLeMotSuivant();
            if (!condition_stmt()){
                return false;
            }
        }
        printf("---> condition_stmt\n");
        return true;
    } else{
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN) {
            afficherErreur(NUMBER_ID_EXPECTED_ERROR);
        }
        ScannerLeMotSuivant();
        while (codeToken == LOGAND_TOKEN || codeToken == LOGOR_TOKEN){
            ScannerLeMotSuivant();
            if (!condition_stmt()){
                return false;
            }
        }
        printf("---> condition_stmt\n");
        return true;
    }
}

