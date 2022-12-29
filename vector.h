/********************************************************************************
* vector.h: Inneh�ller funktionalitet f�r polymorfa (m�ngformiga) vektorer i
*           i C via en kombination av unioner, enumerationer och struktar.
********************************************************************************/
#ifndef VECTOR_H_
#define VECTOR_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>  /* Inneh�ller printf, scanf, FILE* med mera. */
#include <stdlib.h> /* Inneh�ller malloc, realloc och free. */

/********************************************************************************
* vector_type: Enumeration som indikerar anv�nd datatyp f�r polymorfa vektorer.
********************************************************************************/
enum vector_type
{
   VECTOR_TYPE_INT,    /* Vektorn lagrar heltal. */
   VECTOR_TYPE_DOUBLE, /* Vektorn lagrar flyttal. */
   VECTOR_TYPE_NONE    /* Vektorns datatyp �r icke specificerad. */
};

/********************************************************************************
* vector_data_ptr: Inneh�ller pekare till dynamiska f�lt av datatyper int
*                  och double f�r implementering med polymorfa vektorer.
********************************************************************************/
union vector_data_ptr
{
   int* integer;    /* Pekare till dynamiskt f�lt inneh�llande heltal. */
   double* decimal; /* Pekare till dynamiskt f�lt inneh�llande flyttal. */
};

/********************************************************************************
* vector: Strukt f�r polymorfa vektorer som kan lagras b�de heltal och flyttal.
********************************************************************************/
struct vector
{
   union vector_data_ptr data; /* Pekare till dynamiskt f�lt inneh�llande data. */
   size_t size;                /* Vektorns storlek, dvs. antalet element. */
   enum vector_type type;      /* Vektorns datatyp (int eller double). */
};

/********************************************************************************
* vector_data_ptr_init: Initierar pekare f�r en polymorf vektor.
* 
*                       - self: Referens till objektet som ska initieras.
********************************************************************************/
static inline void vector_data_ptr_init(union vector_data_ptr* self)
{
   self->integer = 0;
   self->decimal = 0;
   return;
}

/********************************************************************************
* vector_data_ptr_clear: T�mmer inneh�ll lagrat i en polymorf vektor.
*
*                        - self         : Referens till objektet vars inneh�ll 
*                                         ska t�mmas.
*                        - used_datatype: Indikerar datatypen p� det minne
*                                         som har allokerats.
********************************************************************************/
static inline void vector_data_ptr_clear(union vector_data_ptr* self,
                                         const enum vector_type used_datatype)
{
   if (used_datatype == VECTOR_TYPE_INT)
   {
      free(self->integer);
   }
   else if (used_datatype == VECTOR_TYPE_DOUBLE)
   {
      free(self->decimal);
   }

   self->integer = 0;
   self->decimal = 0;
   return;
}

/********************************************************************************
* vector_init: Initierar tom polymorf vektor av angiven datatyp.
* 
*              - self: Referens till vektorn som ska initieras.
*              - type: Vektorns datatyp.
********************************************************************************/
static inline void vector_init(struct vector* self,
                               const enum vector_type type)
{
   vector_data_ptr_init(&self->data);
   self->size = 0;
   self->type = type;
   return;
}

/********************************************************************************
* vector_clear: T�mmer angiven polymorf vektor.
*
*               - self: Referens till vektorn som ska t�mmas.
********************************************************************************/
static inline void vector_clear(struct vector* self)
{
   vector_data_ptr_clear(&self->data, self->type);
   self->size = 0;
   return;
}

/********************************************************************************
* vector_push_back: L�gger till ett nytt element l�ngst bak i angiven vektor.
*                   Om till�gget lyckas returneras 0, annars returneras felkod 1.
*
*                   - self       : Referens till vektorn som ska tilldelas.
*                   - new_element: Referens till elementet som ska l�ggas till.
********************************************************************************/
static inline int vector_push_back(struct vector* self,
                                   const void* new_element)
{
   if (self->type == VECTOR_TYPE_INT)
   {
      int* copy = (int*)realloc(self->data.integer, sizeof(int) * (self->size + 1));
      if (!copy) return 1;
      copy[self->size++] = *(int*)(new_element);
      self->data.integer = copy;
      return 0;
   }
   else if (self->type == VECTOR_TYPE_DOUBLE)
   {
      double* copy = (double*)realloc(self->data.decimal, sizeof(double) * (self->size + 1));
      if (!copy) return 1;
      copy[self->size++] = *(double*)(new_element);
      self->data.decimal = copy;
      return 0;
   }
   else
   {
      return 1;
   }
}

/********************************************************************************
* vector_print: Skriver ut inneh�ll lagrat i angiven vektor via godtycklig
*               utstr�m, d�r standardutenhet stdout anv�nds som default f�r
*               utskrift i terminalen. Om vektorn �r tom eller om datatypen
*               inte �r specificerad sker ingen utskrift.
*
*               - self   : Referens till vektorn vars inneh�ll ska skrivas ut.
*               - ostream: Referens till godtycklig utstr�m (default = stdout).
********************************************************************************/
static inline void vector_print(const struct vector* self,
                                FILE* ostream)
{
   if (self->size == 0 || self->type == VECTOR_TYPE_NONE) return;
   if (!ostream) ostream = stdout;
   fprintf(ostream, "--------------------------------------------------------------------------------\n");

   for (size_t i = 0; i < self->size; ++i)
   {
      if (self->type == VECTOR_TYPE_INT)
      {
         fprintf(ostream, "%d\n", self->data.integer[i]);
      }
      else
      {
         fprintf(ostream, "%lg\n", self->data.decimal[i]);
      }
   }

   fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
   return;
}

#endif /* VECTOR_H_ */