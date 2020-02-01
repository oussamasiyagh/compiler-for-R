//
// Created by  Oussama Siyagh on 29/01/2020.
//

#include "analyseur_lexical.h"


bool estUnChiffre(){
    if (caractere_courant >= '0' && caractere_courant <='9') return true;
    else return false;
}
bool estUnCaractere(){
    if (caractere_courant >= 'A' && caractere_courant <='z') return true;
    else return false;
}
bool estSpecial(){
    switch (caractere_courant){
        case '.':
            return true;
        case ',':
            return true;
        case '<' :
            return true;
        case '-' :
            return true;
        case '>' :
            return true;
        case '=' :
            return true;
        case '!' :
            return true;
        case '\\' :
            return true;
        case '{' :
            return true;
        case '}' :
            return true;
        case '(' :
            return true;
        case ')' :
            return true;
        case '[' :
            return true;
        case ']' :
            return true;
        case '#' :
            return true;
        case '&' :
            return true;
        case '|' :
            return true;
        case '/' :
            return true;
        case '+' :
            return true;
        case '*' :
            return true;
    }
    return false;
}
bool estUnSeparateur(){
    nouvLigne = false;
    switch (caractere_courant){
        case ' ':
            return true;
        case '\n':
            //it's a new line let's mark it it'll come in handy for the parser
            nouvLigne = true;
            return true;
        case '\r':
            return true;
        case '\t':
            return true;
        default:
            return false;
    }
}
bool estLeEOF(){
    if (caractere_courant == EOF) return true;
    else return false;
}

void lireMot(){
    do{
        ajouterCaractereAuMot();
        lire_caractere_suivant();
    }while(estUnCaractere() || estUnChiffre());
}
void lireChiffre(){
    do{
        ajouterCaractereAuMot();
        lire_caractere_suivant();
    }while(estUnChiffre());
}
void LireSpecial(){
    do{
        ajouterCaractereAuMot();
        lire_caractere_suivant();
    }while(estSpecial());
}
void lireSeperateur(){
    do{
        if (nouvLigne == true){
            ajouterCaractereAuMot();
        }
        lire_caractere_suivant();
    }while(estUnSeparateur());
}
void LireErreur(){
    printf("Error \n");
    lire_caractere_suivant();

}

void lire_caractere_suivant(){
    caractere_courant =  fgetc(f);
}
bool ScannerLeMotSuivant(){
    //pisque il s'agit de l'analyseur syntaxique il faut faire appel a viderMot();
    viderMot();
    do{
        if (estUnChiffre()){
            lireChiffre();
        }else if (estUnCaractere()){
            lireMot();
        }else if (estSpecial()) {
            LireSpecial();
        }else if (estUnSeparateur()){
            lireSeperateur();
        }else if (estLeEOF()){
            return false;
        }else
            LireErreur();
    }while(dernierIndice == 0);
    return true;
}
void associerToken()
{
    if (strcmp(mot, "if") == 0) codeToken = IF_TOKEN;
    else if (strcmp(mot, "else") == 0) codeToken = ELSE_TOKEN;
    else if (strcmp(mot, "NA") == 0) codeToken = NA_TOKEN;
    else if (strcmp(mot, "while") == 0) codeToken = WHILE_TOKEN;
    else if (strcmp(mot, "repeat") == 0) codeToken = REPEAT_TOKEN;
    else if (strcmp(mot, "TRUE") == 0) codeToken = TRUE_TOKEN;
    else if (strcmp(mot, "FALSE") == 0) codeToken = FALSE_TOKEN;
    else if (strcmp(mot, "library") == 0) codeToken = LIBRARY_TOKEN;
    else if (strcmp(mot, "for") == 0) codeToken = FOR_TOKEN;
    else if (strcmp(mot, "break") == 0) codeToken = BREAK_TOKEN;
    else if (strcmp(mot, "return") == 0) codeToken = RETURN_TOKEN;
    else if (strcmp(mot, "function") == 0) codeToken = FUNCTION_TOKEN;
    else if (strcmp(mot, "print") == 0) codeToken = PRINT_TOKEN;
    else if (strcmp(mot, ".") == 0) codeToken = PT_TOKEN;
    else if (strcmp(mot, ",") == 0) codeToken = VIR_TOKEN;
    else if (strcmp(mot, "+") == 0) codeToken = PLUS_TOKEN;
    else if (strcmp(mot, "-") == 0) codeToken = MOINS_TOKEN;
    else if (strcmp(mot, "*") == 0) codeToken = MULT_TOKEN;
    else if (strcmp(mot, "<-") == 0) codeToken = AFF_ND_TOKEN;
    else if (strcmp(mot, "->") == 0) codeToken = AFF_TD_TOKEN;
    else if (strcmp(mot, "=") == 0) codeToken = AFF_FT_TOKEN;
    else if (strcmp(mot, "(") == 0) codeToken = PO_TOKEN;
    else if (strcmp(mot, ")") == 0) codeToken = PF_TOKEN;
    else if (strcmp(mot, "[") == 0) codeToken = ACCO_TOKEN;
    else if (strcmp(mot, "]") == 0) codeToken = ACCF_TOKEN;
    else if (strcmp(mot, "#") == 0) codeToken = COM_TOKEN;
    else if (strcmp(mot, "!=") == 0) codeToken = DIFF_TOKEN;
    else if (strcmp(mot, "\n") == 0) codeToken = NEWLINE_TOKEN;
    else if (strcmp(mot, "\t") == 0) codeToken = TAB_TOKEN;
    else if (strcmp(mot, "\\") == 0) codeToken = BACKSLA_TOKEN;
    else if (strcmp(mot, "<=") == 0) codeToken = INFEG_TOKEN;
    else if (strcmp(mot, ">=") == 0) codeToken = SUPEG_TOKEN;
    else if (strcmp(mot, "<") == 0) codeToken = INF_TOKEN;
    else if (strcmp(mot, ">") == 0) codeToken = SUP_TOKEN;
    else if (strcmp(mot, "==") == 0) codeToken = EQUAL_TOKEN;
    else if (strcmp(mot, "/") == 0) codeToken = DIV_TOKEN;
    else if (strcmp(mot, "||") == 0) codeToken = LOGOR_TOKEN;
    else if (strcmp(mot, "&&") == 0) codeToken = LOGAND_TOKEN;
    else if (strcmp(mot, "&") == 0) codeToken = ELWAND_TOKEN;
    else if (strcmp(mot, "|") == 0) codeToken = ELWOR_TOKEN;
    else if (strcmp(mot, "!") == 0) codeToken = LOGNOT_TOKEN;
    else if (strcmp(mot, "{") == 0) codeToken = CURO_TOKEN;
    else if (strcmp(mot, "}") == 0) codeToken = CURF_TOKEN;
    else if (leMotEstUnNombre()) codeToken = NUM_TOKEN;
    else codeToken = ID_TOKEN;
}

//useful functions
void ajouterCaractereAuMot(){
    mot[dernierIndice++] = caractere_courant;
    mot[dernierIndice] = '\0';
}
void viderMot(){
    dernierIndice = 0;
    mot[dernierIndice] = '\0';
}
bool leMotEstUnNombre(){
    if (mot[0] >= '0' && mot[0] <= '9'){
        return true;
    } else return false;
}
