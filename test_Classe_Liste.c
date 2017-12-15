/******************************************************************************\
fichier : test_Classe_Liste.c
\******************************************************************************/

#include <stdio.h> /* printf, getchar */
#include <stdlib.h> /* EXIT_SUCCESS */

#include "Classe_Liste.h"

int* Creer( int val );
void Detruire( int** ptr_ptr );
void Afficher( int* ptr );
int Est_Superieur( int* ptr1, int* ptr2 );
int Est_Strictment_Superieur( int* ptr1, int* ptr2 );
int Est_Inferieur( int* ptr1, int* ptr2 );

int main ( void )
{
    Classe_Liste liste;
    int* a = NULL;
    int* b = NULL;
    int* c = NULL;
    int* d = NULL;
    int* e = NULL;
    int* f = NULL;
    int* g = NULL;
    int* h = NULL;
    int* i = NULL;
    int* x = NULL;

    printf( "\nTests de la classe Classe_Liste\n\n" );

    /* LISTE_Creer */
    printf( "\n** LISTE_Creer **\n" );
    liste = LISTE_Creer();

    /* LISTE_Ajouter_Elmt_Debut */
    printf( "\n** LISTE_Ajouter_Elmt_Debut **\n" );
    a = Creer( 13 );
    LISTE_Ajouter_Elmt_Debut( liste, a );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );
    b = Creer( 69 );
    LISTE_Ajouter_Elmt_Debut( liste, b );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    /* LISTE_Lire_Taille */
    printf( "\n** LISTE_Lire_Taille **\n" );
    printf( "%u\n", LISTE_Lire_Taille( liste ) );

    /* LISTE_Detruire */
    printf( "\n** LISTE_Detruire **\n" );
    printf( "liste : %u\n", liste );
    LISTE_Detruire( &liste );
    printf( "liste : %u\n", liste );
    LISTE_Detruire( &liste );
    printf( "liste : %u\n", liste );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );
    Afficher( a );
    Afficher( b );

    /* LISTE_Ajouter_Elmt_Fin */
    printf( "\n** LISTE_Ajouter_Elmt_Fin **\n" );
    liste = LISTE_Creer();
    LISTE_Ajouter_Elmt_Fin( liste, a );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );
    LISTE_Ajouter_Elmt_Fin( liste, b );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );
    c = Creer( -15 );
    LISTE_Ajouter_Elmt_Fin( liste, c );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    /* LISTE_Lire_Premier_Elmt */
    printf( "\n** LISTE_Lire_Premier_Elmt **\n" );
    x = LISTE_Lire_Premier_Elmt( liste );
    Afficher( x );
    x = LISTE_Lire_Elmt_Suivant( liste );
    Afficher( x );

    /* LISTE_Ajouter_Elmt */
    printf( "\n** LISTE_Ajouter_Elmt **\n" );
    d = Creer( 0 );
    LISTE_Ajouter_Elmt( liste, d );
     printf( "Liste :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    x = LISTE_Lire_Premier_Elmt( liste );
    e = Creer( 25 );
    LISTE_Ajouter_Elmt( liste, e );
    printf( "Liste :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    x = LISTE_Lire_Dernier_Elmt( liste );
    f = Creer( 666 );
    LISTE_Ajouter_Elmt( liste, f );
    printf( "Liste :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    /* LISTE_Inserer_En_Triant */
    printf( "\n** LISTE_Inserer_En_Triant **\n" );
    g = Creer( 20 );
    LISTE_Inserer_En_Triant( liste, g, (t_fct_classe_lst_comp)Est_Superieur );
    printf( "Liste :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    h = Creer( -4 );
    LISTE_Inserer_En_Triant( liste, h, (t_fct_classe_lst_comp)Est_Superieur );
    printf( "Liste :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    /* LISTE_Trier */
    printf( "\n** LISTE_Trier **\n" );
    printf( "Liste :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    LISTE_Trier( liste, (t_fct_classe_lst_comp)Est_Superieur );
    printf( "Liste triee :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    LISTE_Trier( liste, (t_fct_classe_lst_comp)Est_Inferieur );
    printf( "Liste triee :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    i = Creer( 25 );
    LISTE_Ajouter_Elmt_Fin( liste, i );
    LISTE_Trier( liste, (t_fct_classe_lst_comp)Est_Strictment_Superieur );
    printf( "Liste triee :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    LISTE_Trier( liste, (t_fct_classe_lst_comp)Est_Inferieur );
    printf( "Liste triee :\n" );
    LISTE_Appliquer_A_Tous( liste, (t_fct_classe_lst)Afficher );

    Detruire( &a );
    Detruire( &b );
    Detruire( &c );
    Detruire( &d );
    Detruire( &e );
    Detruire( &f );
    Detruire( &g );
    Detruire( &h );
    Detruire( &i );
    LISTE_Detruire( &liste );
    return EXIT_SUCCESS;
}


int* Creer( int val )
{
    int* p = NULL;
    p = (int*)malloc( sizeof(int) );
    *p = val;
    return p;
}

void Detruire( int** ptr_ptr )
{
    if( ptr_ptr!=NULL )
    {
        if( *ptr_ptr!=NULL )
        {
            **ptr_ptr = 0;
            free( *ptr_ptr );
            *ptr_ptr = NULL;
        }
        else
        {
            printf( "ptr est deja NULL\n" );
        }
    }
}

void Afficher( int* ptr )
{
    if( ptr!=NULL )
    {
        printf( "valeur = %d\n", *ptr );
    }
    else
    {
        printf( "afficher ptr NULL\n" );
    }
}

int Est_Strictment_Superieur( int* ptr1, int* ptr2 )
{
    if( *ptr1 > *ptr2 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Est_Superieur( int* ptr1, int* ptr2 )
{
    if( *ptr1 >= *ptr2 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Est_Inferieur( int* ptr1, int* ptr2 )
{
    if( *ptr1 <= *ptr2 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
