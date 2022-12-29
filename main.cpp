/********************************************************************************
* main.cpp: Demonstration av polymorfa (mångformiga) vektorer i C++.
********************************************************************************/
#include <iostream> /* Innehåller std::cout för utskrift. */
#include <cstdlib>  /* Innehåller std::malloc för dynamisk minnesallokering. */

/********************************************************************************
* vector: Strukt för lagring av element av godtycklig datatyp.
********************************************************************************/
template<class T>
struct vector
{
   T* data = nullptr;    /* Pekare till det dynamiska fältet. */
   std::size_t size = 0; /* Vektorns storlek, dvs. antalet element. */

   /********************************************************************************
   * vector: Tom konstruktor, initierar tom vektor.
   ********************************************************************************/
   vector(void) { }

   /********************************************************************************
   * begin: Returnerar adressen där vektorn börjar.
   ********************************************************************************/
   T* begin(void) const
   {
      return this->data;
   }

   /********************************************************************************
   * end: Returnerar adressen där vektorn slutar.
   ********************************************************************************/
   T* end(void) const
   {
      return this->data + this->size;
   }

   /********************************************************************************
   * push_back: Lägger ett nytt element längst bak i angiven vektor. Om tillägget
   *            lyckas returneras 0, annars returneras felkod 1.
   * 
   *            - new_element: Referens till elementet som ska läggas till.
   ********************************************************************************/
   int push_back(const T& new_element)
   {
      auto copy = static_cast<T*>(std::realloc(this->data, sizeof(T) * (this->size + 1)));
      if (!copy) return 1;
      copy[this->size++] = new_element;
      this->data = copy;
      return 0;
   }

   /********************************************************************************
   * print: Skriver ut innehållet i angiven vektor via angiven utström, där
   *        standardutenheten std::cout används som default för utskrift i 
   *        terminalen. Om vektorn är tom sker ingen utskrift.
   * 
   *        - ostream: Referens till angiven utström (default = std::cout).
   ********************************************************************************/
   void print(std::ostream& ostream = std::cout) const
   {
      if (this->size == 0) return;
      ostream << "--------------------------------------------------------------------------------\n";

      for (auto& i : *this)
      {
         ostream << i << "\n";
      }

      ostream << "--------------------------------------------------------------------------------\n\n";
      return;
   }
};

/********************************************************************************
* main: Fyller en vektor v1 med tio heltal 0 - 9 samt en vektor v2 med tio
*       flyttal 0 - 4.5. Vektorernas innehåll skrivs ut i terminalen.
********************************************************************************/
int main(void)
{
   vector<int> v1;
   vector<double> v2;

   for (auto i = 0; i < 10; ++i)
   {
      v1.push_back(i);
      v2.push_back(i / 2.0);
   }

   v1.print();
   v2.print();
   return 0;
}