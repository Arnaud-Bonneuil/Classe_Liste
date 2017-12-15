/******************************************************************************\
fichier : Classe_Liste.c
\******************************************************************************/

/* Inclusion des bibliotheques standard du C */
#include <stdlib.h> /* malloc */
#include <string.h> /* memset */
#include <stdint.h> /* uint32_t */



/******************************************************************************/
/* Definition des types prives */
/******************************************************************************/
typedef struct t_elmt_lst
{
    void* ptr_donnee;
    struct t_elmt_lst* precedant;
    struct t_elmt_lst* suivant;
} t_elmt_lst, *t_ptr_elmt_lst;
/******************************************************************************/



/******************************************************************************/
/* Definition des attributs de la classe */
/******************************************************************************/
#define NB_MAXIMUM_ELEMENTS 0xFFFFFFFF
typedef struct classe_liste
{
    t_ptr_elmt_lst premier;
    t_ptr_elmt_lst dernier;
    t_ptr_elmt_lst courant;
    uint32_t nb_elements;
} classe_liste, *Classe_Liste;
/******************************************************************************/

#define CLASSE_LISTE_C
#include "Classe_Liste.h"
#undef CLASSE_LISTE_C



/******************************************************************************/
/* Declaration des fonctions privees */
/******************************************************************************/
static t_ptr_elmt_lst Allouer_Elmt( void );
/******************************************************************************/



