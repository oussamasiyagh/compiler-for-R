#include "analyseur_lexical.h"
int dernierIndice = 0;

void afficherErreur();
bool single_input();
bool simple_stmt();
bool assign_stmt();
bool aff();
bool Exp();
bool Exp_prime();
//bool value();
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

//analyseur_syntaxique :
// single_input ::= simple_stmt | compound_stmt

bool single_input(){
    if ( !simple_stmt() && !compound_stmt() ) return false;
    else if (!compound_stmt()){
        printf("---> single_input\n");
    }
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
    ScannerLeMotSuivant();
    if(Exp_prime()){
        printf("il ya une affectation après \n");
    }
    printf("--->assign_stmt\n");
    return true;
}
bool Exp_prime(){
    if (codeToken != AFF_FT_TOKEN && codeToken != AFF_ND_TOKEN) return false;
    ScannerLeMotSuivant();
    if (!aff()){
        afficherErreur();
    }
    printf("---> Exp_prime\n");
    return true;
}
bool aff(){
    if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN  && !function_stmt() && !other_term()) return false;
    else if (codeToken == ID_TOKEN){
        ScannerLeMotSuivant();
        //printf("%s", mot);
        if (numeric_term()){
            printf("un simple calcul :) \n");
        }
        if (Exp_prime()){
            printf(" affectation  ? encore -_- \n");
        }
        if (function_call()){
            printf(" c'est un appel à une fonction");
        }
    } else if (codeToken == NUM_TOKEN){
        ScannerLeMotSuivant();
        if (numeric_term()){
            printf("un simple calcul :) \n");
        }
    }
    return true;
}

//value ::= numeric_term
/*
bool value(){
    if (!numeric_term() && !function_call() && !other_term() && !function_stmt()) return false;
    printf("---> value\n");
    return true;
}
*/
// numeric_term ::= [+|-] term { [ + | - ] term }*

bool numeric_term(){
    if(codeToken != PLUS_TOKEN && codeToken != MOINS_TOKEN) return false;
    ScannerLeMotSuivant();
    if(!term()){
        afficherErreur();
    }
    while (codeToken == PLUS_TOKEN || codeToken == MOINS_TOKEN){
        ScannerLeMotSuivant();
        if (!term()){
            afficherErreur();
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
            afficherErreur();
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
                afficherErreur();
            }
            if (codeToken != PF_TOKEN) {
                printf("%s", mot);
                afficherErreur();
            }
        } else if (codeToken == ID_TOKEN || codeToken == NUM_TOKEN){
                    ScannerLeMotSuivant();
                }
    printf("---> fact\n");
    return true;
}

// function_stmt ::= 'function' '(' id { , id }* ')' function_body_stmt

bool function_stmt(){
    if ( codeToken != FUNCTION_TOKEN) return false;
    ScannerLeMotSuivant();
    if ( codeToken != PO_TOKEN) {
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    while (codeToken == VIR_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN){
            afficherErreur();
        }
        ScannerLeMotSuivant();
    }
    if (codeToken != PF_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (!function_body_stmt()){
        afficherErreur();
    }
    printf("---> function_stmt\n");
    return true;
}

// function_body_stmt := '{' {\n}* single_input|  {'\n' {single_input | return_stmt }}*  '}' | simple_stmt | return_stmt

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
                    printf("%d - %s", codeToken, mot);
                    afficherErreur();
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
                        printf("%d - %s", codeToken, mot);
                        afficherErreur();
                        //here is the problem
                    }
                }
                printf("%d - %s\n", codeToken, mot);
            }
            //printf("%d - %s", codeToken, mot);
            if (codeToken == NEWLINE_TOKEN){
               ScannerLeMotSuivant();
            }
            if (codeToken != CURF_TOKEN){
                //printf("%d - %s", codeToken, mot);
                afficherErreur();
            }
        }
        printf("---> function_body_stmt\n");
    }

    return true;
}

// return_stmt ::= 'return' '(' id ')'

