/******************************************************************************\
fichier : Classe_Liste.h

Permet de gerer une liste de pointeurs generiques.

\******************************************************************************/


#ifndef CLASSE_LISTE_H
#define CLASSE_LISTE_H

/* Inclusion des bibliotheques standard du C */
#include <stdint.h> /* uint32_t */

#ifndef CLASSE_LISTE_C
    typedef void* Classe_Liste;
#endif

typedef void (*t_fct_classe_lst)(void*);
typedef int (*t_fct_classe_lst_comp)(void*,void*);

/******************************************************************************/
/* LISTE_Creer
Description :
    Constructeur
Parametres :
    aucun
Retour :
    liste
*/
Classe_Liste LISTE_Creer( void );

/******************************************************************************/
/* LISTE_Detruire
Description :
    Destructeur de liste
    Ne detruit les elements organises par la liste
Parametres :
    pointeur sur la liste a detruire
Retour :
    aucun
*/
void LISTE_Detruire( Classe_Liste* p_liste );

/******************************************************************************/
/* LISTE_Lire_Taille
Description :
    Retourne le nombre d'elements de la liste.
Parametres :
    liste
Retour :
    nombre d'elements de la liste
*/
uint32_t LISTE_Lire_Taille( Classe_Liste liste );

/******************************************************************************/
/* LISTE_Ajouter_Elmt_Debut
Description :
    Ajoute un element au debut de la liste.
Parametres :
    liste
    'element' : pointeur sur l'element a ajouter en tete de liste
Retour :
    aucun
*/
void LISTE_Ajouter_Elmt_Debut( Classe_Liste liste, void* element );

/******************************************************************************/
/* LISTE_Ajouter_Elmt_Fin
Description :
    Ajoute un element a la fin de la liste.
Parametres :
    liste
    'element' : pointeur sur l'element a ajouter a la fin de liste
Retour :
    aucun
*/
void LISTE_Ajouter_Elmt_Fin( Classe_Liste liste, void* element );

/******************************************************************************/
/* LISTE_Ajouter_Elmt
Description :
    Ajoute un element avant l'element courant de la liste.
Parametres :
    liste
    element
        pointeur sur l'element a ajouter
Retour :
    aucun
*/
void LISTE_Ajouter_Elmt( Classe_Liste liste, void* element );

/******************************************************************************/
/* LISTE_Inserer_En_Triant
Description :
    Insere un element dans 'liste' de facon a ce que les elements de la liste
    soient ordonnees selon une regle donnee par 'fonction'.
Parametres :
    liste
    'element' : pointeur sur l'element a inserer dans la liste
Retour :
    aucun
*/
void LISTE_Inserer_En_Triant( Classe_Liste liste, void* element,
                              t_fct_classe_lst_comp fonction );

/******************************************************************************/
/* LISTE_Lire_Premier_Elmt
Description :
    Positionne l'element courant de la liste sur le premier element.
    Retourne un pointeur sur le premier element.
Parametres :
    liste
Retour :
    pointeur sur le premier element de la liste
*/
void* LISTE_Lire_Premier_Elmt( Classe_Liste liste );

/******************************************************************************/
/* LISTE_Lire_Dernier_Elmt
Description :
    Positionne l'element courant de la liste sur le dernier element.
    Retourne un pointeur sur le dernier element de la liste.
Parametres :
    liste
Retour :
    pointeur sur le dernier element de la liste
*/
void* LISTE_Lire_Dernier_Elmt( Classe_Liste liste );

/******************************************************************************/
/* LISTE_Lire_Elmt_Suivant
Description :
    Deplace l'element courant de la liste sur l'element suivant.
    Retourne un pointeur sur le (nouvel) element courant.
    Si l'element courant est le dernier, retourne NULL (et l'element courant
    demeure le dernier).
Parametres :
    liste
Retour :
    Pointeur sur le (nouvel) element courant.
*/
void* LISTE_Lire_Elmt_Suivant( Classe_Liste liste );

/******************************************************************************/
/* LISTE_Lire_Elmt_Precedant
Description :
    Deplace l'element courant de la liste sur l'element precedant.
    Retourne un pointeur sur le (nouvel) element courant.
    Si l'element courant est le premier, retourne NULL (et l'element courant
    demeure le premier).
Parametres :
    liste
Retour :
    Pointeur sur le (nouvel) element courant.
*/
void* LISTE_Lire_Elmt_Precedant( Classe_Liste liste );

/******************************************************************************/
/* LISTE_Lire_Elmt_Par_Index
Description :
    Retourne un pointeur sur l''index'ieme element de la liste.
    Deplace l'element courant sur l''index'ieme element de la liste.
    Si 'index' est plus grand que le nombre d'element de la liste, retourne NULL
    et ne deplace pas l'element courant.
Parametres :
    liste
    'index' : position de l'element dans la liste
Retour :
    pointeur sur l''index'ieme element de la liste
*/
void* LISTE_Lire_Elmt_Par_Index( Classe_Liste liste, uint32_t index );

/******************************************************************************/
/* LISTE_Retirer_Premier_Elmt
Description :
    Retire le premier element de la liste.
    Retourne un pointeur sur l'element retire de la liste.
Parametres :
    liste
Retour :
    pointeur sur l'element retire de la liste
*/
void* LISTE_Retirer_Premier_Elmt( Classe_Liste liste );

/******************************************************************************/
/* LISTE_Retirer_Elmt_Courant
Description :
    Retire l'element courant de la liste.
    Retourne un pointeur sur l'element retire de la liste.
Parametres :
    liste
Retour :
    pointeur sur l'element retire de la liste
*/
void* LISTE_Retirer_Elmt_Courant( Classe_Liste liste );

/******************************************************************************/
/* LISTE_Retirer_Dernier_Elmt
Description :
    Retire le dernier element de la liste.
    Retourne un pointeur sur l'element retire de la liste.
Parametres :
    liste
Retour :
    pointeur sur l'element retire de la liste
*/
void* LISTE_Retirer_Dernier_Elmt( Classe_Liste liste );

/******************************************************************************/
/* LISTE_Appliquer_A_Tous
Description :
    Applique une procedure specifique a tous les elements de la liste.
Parametres :
    liste
    'fonction' :  pointeur sur la procedure a apliquer
Retour :
    aucun
*/
void LISTE_Appliquer_A_Tous( Classe_Liste liste, t_fct_classe_lst fonction );

/******************************************************************************/
/* LISTE_Trier
Description :
Parametres :
    liste
    fonction
        fonction de comparaison des elements
Retour :
    aucun
*/
void LISTE_Trier( Classe_Liste liste, t_fct_classe_lst_comp fonction );

#endif
