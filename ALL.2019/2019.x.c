#include <stdio.h>


/* global card structure definition */
struct card
{
    int face ; // define pointer face
};// end structure card

typedef struct card Card ;

/* function prototypes */
void passByValue(Card c[]);

int main(void)
{
    Card c[2] ;
    c[0].face = 1;

    printf("c.face before passByValue() = %d\n", c[0].face);

    passByValue(c);

    printf("c.face after passByValue() = %d\n",c[0].face);
    printf("As you can see the value of c did not change\n");
    printf("\nand the Card c inside the function has been destroyed"
        "\n(no longer in memory)");
}


void passByValue(Card c[])
{
    c[0].face = 5;
}
