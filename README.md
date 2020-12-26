A compiler for a subset of R programming language

1- Scanner (analyseur_lexical.c)

2- Parser  (analyseur_syntaxique.c)

3- Semantic (also in analyseur_syntaxique.c)

---------------------------------------------------------Grammaire:

	Soit G = < T, NT, program, P > notre grammaire.

----L’ensemble des symboles terminaux :
T = 	{ id | "{" | "}" | "=" | "<-" | num | "+" | "-" | "function" | "(" | ")" | "," | ” | "return" |
	"print" | "NA" | "TRUE" | "FALSE" | "library" | "if" | "BREAK" | "else" | "while" |
	"repeat" | "for" | "in" | ":"  | "==" | "!=" | "!" }


----L’ensemble des symboles non-terminaux :
NT=	{program , single_input ,simple_stmt , compound_stmt , assign_stmt ,
	lib_stmt , print_stmt , exp_prime , aff , numeric_term , function_call ,
	fact , function_stmt , function_body_stmt , return_stmt , other_term , if_stmt,
	repeat_stmt ,while_stmt , for_stmt , condition_stmt , if_body , else_stmt ,
	loop_body }

----L’axiome : program

L’ensemble des règles de réécriture :
P = {
	program 		: := single_input {” {single_input|’break’}}*
	
	single_input 		: := simple_stmt 
				| compound_stmt
	
	simple_stmt 		: := assign_stmt
				| lib_stmt
				| print_stmt
	
	assign_stmt 		: := id {exp_prime}
	
	exp_prime 		: := [= |<-] aff
	
	aff 			: := id {numeric_term | function_call |ex_prime} |num {numeric_term}
				| function_stmt
				| other_term

	numeric_term 		: := [+|-] term { [ + | - ] term }*
	
	term 			: := fact { [ * | / ] fact}*
	
	fact 			: := id
				| num
				| ’(’ numeric_term ’)’

	function_stmt 		: := ’function’ ’(’ id , id * ’)’ function_body_stmt
	
	function_body_stmt 	:= ’{’ {}* [single_input| return_stmt] {” {single_input | return_stmt }}* ’}’ 
				| simple_stmt 
				| return_stmt

	return_stmt 		: := ’return’ ’(’ id ’)’
	
	print_stmt 		: := ’print’ ’(’[id nmueric_term | numeric_term]’)’
	
	function_call 		: := ’(’ id {, id}* ’)’
	
	other_term 		: := NA
				| TRUE
				| FALSE

	lib_stmt 		: := ’library’ ’(’ id ’)’

	compound_stmt 		: := if_stmt | repeat_stmt | while_stmt | for_stmt

	if_stmt 		: := ’if’ ’(’ condition_stmt ’)’ if_body
	
	if_body 		: := ’{’ {}* program ’}’ {else_stmt}
				|simple_stmt {else_stmt}
				| BREAK {else_stmt}

	else_stmt 		: := else [ ’{’ {}* program ’}’ | {if_stmt} | simple_stmt | BREAK ]

	while_stmt 		: := ’while’ ’(’ condition_stmt ’)’ loop_body

	loop_body 		: := ’{’ {}* program ’}’
				| simple_stmt
				| BREAK

	repeat_stmt 		: := ’repeat’ loop_body
	
	for_stmt 		: := ’for’ ’(’ id ’in’ [id|num] { :[id|num]} ’)’ loop_body
	
	condition_stmt 		: := [id|num] { [== | !=] [id|num]} {[&&| ||] conditon_stmt} || ’ !’ [id|num] [&&| ||] conditon_stmt}

}


---------------------------------------------------------Règles sémantiques:
- Toutes les variables à utiliser doivent avoir une valeur.
- Tous les termes numériques doivent utiliser seulement Numeric Class.
- Toutes les fonctions à appeler doivent être référenciées à une fonction déjà existante et avec un exact nombre d’arguments.
- BREAK doit être dans une boucle.