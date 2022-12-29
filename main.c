/********************************************************************************
* main.c: Demonstration av polymorfa (mångformiga) vektorer i C via en
*         kombination av struktar, unioner och enumerationer.
********************************************************************************/
#include "vector.h"

/********************************************************************************
* main: Fyller en vektor v1 med tio heltal 0 - 9 samt en vektor v2 med tio
*       flyttal 0 - 4.5. Vektorernas innehåll skrivs ut i terminalen.
********************************************************************************/
int main(void)
{
   struct vector v1, v2;

   vector_init(&v1, VECTOR_TYPE_INT);
   vector_init(&v2, VECTOR_TYPE_DOUBLE);

   for (int i = 0; i < 10; ++i)
   {
      const double num = i / 2.0;
      vector_push_back(&v1, &i);
      vector_push_back(&v2, &num);
   }

   vector_print(&v1, 0);
   vector_print(&v2, 0);
   return 0;
}