bool return_stmt(){
    if (codeToken != RETURN_TOKEN) return false;
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken != PF_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    printf("---> return_stmt\n");
    return true;
}

// print_stmt ::= 'print' '('[id {nmueric_term} | numeric_term]')'

bool print_stmt(){
    if ( codeToken != PRINT_TOKEN ) return false;
    else {
            ScannerLeMotSuivant();
            if (codeToken != PO_TOKEN) {
                afficherErreur();
            }
            ScannerLeMotSuivant();
            if (codeToken == ID_TOKEN){
                ScannerLeMotSuivant();
                if (numeric_term()){
                    //printf("%s", mot);
                }

            }
            if (numeric_term()) {
                printf("afficher un calcul 2");
            }
            //printf("%d - %s", codeToken, mot);
            if (codeToken != PF_TOKEN) {
                afficherErreur();
            }
            ScannerLeMotSuivant();
        printf("---> print_stmt\n");
    }
    return true;
}

// function_call ::= '(' id {, id}* ')'

bool function_call(){
    printf("%s", mot);
    if (codeToken != PO_TOKEN)return false;
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    while( codeToken == VIR_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN){
            afficherErreur();
        }
        ScannerLeMotSuivant();
    }
    if (codeToken != PF_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    printf("---> function_call\n");
    return true;
}

// other_term ::= NA | TRUE | FALSE
bool other_term(){
    if (codeToken != TRUE_TOKEN && codeToken != FALSE_TOKEN && codeToken != NA_TOKEN) return false;
    return true;
}

