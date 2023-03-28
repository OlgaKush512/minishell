
  __  __ ___ _   _ ___ ____  _   _ _____ _     _     
 |  \/  |_ _| \ | |_ _/ ___|| | | | ____| |   | |    
 | |\/| || ||  \| || |\___ \| |_| |  _| | |   | |    
 | |  | || || |\  || | ___) |  _  | |___| |___| |___ 
 |_|  |_|___|_| \_|___|____/|_| |_|_____|_____|_____|
                                                     


============================================================================================================================
LIST TOKEN

COMMANDE -> echo wc ls cat exit etc
FLAG -> -a -la -n etc
ARG -> "test" test nom de fichier/doc etc
SYMBOLE ->   < >> > << | $ 
QUOTE ->    ' " peut-etre juste un sy`mbole
============================================================================================================================
PIPE

chaque pipe demande forcement un appel a fork preuve avec exit | exit qui exit 2 subprocess
============================================================================================================================
PARSING

quote a gerer au debut car il empeche l'interpretation
si ' tant que pas ' on avance naivement
pareil pour " sauf $ (fonction pour expand existe deja)
check si la ligne est vide ou remplie d'espace par exemple et la skip directement (evite des problemes :D)

idee: transformer l'input avec des quotes en un input sans quote (avec ce que ca implique) puis le lexer?

idee: peut-etre separe les commandes selon builtin ou binaire? je pense pas qu'il y ai besoin mais je sais pas
============================================================================================================================
REDIRECTION

apres < > >> il faut un nom de fichier, si on fait un tableau de fd pour infile et un pour outfile il faut trouver un moyen d'indiquer si l'outfile est > ou >>
en fait je pense qu'il faut faire une petite liste chaine qui contient le chemin et si c'est infile/outfile/outfile append (>>) car il faut qu'on sache dans quel ordre sont ecrits les < > >>

quand on rencontre < il faudra pipe le fd du fichier et remplacer l'entree de la commande
quand > >> il faut pipe le fd du fichier (ouvert en append ou write) et remplacer la sortie de la commande
et tous les combos de < > >> > < > qui vont avec
toujours lire de gauche a droite

le premier token peut seulement etre une commande ou < > << >> puis fichier et on recommence
pour << ecrire dans un fichier temporaire qu'on supprime je pense? mais comment choisir le nom? car pb si il existe deja

============================================================================================================================
BUILTIN

lire pour connaitre exactement tous les comportements des builtin car on les recode nous meme

======
ECHO seul flag -n
http://pwet.fr/man/linux/commandes/posix/echo/

syscall de write je suppose mais pas trouve
display simplement la string, enleve les espaces en trop entre les arguements (fait dans le parsing je pense)
renvoie 0 si ca a fonctionne
sinon retour > 0

======
EXIT
http://pwet.fr/man/linux/commandes/posix/exit/

exit affiche exit puis exit
peut prendre un argument : la valeur de retour qu'on renvoie en sortant -> $? une fois sortie de minishell 

exit sans argument exit minishell et renvoie la valeur de retour de la derniere commande -> $? dans minishell
si aucune commande renvoie 0

(valeur est un nombre cast en (unsigned char)) si pas nombre exit quand meme et retourne 2, pourquoi 2?


======
ENV

ne peut prendre ni argument ni flags -> on les ignore
affiche toutes les variables d'environnement sans tri

renvoie 0 si fonctionne sinon return > 0


======
EXPORT
http://pwet.fr/man/linux/commandes/posix/export/


avec export [name[=value]]
name
A word consisting solely of letters, numbers, and underscores, and beginning with a letter or underscore. Names are used as shell variable and function names. Also referred to as an identifier.
word
A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.

======
UNSET
http://pwet.fr/man/linux/commandes/posix/unset/


======
CD 
http://pwet.fr/man/linux/commandes/posix/cd/

sans arg doit regarder la variable HOME et cd ici, si HOME unset undef behavior
doit changer le dossier en fonction de l'arg et update la variable PWD manuellement je crois?
utiliser chdir() pour changer le dir, voir relative ET absolute path

renvoie 0 si fonctionne sinon return > 0
si erreur il faut rester dans le directory de base et return > 0

======
PWD
http://pwet.fr/man/linux/commandes/posix/pwd/

ecrire le path absolu du working directory puis \n 
utiliser getcwd() et pas la var PWD

renvoie 0 si fonctionne sinon return > 0