/******************************************************************************/
/* Definition des methodes publiques */
/******************************************************************************/
Classe_Liste LISTE_Creer( void )
{
    Classe_Liste liste; /* liste nouvellement cree */

    liste = (Classe_Liste) malloc( sizeof( classe_liste ) );
    if( liste != NULL )
    {
        memset( liste, 0, sizeof( classe_liste ) );
        liste->premier = NULL;
        liste->dernier = NULL;
        liste->courant = NULL;
        liste->nb_elements = 0;
    }
    return liste;
}
/******************************************************************************/
void LISTE_Detruire( Classe_Liste* p_liste )
{
    t_ptr_elmt_lst ptr_elmt_courant;
    t_ptr_elmt_lst ptr_elmt_a_detruire;
    if( p_liste != NULL )
    {
        if( *p_liste != NULL )
        {
            /* Detruire tous les elements de la liste */
            ptr_elmt_courant = (*p_liste)->premier;
            while( ptr_elmt_courant != NULL )
            {
                /* Enregistrer l'element a detruire */
                ptr_elmt_a_detruire = ptr_elmt_courant;

                /* Acquerir l'element suivant */
                ptr_elmt_courant = ptr_elmt_courant->suivant;

                /* Detruire l'element */
                ptr_elmt_a_detruire->precedant = NULL;
                ptr_elmt_a_detruire->suivant = NULL;
                ptr_elmt_a_detruire->ptr_donnee = NULL;
                free( ptr_elmt_a_detruire );
                ptr_elmt_a_detruire = NULL;
            }

            /* Detruire la liste */
            free( *p_liste );
            *p_liste = NULL;
        }
        else
        {
            /* rien a faire si liste est NULL */
        }
    }
}
/******************************************************************************/
uint32_t LISTE_Lire_Taille( Classe_Liste liste )
{
    uint32_t taille = 0;

    if( liste != NULL )
    {
        taille = liste->nb_elements;
    }
    return taille;
}
/******************************************************************************/
void LISTE_Ajouter_Elmt_Debut( Classe_Liste liste, void* element )
{
    t_ptr_elmt_lst nouvel_element = NULL;

    if( liste != NULL && element!=NULL )
    {
        if( liste->nb_elements < NB_MAXIMUM_ELEMENTS )
        {
            /* Creer un nouvel element de liste */
            nouvel_element = Allouer_Elmt();
            if( nouvel_element != NULL )
            {
                nouvel_element->ptr_donnee = element;

                nouvel_element->precedant = NULL;
                if( liste->premier==NULL ) /* liste vide */
                {
                    nouvel_element->suivant = NULL;
                    liste->premier = nouvel_element;
                    liste->dernier = nouvel_element;
                    liste->courant = nouvel_element;
                }
                else /* liste non vide */
                {
                    /* premier devient second */
                    nouvel_element->suivant = liste->premier;
                    liste->premier->precedant = nouvel_element;
                    /* mettre à jour premier et courant */
                    liste->premier = nouvel_element;
                    liste->courant = nouvel_element;
                }
                (liste->nb_elements)++;
            }
        }
    }
}
/******************************************************************************/
void LISTE_Ajouter_Elmt_Fin( Classe_Liste liste, void* element )
{
    t_ptr_elmt_lst nouvel_element = NULL;

    if( liste != NULL && element != NULL )
    {
        if( liste->nb_elements < NB_MAXIMUM_ELEMENTS )
        {
            nouvel_element = Allouer_Elmt();
            if( nouvel_element != NULL )
            {
                nouvel_element->ptr_donnee = element;

                nouvel_element->suivant = NULL;
                if( liste->premier == NULL ) /* liste vide */
                {
                    nouvel_element->precedant = NULL;
                    liste->premier = nouvel_element;
                    liste->dernier = nouvel_element;
                    liste->courant = nouvel_element;
                }
                else /* liste non vide */
                {
                    /* dernier devient avant-dernier */
                    nouvel_element->precedant = liste->dernier;
                    liste->dernier->suivant = nouvel_element;
                    /* mettre a jour dernier et courant */
                    liste->dernier = nouvel_element;
                    liste->courant = nouvel_element;
                }
                (liste->nb_elements)++;
            }
        }
    }
}
/******************************************************************************/
void LISTE_Ajouter_Elmt( Classe_Liste liste, void* element  )
{
    t_ptr_elmt_lst nouvel_element = NULL;

    if( liste!=NULL && element!=NULL )
    {
        if( liste->courant==liste->premier )
        {
            LISTE_Ajouter_Elmt_Debut( liste, element );
        }
        else
        {
            /* Creer le nouvel element a inserer */
            nouvel_element = Allouer_Elmt();
            if( nouvel_element != NULL )
            {
                nouvel_element->ptr_donnee = element;

                /* Inserer l'element */
                nouvel_element->precedant = liste->courant->precedant;
                liste->courant->precedant->suivant = nouvel_element;
                liste->courant->precedant = nouvel_element;
                nouvel_element->suivant = liste->courant;

                liste->courant = nouvel_element;
            }
        }
    }
}
/******************************************************************************/
void LISTE_Inserer_En_Triant( Classe_Liste liste, void* element,
                              t_fct_classe_lst_comp fonction )
{
    void* element_teste = NULL;
    int insere = 0;

    if( liste!=NULL && element != NULL && fonction != NULL )
    {
        if( liste->courant==NULL )
        {
            /* la liste est vide */
            /* Ajouter l'element */
            LISTE_Ajouter_Elmt_Debut( liste, element );
        }
        else
        {
            /* Selectionner le premier element de la liste */
            element_teste = LISTE_Lire_Premier_Elmt( liste );
            while( insere==0 && element_teste!=NULL )
            {
                if( fonction( element, element_teste) )
                {
                    /* element prend la place de element_teste */
                    LISTE_Ajouter_Elmt( liste, element );
                    insere = 1;
                }
                else
                {
                    element_teste = LISTE_Lire_Elmt_Suivant( liste );
                }
            }
            /* Si toute la liste est parcourue mais que element n'a pas pu etre
            insere */
            if( insere==0 )
            {
                /* Ajouter l'element en fin de liste */
                LISTE_Ajouter_Elmt_Fin( liste, element );
            }
        }
    }
}
/******************************************************************************/
void* LISTE_Lire_Premier_Elmt( Classe_Liste liste )
{
    if( liste!=NULL && liste->courant!=NULL )
    {
        liste->courant = liste->premier;
        return liste->premier->ptr_donnee;
    }
    else
    {
        return NULL; /* liste = NULL ou liste vide */
    }
}
/******************************************************************************/
void* LISTE_Lire_Dernier_Elmt( Classe_Liste liste )
{
    if( liste!=NULL && liste->courant!=NULL )
    {
        liste->courant = liste->dernier;
        return liste->dernier->ptr_donnee;
    }
    else
    {
        return NULL; /* liste = NULL ou liste vide */
    }
}
/******************************************************************************/
void* LISTE_Lire_Elmt_Suivant( Classe_Liste liste )
{
    void* element = NULL;

    if( liste==NULL )
    {
        /* liste = NULL, retourner NULL */
    }
    else
    {
        if( liste->courant==NULL )
        {
            /* liste vide, retourner NULL */
        }
        else
        {
            if( liste->courant->suivant==NULL )
            {
                /* fin de la liste atteinte : retourner NULL */
            }
            else
            {
                liste->courant = liste->courant->suivant;
                element = liste->courant->ptr_donnee;
            }
        }
    }
    return element;
}
/******************************************************************************/
void* LISTE_Lire_Elmt_Precedant( Classe_Liste liste )
{
    void* element = NULL;

    if( liste==NULL )
    {
        /* liste = NULL, retourner NULL */
    }
    else
    {
        if( liste->courant==NULL )
        {
            /* liste vide, retourner NULL */
        }
        else
        {
            if( liste->courant->precedant==NULL )
            {
                /* debut de la liste atteinte : retourner NULL */
            }
            else
            {
                liste->courant = liste->courant->precedant;
                element = liste->courant->ptr_donnee;
            }
        }
    }
    return element;
}
/******************************************************************************/
void* LISTE_Lire_Elmt_Par_Index( Classe_Liste liste, uint32_t index )
{
    void* ptr_donnee = NULL;
    uint32_t compteur;

    if( index<=liste->nb_elements )
    {
        ptr_donnee = LISTE_Lire_Premier_Elmt( liste );
        for( compteur=1; compteur<index ; compteur++ )
        {
            ptr_donnee = LISTE_Lire_Elmt_Suivant( liste );
        }
    }
    return ptr_donnee;
}
/******************************************************************************/
void* LISTE_Retirer_Premier_Elmt( Classe_Liste liste )
{
    t_ptr_elmt_lst ptr_elmt_a_detruire;
    void* ptr_donnee = NULL;

    if( liste!=NULL && liste->premier!=NULL )
    {
        /* Enregistrer l'element a detruire */
        ptr_elmt_a_detruire = liste->premier;
        ptr_donnee = ptr_elmt_a_detruire->ptr_donnee;

        /* Le nouveau premier est l'ancien second */
        liste->premier = liste->premier->suivant;
        if( liste->premier!=NULL ) /* si la liste avait plus d'un element */
        {
            liste->premier->precedant = NULL;
        }

        /* Gerer element courant */
        if( liste->courant==ptr_elmt_a_detruire )
        {
            /* le precedant courant etait premier, positionner le nouveau
            courant sur le nouveau premier */
            liste->courant = liste->premier;
        }

        /* Detruire l'element */
        ptr_elmt_a_detruire->precedant = NULL;
        ptr_elmt_a_detruire->suivant = NULL;
        ptr_elmt_a_detruire->ptr_donnee = NULL;
        free( ptr_elmt_a_detruire );

        liste->nb_elements--;
    }
    return ptr_donnee;
}
/******************************************************************************/
void* LISTE_Retirer_Elmt_Courant( Classe_Liste liste )
{
    t_ptr_elmt_lst ptr_elmt_a_detruire;
    void* ptr_donnee = NULL;

    if( liste!=NULL && liste->courant!=NULL )
    {
        /* Enregistrer l'element a detruire  */
        ptr_elmt_a_detruire = liste->courant;
        ptr_donnee = ptr_elmt_a_detruire->ptr_donnee;

        if( ptr_elmt_a_detruire==liste->premier )
        {
            /* Retirer le premier element */
            /* Le precedent second devient le premier */
            liste->premier = liste->premier->suivant;
            if( liste->premier!=NULL )
            {
                /* si la liste avait plus d'un element */
                liste->premier->precedant = NULL;
            }
            /* Mettre a jour courant */
            liste->courant = liste->premier;
        }
        else if( ptr_elmt_a_detruire==liste->dernier )
        {
            /* Retirer le dernier element */
            /* Le precedant avant-dernier devient le dernier */
            liste->dernier = liste->dernier->precedant;
            if( liste->dernier!=NULL )
            {
                /* si la liste avait plus d'un element */
                liste->dernier->suivant = NULL;
            }
            /* Mettre a jour courant */
            liste->courant = liste->dernier;
        }
        else /* Retirer tout autre element */
        {
            /* Modifier les liens */
            ptr_elmt_a_detruire->precedant->suivant =
                ptr_elmt_a_detruire->suivant;
            ptr_elmt_a_detruire->suivant->precedant =
                ptr_elmt_a_detruire->precedant;
            /* Mettre a jour courant */
            liste->courant = ptr_elmt_a_detruire->precedant;
        }

        /* Destruire l'element */
        ptr_elmt_a_detruire->precedant = NULL;
        ptr_elmt_a_detruire->suivant = NULL;
        ptr_elmt_a_detruire->ptr_donnee = NULL;
        free( ptr_elmt_a_detruire );

        liste->nb_elements--;
    }
    return ptr_donnee;
}
/******************************************************************************/
void* LISTE_Retirer_Dernier_Elmt( Classe_Liste liste )
{
    t_ptr_elmt_lst ptr_elmt_a_detruire;
    void* ptr_donnee = NULL;

    if( liste!=NULL && liste->dernier!=NULL )
    {
        /* Enregistrer l'element a detruire */
        ptr_elmt_a_detruire = liste->dernier;
        ptr_donnee = ptr_elmt_a_detruire->ptr_donnee;

        /* Le nouveau dernier est l'ancien avant-dernier */
        liste->dernier = liste->dernier->precedant;
        if( liste->dernier!=NULL ) /* si la liste avait plus d'un element */
        {
            liste->dernier->suivant = NULL;
        }

        /* Gerer element courant */
        if( liste->courant==ptr_elmt_a_detruire )
        {
            /* le precedant courant etait dernier, positionner le nouveau
            courant sur le nouveau dernier */
            liste->courant = liste->dernier;
        }

        /* Detruire l'element */
        ptr_elmt_a_detruire->precedant = NULL;
        ptr_elmt_a_detruire->suivant = NULL;
        ptr_elmt_a_detruire->ptr_donnee = NULL;
        free( ptr_elmt_a_detruire );

        liste->nb_elements--;
    }
    return ptr_donnee;
}
/******************************************************************************/
void LISTE_Appliquer_A_Tous( Classe_Liste liste, t_fct_classe_lst fonction )
{
    t_ptr_elmt_lst ptr_elmt_courant;

    if( liste != NULL )
    {
        if( fonction != NULL )
        {
            ptr_elmt_courant = liste->premier;
            while( ptr_elmt_courant != NULL )
            {
                fonction( ptr_elmt_courant->ptr_donnee );
                ptr_elmt_courant = ptr_elmt_courant->suivant;
            }
        }
    }
}
/******************************************************************************/
void LISTE_Trier( Classe_Liste liste, t_fct_classe_lst_comp fonction )
{
    Classe_Liste liste_triee = NULL;
    t_ptr_elmt_lst tampon = NULL;
    void* ptr_donnee = NULL;

    if( liste != NULL && liste->courant!=NULL && fonction!=NULL )
    {
        if( LISTE_Lire_Taille( liste ) >= 2 )
        {
            /* Creer une nouvelle liste */
            liste_triee = LISTE_Creer();

            /* Ajouter le premier element de liste */
            ptr_donnee = LISTE_Lire_Premier_Elmt( liste );
            LISTE_Ajouter_Elmt_Debut( liste_triee, ptr_donnee );

            /* Traiter tous les elements de la liste */
            ptr_donnee = LISTE_Lire_Elmt_Suivant( liste );
            while( ptr_donnee!=NULL )
            {
                LISTE_Inserer_En_Triant( liste_triee, ptr_donnee, fonction );
                ptr_donnee = LISTE_Lire_Elmt_Suivant( liste );
            }

            /* Echanger la liste originale et la liste triee */
            tampon = liste_triee->premier;
            liste_triee->premier = liste->premier;
            liste->premier = tampon;
            tampon = liste_triee->dernier;
            liste_triee->dernier = liste->dernier;
            liste->dernier = tampon;
            liste->courant = liste->premier;

            /* Supprimmer la liste "originale" */
            LISTE_Detruire( &liste_triee );
        }
    }
}
/******************************************************************************/


/******************************************************************************/
/* Definition des fonctions privees */
/******************************************************************************/
static t_ptr_elmt_lst Allouer_Elmt(void)
{
    t_ptr_elmt_lst nouvel_element;
    nouvel_element = (t_ptr_elmt_lst)malloc(sizeof(t_elmt_lst));
    return nouvel_element;
}
/******************************************************************************/
