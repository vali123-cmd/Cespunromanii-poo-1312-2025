# Ce spun românii? 🇷🇴

---
**Ce spun românii?** este un joc inspirat de celebrul Family Feud, creat pentru cei care vor să retrăiască experiența copilăriei într-un mod modern și interactiv, direct din terminal.

---

## 🕹️ Caracteristici principale

- **Gameplay**: Două familii se întrec în a ghici cele mai populare răspunsuri la întrebări amuzante și interesante.
- **Verificare inteligentă a răspunsurilor**: Folosește AI (prin Ollama sau alt LLM local) pentru a valida răspunsurile jucătorilor, nu doar pe baza asemănării literale, ci și pe baza sensului.
- **Similaritate semantică**: Răspunsurile nu sunt verificate doar cu distanța Levenshtein (care măsoară diferențele de caractere), ci și cu ajutorul AI, care înțelege contextul și sensul cuvintelor.
- **Interfață colorată și spațiată pentru terminal**: Întrebările sunt evidențiate cu roșu, iar afișarea scorurilor și răspunsurilor este aerisită și clară.
- **Moduri de joc variate**: Poți alege între mod Normal și Special, fiecare cu provocări diferite.
- **Configurare flexibilă pentru AI**: Poți activa sau dezactiva validarea cu AI, în funcție de preferințe sau de conexiunea la internet.

---

## 🤖 Cum funcționează verificarea răspunsurilor?

Inițial, jocul folosea distanța Levenshtein pentru a compara răspunsurile jucătorilor cu cele corecte. Această metodă funcționează bine pentru greșeli de scriere minore, dar nu poate înțelege dacă două răspunsuri diferite exprimă același lucru (ex: "mașină" vs "automobil").

**Acum, jocul folosește AI pentru a verifica răspunsurile:**
- AI-ul analizează răspunsul jucătorului și îl compară semantic cu răspunsurile corecte.
- Astfel, răspunsuri cu același sens, dar scrise diferit, sunt recunoscute ca fiind corecte.
- Dacă nu ai AI activat, se folosește totuși o verificare de similaritate, dar fără înțelegerea contextului.
- 
---

##  Resurse externe

- [cpr (1.11.0)](https://github.com/libcpr/cpr/releases/tag/1.11.0) (MIT)
- [json (3.11.3)](https://github.com/nlohmann/json/releases/tag/v3.11.3) (MIT)
- [llamafile (v0.9.1)](https://github.com/Mozilla-Ocho/llamafile) (Apache 2.0)

---

## 🛠️ Instalare și configurare AI

### Activare Ollama (AI) pe Linux:
- [Tutorial complet](https://itsfoss.com/ollama-setup-linux/)


### Pentru Windows și Mac:
- [Ghid pas cu pas](https://medium.com/@sridevi17j/step-by-step-guide-setting-up-and-running-ollama-in-windows-macos-linux-a00f21164bf3)

Dacă Ollama nu funcționează, apasă `0` când ești întrebat de serverul AI.

Pentru alte LLM-uri locale, modifică fișierul `configure.json` la secțiunea `url_endpoint`.

## 📄 Ghid rapid pentru `configure.json`

Fișierul `configure.json` permite personalizarea modului în care jocul interacționează cu AI-ul și gestionează validarea răspunsurilor. Acesta se află în directorul principal al proiectului și poate fi editat cu orice editor de text.

### Exemplu de structură:

```json
{
  "api-endpoint": "127.0.0.1:11434/api/chat",
  "timeout": "5000",
  "model": "llama3",
  "custom-prompt": "Compare the level of similarity between the following two romanian words based on their meanings and usage. Provide a float value between 0 and 1, where 0 means no similarity and 1 means identical meaning. I want only a number of type 0.xx in the answer and nothing else. The words are: <word1> and <word2>.",
  "additional-prompt": "Poate fi considerat următorul răspuns corect la întrebarea: <question> ? Răspunsul este: <answer> . Răspunsul este corect? Răspunde cu '1' pentru 'da' sau '0' pentru 'nu'."
}
```

###  Explicație a variabilelor:

- **api-endpoint**: Adresa și portul la care rulează serverul AI (ex: Ollama). Modifică dacă folosești altă adresă sau port.
- **timeout**: Timpul maxim (în milisecunde) de așteptare pentru răspunsul AI-ului.
- **model**: Numele modelului AI folosit (ex: `llama3`). Poate fi schimbat în funcție de modelele disponibile local.
- **custom-prompt**: Promptul folosit pentru a compara semantic două cuvinte. Poți personaliza formularea pentru a obține rezultate mai bune.
- **additional-prompt**: Promptul folosit pentru a verifica dacă un răspuns este corect pentru o anumită întrebare. Poți adapta textul pentru a schimba modul de validare.

### Recomandări:

- Dacă folosești un alt model sau server AI, modifică valorile pentru `api-endpoint` și `model`.
- Pentru rezultate mai bune la validarea răspunsurilor, poți ajusta prompturile după preferință.
- Orice modificare a acestui fișier se aplică la următoarea rulare a jocului.

---

## Note

- Asigură-te că ai instalat toate dependențele necesare înainte de a rula jocul.
- Pentru o experiență optimă, joacă jocul în terminale care suportă culori și formatare avansată.

---

## Contribuții

Contribuțiile sunt binevenite! Dacă dorești să adaugi ceva sau să raportezi o problemă, te rog să deschizi un issue sau un pull request pe GitHub.

---



## Tehnologii folosite

- **C++** pentru logica jocului și gestionarea întrebărilor/răspunsurilor.
- **AI/ML model** pentru verificarea răspunsurilor bazată pe înțelegerea semantică.

---

## Planuri de viitor

- Realizarea unei versiuni cu interfață grafică (GUI) pentru o experiență mai prietenoasă.
- Nu sunt decis dacă să folosesc Qt sau SFML pentru GUI, dar sper să o fac cât mai curând. :)


Mulțumesc că ai ales să joci **Ce spun românii?**! Sper să te distrezi și să îți testezi cunoștințele într-un mod plăcut și provocator.
Nu ezita să împărtășești feedback-ul tău!

---

