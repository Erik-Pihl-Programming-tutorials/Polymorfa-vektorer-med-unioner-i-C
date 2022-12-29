# Unioner för polymorfa vektorer i C
Enkel implementering av polymorfa (mångformiga) vektorer i C via användning av unioner. 
Även motsvarande funktionalitet i C++ demonstreras via templates.

Filen "vector.h" innehåller deklaration och definition av unioner, struktar, enumerationer och funktioner för 
implementering av polymorfa vektorer via strukten vector.

I filen "main.c" deklareras två vektorer, varav den första används för lagring av heltal och den andre för flyttal.
Heltalsvektorn fylls med tio heltal 0 - 9, samtidigt som flyttalsvektorn fylls med tio flyttal 0 - 4.5.

Filen "main.cpp" demonstrerar motsvarande funktionalitet i C++ via en generisk strukt vector, som möjliggör
att vektorns datatyp kan väljas vid deklarationen. Templates ersätter därmed union-implementeringen i detta fall.

Se video tutorial här: https://youtu.be/a5nS0vrzPMk

Se mer utvecklad vektorimplementering för lagring av heltal i C här:
https://github.com/Erik-Pihl-Programming-tutorials/Dynamisk-minnesallokering-i-C-del-II.git

Se mer utvecklad klasstemplate-implementering för polymorfa vektorer i C++ här: 
https://github.com/Erik-Pihl-Programming-tutorials/Klasstemplates-i-CPP.git
