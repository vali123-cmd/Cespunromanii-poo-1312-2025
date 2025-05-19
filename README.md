## Ce spun romanii?

<hr>
Acesta este un joc de tipul Family Feud sau 
Ce spun romanii? pentru cei ce s-au uitat in copilarie
si vor sa retraiasca aceasta experienta. 
<hr>






### Viitoare feature-uri

- [ ] Adaugare de intrebari
  
- [ ] Adaugare de raspunsuri
  
- [ ] Adaugare de imagini cu SFML
  
- [ ] Adaugare de sunete
  
- [ ] Adaugare de animatii
  
- [ ] Adaugare AI Similarity Calculator
  
- [ ] Adaugare de statistici
  
- [ ] Adaugare de AI pentru a juca impotriva calculatorului
  
- [ ] Adaugare de AI Tips
<hr>

### Resurse externe:

- [cpr (1.11.0)](https://github.com/libcpr/cpr/releases/tag/1.11.0) (MIT)
- [json (3.11.3)](https://github.com/nlohmann/json/releases/tag/v3.11.3) (MIT)
- [llamafile (v0.9.1)](https://github.com/Mozilla-Ocho/llamafile) (Apache 2.0)
- [simsimd (v6.4.0)](https://github.com/ashvardanian/simsimd) (Apache 2.0)
    - pentru <a href="https://en.wikipedia.org/wiki/Cosine_similarity">similaritate cosinus</a>



TUTORIAL PENTRU ACTIVARE OLLAMA(AI) PE LINUX:
https://itsfoss.com/ollama-setup-linux/
La model, in loc de ollama pull llama2, recomand llama3









separarea codului din clase în .h (sau .hpp) și .cpp (facut)
moșteniri:
minim o clasă de bază și 3 clase derivate din aceeași ierarhie
ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
minim o funcție virtuală va fi specifică temei (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
afișare virtuală, interfață non-virtuală
apelarea constructorului din clasa de bază din constructori din derivate
clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
dynamic_cast/std::dynamic_pointer_cast pentru downcast cu sens

excepții
ierarhie proprie cu baza std::exception sau derivată din std::exception; minim 3 clase pentru erori specifice distincte
clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
utilizare cu sens: de exemplu, throw în constructor (sau funcție care întoarce un obiect), try/catch în main
această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
funcții și atribute static
STL
cât mai multe const
funcții de nivel înalt, de eliminat cât mai mulți getters/setters/funcții low-level
minim 75-80% din codul propriu să fie C++
la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, pe lângă cele 3 derivate deja adăugate din aceeași ierarhie
noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
tag de git pe commit cu toate bifele: de exemplu v0.2