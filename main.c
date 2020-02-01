#include "analyseur_lexical.h"

int dernierIndice = 0;


void afficherErreur();
bool single_input();
bool simple_stmt();
bool assign_stmt();
bool Exp();
bool value();
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

int main() {
    f = fopen("/Users/macbook/Documents/untitled1/code.r", "r");
    viderMot();
    lire_caractere_suivant();

    //tester l'analyseur lexical:
    /*
    while (ScannerLeMotSuivant()){
        associerToken();
        printf("-> %s  ---> %d \n", mot, codeToken);
        viderMot();
    }
    printf( "FIN !! \n");
    */

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
    printf("---> single_input\n");
    if (simple_stmt()){
        printf("single_input valid");
    }
    return true;
}
// simple_stmt  ::= assign_stmt | lib_stmt | print_stmt
bool simple_stmt() {
    if ( !assign_stmt() && !lib_stmt() && !print_stmt()) return false;
    printf("---> simple_stmt\n");
    return true;
}

// assign_stmt ::= exp [=|<-] value

bool assign_stmt(){
    if (!Exp()) return false;
    printf("---> assign_stmt\n");
    if (codeToken != AFF_FT_TOKEN && codeToken != AFF_ND_TOKEN){
        printf("--->%s---->%d", mot, codeToken);
        afficherErreur();
    }
    printf("---> assign_stmt valid\n");
    ScannerLeMotSuivant();
    if (!value()){
        afficherErreur();
    }
    return true;
}

// Exp  ::= id { [= | <-] id }*

bool Exp(){
    if (codeToken != ID_TOKEN) return false;
    printf("---> Exp\n");
    ScannerLeMotSuivant();
    while(codeToken == AFF_FT_TOKEN || codeToken == AFF_ND_TOKEN){
        ScannerLeMotSuivant();
        if (codeToken != ID_TOKEN){
            afficherErreur();
        }
        ScannerLeMotSuivant();
    }
    return true;
}

//value ::= numeric_term | function_call | other_term | function_stmt

bool value(){
    if (!numeric_term() && !function_call() && !other_term() && !function_stmt()) return false;
    printf("---> value\n");
    return true;
}

// numeric_term ::= term { [ + | - ] term }*

bool numeric_term(){
    if(!term()) return false;
    printf("---> numeric_term\n");
    while (codeToken == PLUS_TOKEN || codeToken == MOINS_TOKEN){
        ScannerLeMotSuivant();
        if (!term()){
            afficherErreur();
        }
    }
    return true;
}

// term ::= fact { [ * | / ] fact}*

bool term(){
    if (!fact()) return false;
    printf("---> term\n");
    while( codeToken == MULT_TOKEN || codeToken == DIV_TOKEN){
        ScannerLeMotSuivant();
        if (!fact()){
            afficherErreur();
        }
    }
    return true;
}

// fact ::= id | num | '(' numeric_term ')'

bool fact(){
    if ( codeToken != ID_TOKEN && codeToken != NUM_TOKEN && codeToken != PO_TOKEN) return false;
    else {
        printf("---> fact\n");
        if (codeToken == PO_TOKEN) {
            ScannerLeMotSuivant();
            if (!numeric_term()) {
                printf("hna");
                afficherErreur();
                printf("salat hna");
            }
            if (codeToken != PF_TOKEN) {
                afficherErreur();
            }
        }
    }
    return true;
}

// function_stmt ::= 'function' '(' id { , id }* ')' function_body_stmt

bool function_stmt(){
    if ( codeToken != FUNCTION_TOKEN) return false;
    printf("---> function_stmt\n");
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
    if (!function_body_stmt()){
        afficherErreur();
    }
    return true;
}

// function_body_stmt := '{' single_input { '\n' single_input }* '}' | simple_stmt | return_stmt

bool function_body_stmt(){
    if ( codeToken != CURO_TOKEN && !simple_stmt() && !return_stmt() ) return false;
    else {
        printf("---> function_body_stmt\n");
        if (codeToken == CURO_TOKEN){

            ScannerLeMotSuivant();
            if ( !single_input() ){
                afficherErreur();
            }
            while(codeToken == NEWLINE_TOKEN){
                if (!single_input()){
                    afficherErreur();
                }
            }
            if (codeToken != CURF_TOKEN){
                afficherErreur();
            }
        }
    }
    return true;
}

// return_stmt ::= 'return' '(' id ')'

bool return_stmt(){
    if (codeToken != RETURN_TOKEN) return false;
    printf("---> return_stmt\n");
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

// print_stmt ::= 'print' '(' value ')' | value

bool print_stmt(){
    if ( codeToken != PRINT_TOKEN && !value()) return false;
    else {
        printf("---> print_stmt\n");
        if (codeToken == PRINT_TOKEN) {
            ScannerLeMotSuivant();
            if (codeToken != PO_TOKEN) {
                afficherErreur();
            }
            ScannerLeMotSuivant();
            if (!value()) {
                afficherErreur();
            }
            if (codeToken != PF_TOKEN) {
                afficherErreur();
            }
        }
    }
    return true;
}

// function_call ::= id '(' id {, id}* ')'

bool function_call(){
    if (codeToken != ID_TOKEN)return false;
    printf("---> function_call\n");
    ScannerLeMotSuivant();
    if (codeToken != PO_TOKEN){
        afficherErreur();
    }
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
    return true;
}

bool other_term(){
    return false;
}
bool lib_stmt(){
    return false;
}
bool compound_stmt(){
    return false;
}

void afficherErreur(){
    printf("ERREUR \n");
}