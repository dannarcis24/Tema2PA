# CERINTA:
Simularea unui turneu sportiv pe echipe, bazat pe 2cerinte (task 1, 2). Pentru a putea rula programul este necesara introducerea a 3a fisiere, toate fiind date ca date de intrare din terminal (un fisier de intrare ".in" si 2fisiere de iesire ".out").                                       
>Primul fisier: contine informatii despre echipele participante                                 
>Al doilea fisier: rezultatul primei cerinte                                                  
>Al treilea fisier: rezultatul celei de a doua cerinta                                       

# PRINCIPALELE STRUCTURI UTILIZATE:

typedef struct{                            
char *nume_echipa;                      
float punctaj;                           
unsigned int pozitie;                                             
} Team;       

In concurs sunt inscrise mai multe echipe, despre fiecare se stiu punctajul si numele echipei, dar este necesara retinerea pozitiei din fisier (pozitie-1, numaratoarea trebuie sa inceapa de la 0).

# FUNCTIA MAIN:
Se verifica daca datele de intrare (cele 3fisiere) sunt introduse corespunzator.
>Primul fisier: ".in"                                     
>Al doilea fisier: "Graf", ".out"                                      
>Al treilea fisier: "Scor", ".out"
                 
Se fac initializarile necesare, iar la final se dezaloca memoria pentru toate structurile utilizate pe parcurs.

# BIBLIOTECI:
><stdio.h>, <stdlib.h>, <string.h> incluse in "structs.h>, care este inclus in "tasks.h", fiind inclus in main; in felul acesta nu este intalnita problema duplicarii functiilor, deci nu este necesar sa folosim pragma once
1. "tasks.h": toate apelurile folosite pentru rezolvarea cerintelor (biblioteca principala, cea inclusa in main)
2. "structs.h": toate apelurile pentru utilizarea structurilor (liste, cozi) si declararile apelurilor (biblioteca initiala, fiind inclusa in "tasks.h")

# TASK 1
>Primul fisier este formatat astfel: pe fiecare linie se afla informatiile despre fiecare echipa, respectiv punctajul, fiind dat ca numar real cu 2zecimale (float) si numele echipei. De asemenea se cunoaste numarul de echipe participante, acesta fiind 32.
                                                                                  
Pentru rezolvarea primului task este necesara crearea unei matrici de adiacenta a turneului. Echipele se vor duela in mai multe meciuri (primele 2echipe, urmatoarele 2echipe...), iar fiecare meci este introdus in matricea de adiacenta, daca echipa1 de pe pozitia i si echipa de pe pozitia j au un meci, iar echipa de pe pozitia j castiga, atunci elementul de pe pozitia i si j (matrice[ix32+j] = 1), de retinut este faptul ca matricea este retinuta ca vector, pentru a nu se face alocarea fiecarei linii in parte, iar accesarea se face dupa formula: "i x numar_coloane + j", unde i si j sunt indexi ('x' - '*').
>Criteriul de alegere al echipei castigatoare este luat dupa punctaj, in cazul in care punctajele ambelor echipe sunt egale, atunci se vor ordona dupa nume (nume_echipa).

Este necesara introducere a 2structuri: o lista inlantuita (List), care primeste ca valoare void*, in modul acesta se poate introduce orice tip de element si o coada (Queue), care poate primi, la randul ei, orice tip de lista inlantuita. Astfel se evita problemele de scriere a mai multe structuri de acelasi tip, dar care contin valori distincte.

!! FUNCTIILE PENTRU CERINTA 1 -> matches.c                             
!! FUNCTIILE PENTRU LISTE INLANTUITE -> lists.c                                 
!! FUNCTIILE PENTRU COZI -> queue.c                                               

Se citesc datele din primul fisier (.in) si se introduc, pe rand, in lista, la final, astfel se poate retine si pastra ordinea echipelor din fisier.                                    
In timpul gestionarii meciurilor se folosesc 2cozi, una reprezinta castigatorii, iar celalata reprezinta pierzatorii. Initial sunt introduse toate echipele in prima coada (coada cu castigatori), urmand sa se dispute castigatorul in functie de criteriul de alegere, urmand ca echipa castigatoare sa se adauge inapoi in lista (in cadrul unui meci se adigura parcurgerea, astfel incat o echipa sa nu joace de mai multe ori), iar echipa, care a pierdut, este introdusa in coada pentru pierzatori, care este salvata si transmina in main. Dupa incheierea fiecarui meci se reincepe procesul, pana cand in coada de castigatori ramane o singura echipa, care este introdusa, de asemenea, in coada de pierzatori.

In final se face afisarea matricii de adiacenta a turneului in cel de al doilea fisier ("Graf", ".out").

# TASK 2
Pentru rezolvarea celui de al doilea task este necesara recalcularea punctajului echipei, folosind urmatoare formula: P = q x (2-q)^r/(2^l+(q-1) x (2-q)^l.                          
P - punctajul unei echipe                                        
q - ratie, care apartine [0, 1]                                                                                   
r - numarul de victorii obtinute                        >numarul de 1 pe coloana pozitiei corespunzatoare echipei                                                                       
l - numarul total de meciuri ale turneului                                                                      

In cazul de fata, avem q = 0.15 si l = 6 (log(32)+1 = 5+1 = 6), iar pentru a calcula numarul de victorii al unei echipe trebuie numarat numarul de aparitii al lui 1 (conform task 1) de pe coloana corespunzatoare pozitiei echipei (cea din fisier). 
Deci se va parcurge lista si modifica punctajele.

!! FUNCTIILE PENTRU CERINTA 2 -> score.c

In final, se face afisarea echipelor in ordine crescatoare a punctajelor, dar respectand ordinea, in care au fost eliminate din turneu, adica se vor afisa echipele retinute in coada de pierzatori, deoarece respecta regula si nu mai este necesara ordonarea listei inlantuite.
