/********************************************************************************
* vector.h: Innehåller funktionalitet för polymorfa (mångformiga) vektorer i
*           i C via en kombination av unioner, enumerationer och struktar.
********************************************************************************/
#ifndef VECTOR_H_
#define VECTOR_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>  /* Innehåller printf, scanf, FILE* med mera. */
#include <stdlib.h> /* Innehåller malloc, realloc och free. */

/********************************************************************************
* vector_type: Enumeration som indikerar använd datatyp för polymorfa vektorer.
********************************************************************************/
enum vector_type
{
   VECTOR_TYPE_INT,    /* Vektorn lagrar heltal. */
   VECTOR_TYPE_DOUBLE, /* Vektorn lagrar flyttal. */
   VECTOR_TYPE_NONE    /* Vektorns datatyp är icke specificerad. */
};

/********************************************************************************
* vector_data_ptr: Innehåller pekare till dynamiska fält av datatyper int
*                  och double för implementering med polymorfa vektorer.
********************************************************************************/
union vector_data_ptr
{
   int* integer;    /* Pekare till dynamiskt fält innehållande heltal. */
   double* decimal; /* Pekare till dynamiskt fält innehållande flyttal. */
};

/********************************************************************************
* vector: Strukt för polymorfa vektorer som kan lagras både heltal och flyttal.
********************************************************************************/
struct vector
{
   union vector_data_ptr data; /* Pekare till dynamiskt fält innehållande data. */
   size_t size;                /* Vektorns storlek, dvs. antalet element. */
   enum vector_type type;      /* Vektorns datatyp (int eller double). */
};

/********************************************************************************
* vector_data_ptr_init: Initierar pekare för en polymorf vektor.
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
* vector_data_ptr_clear: Tömmer innehåll lagrat i en polymorf vektor.
*
*                        - self         : Referens till objektet vars innehåll 
*                                         ska tömmas.
*                        - used_datatype: Indikerar datatypen på det minne
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
* vector_clear: Tömmer angiven polymorf vektor.
*
*               - self: Referens till vektorn som ska tömmas.
********************************************************************************/
static inline void vector_clear(struct vector* self)
{
   vector_data_ptr_clear(&self->data, self->type);
   self->size = 0;
   return;
}

/********************************************************************************
* vector_push_back: Lägger till ett nytt element längst bak i angiven vektor.
*                   Om tillägget lyckas returneras 0, annars returneras felkod 1.
*
*                   - self       : Referens till vektorn som ska tilldelas.
*                   - new_element: Referens till elementet som ska läggas till.
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
* vector_print: Skriver ut innehåll lagrat i angiven vektor via godtycklig
*               utström, där standardutenhet stdout används som default för
*               utskrift i terminalen. Om vektorn är tom eller om datatypen
*               inte är specificerad sker ingen utskrift.
*
*               - self   : Referens till vektorn vars innehåll ska skrivas ut.
*               - ostream: Referens till godtycklig utström (default = stdout).
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