//lib_stmt ::= 'library' '(' ID ')'
bool lib_stmt(){
    if(codeToken != LIBRARY_TOKEN) return false;
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken != PF_TOKEN){
        afficherErreur();
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
//if_body ::= '{' {\n}* {single_input|BREAK} {'\n' {single_input |BREAK} }* '}' {else_stmt} |simple_stmt {else_stmt} | BREAK
//else_stmt ::= else [ '{' {\n}* {single_input|BREAK} {'\n' {single_input |BREAK} }* '}' | {if_stmt} ]
bool if_stmt(){
    if (codeToken != IF_TOKEN)return false;
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();

    if (!condition_stmt()){
        afficherErreur();
    }

    if (codeToken != PF_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (!if_body()){
        afficherErreur();
    }
    printf("---> if_stmt\n");
    return true;
}
bool if_body(){
    if ( codeToken != CURO_TOKEN && !simple_stmt() && codeToken != BREAK_TOKEN) return false;
    if (codeToken == CURO_TOKEN){
            ScannerLeMotSuivant();
            while (codeToken == NEWLINE_TOKEN){
                ScannerLeMotSuivant();
            }

            if (!single_input()){
                if (codeToken != BREAK_TOKEN){
                    printf("%d - %s", codeToken, mot);
                    afficherErreur();
                    //here is the problem
                }
            }

            while(codeToken == NEWLINE_TOKEN){
                ScannerLeMotSuivant();
                if (codeToken == CURF_TOKEN){
                    printf("---> if_body\n");
                    return true;
                }
                if (!single_input()){
                    if (codeToken != BREAK_TOKEN){
                        printf("%d - %s", codeToken, mot);
                        afficherErreur();
                        //here is the problem
                    }
                }
                printf("%d - %s\n", codeToken, mot);
            }
            //printf("%d - %s", codeToken, mot);
            if (codeToken == NEWLINE_TOKEN){
                ScannerLeMotSuivant();
            }
            if (codeToken != CURF_TOKEN){
                //printf("%d - %s", codeToken, mot);
                afficherErreur();
            }
            ScannerLeMotSuivant();
            if (else_stmt()){
                printf("there is an ELSE\n");
            }
        return true;
    }
    if (else_stmt()){
        printf("there is an ELSE\n");
    }
    printf("---> if_body\n");
    return true;
    }
bool else_stmt(){
    if (codeToken != ELSE_TOKEN) return false;
    ScannerLeMotSuivant();
    if (codeToken == CURO_TOKEN){
        ScannerLeMotSuivant();
        while (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }

        if (!single_input()){
            if (codeToken != BREAK_TOKEN){
                printf("%d - %s", codeToken, mot);
                afficherErreur();
                //here is the problem
            }
        }

        while(codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
            if (codeToken == CURF_TOKEN){
                printf("---> else_body\n");
                return true;
            }
            if (!single_input()){
                if (codeToken != BREAK_TOKEN){
                    printf("%d - %s", codeToken, mot);
                    afficherErreur();
                    //here is the problem
                }
            }
            printf("%d - %s\n", codeToken, mot);
        }
        //printf("%d - %s", codeToken, mot);
        if (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }
        if (codeToken != CURF_TOKEN){
            //printf("%d - %s", codeToken, mot);
            afficherErreur();
        }
        printf("---> else_stmt");
        return true;
    }
    if (if_stmt()){
        printf("another if_stmt\n");
        return true;
    }
}

//while_stmt ::= 'while' '(' condition_stmt ')' loop_body
//loop_body ::= '{' {\n}* {single_input|BREAK} {'\n' {single_input |BREAK} }* '}' | simple_stmt | BREAK
bool while_stmt(){
    if (codeToken != WHILE_TOKEN) return false;
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (!condition_stmt()){
        afficherErreur();
    }
    if (codeToken != PF_TOKEN){
        afficherErreur();
    }
    if (!loop_body()){
        afficherErreur();
    }
    printf("---> while_stmt");
    return true;
}
bool loop_body(){
    if (codeToken != CURO_TOKEN && codeToken != BREAK_TOKEN && !simple_stmt()) return false;
    if (codeToken == CURO_TOKEN){
        ScannerLeMotSuivant();
        while (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }

        if (!single_input()){
            if (codeToken != BREAK_TOKEN){
                printf("%d - %s", codeToken, mot);
                afficherErreur();
                //here is the problem
            }
        }

        while(codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
            if (codeToken == CURF_TOKEN){
                printf("---> loop_body\n");
                return true;
            }
            if (!single_input()){
                if (codeToken != BREAK_TOKEN){
                    printf("%d - %s", codeToken, mot);
                    afficherErreur();
                    //here is the problem
                }
            }
            printf("%d - %s\n", codeToken, mot);
        }
        //printf("%d - %s", codeToken, mot);
        if (codeToken == NEWLINE_TOKEN){
            ScannerLeMotSuivant();
        }
        if (codeToken != CURF_TOKEN){
            //printf("%d - %s", codeToken, mot);
            afficherErreur();
        }
        printf("---> loop_body");
        return true;
    }
    return true;
}

//repeat_stmt ::= 'repeat' loop_body
bool repeat_stmt(){
    if (codeToken != REPEAT_TOKEN) return false;
    ScannerLeMotSuivant();
    if (!loop_body()){
        afficherErreur();
    }
    printf("---> repeat_stmt\n");
    return true;
}

//for_stmt ::= 'for' '(' id 'in' [id| num:num] ')' loop_body
bool for_stmt(){
    if (codeToken != FOR_TOKEN) return false;
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken != IN_TOKEN){
        afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN){
       afficherErreur();
    }
    ScannerLeMotSuivant();
    if (codeToken == DPT_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN && codeToken != NUM_TOKEN){
            afficherErreur();
        }
        ScannerLeMotSuivant();
    }
    if (codeToken != PF_TOKEN){
        afficherErreur();
    }
    if (!loop_body()){
        afficherErreur();
    }
    printf("---> for_stmt");
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
                afficherErreur();
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
            afficherErreur();
        }
        while (codeToken == LOGAND_TOKEN || codeToken == LOGOR_TOKEN){
            ScannerLeMotSuivant();
            if (!condition_stmt()){
                return false;
            }
        }
        printf("---> condition_stmt");
        return true;
    }
}
void afficherErreur(){
    printf("ERREUR \n");
}