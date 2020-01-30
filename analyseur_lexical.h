//
// Created by  Oussama Siyagh on 29/01/2020.
//

#ifndef UNTITLED1_ANALYSEUR_LEXICAL_H
#define UNTITLED1_ANALYSEUR_LEXICAL_H

#include "main.h"

bool ScannerLeMotSuivant();
void lire_caractere_suivant();
void associerToken();
void ajouterCaractereAuMot();
void viderMot();
bool leMotEstUnNombre();

bool estUnChiffre();
bool estUnCaractere();
bool estSpecial();
bool estUnSeparateur();

void lireChiffre();
void lireMot();
void LireSpecial();
void lireSeperateur();
void LireErreur();

#endif //UNTITLED1_ANALYSEUR_LEXICAL_H
