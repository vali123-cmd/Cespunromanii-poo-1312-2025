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

---

##  Resurse externe

- [cpr (1.11.0)](https://github.com/libcpr/cpr/releases/tag/1.11.0) (MIT)
- [json (3.11.3)](https://github.com/nlohmann/json/releases/tag/v3.11.3) (MIT)
- [llamafile (v0.9.1)](https://github.com/Mozilla-Ocho/llamafile) (Apache 2.0)

---

## 🛠️ Instalare și configurare AI

### Activare Ollama (AI) pe Linux:
- [Tutorial complet](https://itsfoss.com/ollama-setup-linux/)
- Recomandare: folosește `llama3` în loc de `llama2` (`ollama pull llama3`)
- OBSERVATIE: ROLLAMA sau ROGEMMA sunt alternative bune pe Limba Română pentru Ollama.
- Este la latitudinea utilizatorului ce model de LLM doreste să folosească, dar acesta trebuie să fie local si să modifice fișierul `configure.json` la secțiunea `url_endpoint`.

### Pentru Windows și Mac:
- [Ghid pas cu pas](https://medium.com/@sridevi17j/step-by-step-guide-setting-up-and-running-ollama-in-windows-macos-linux-a00f21164bf3)

Dacă Ollama nu funcționează, apasă `0` când ești întrebat de serverul AI.

Pentru alte LLM-uri locale, modifică fișierul `configure.json` la secțiunea `url_endpoint`.


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
