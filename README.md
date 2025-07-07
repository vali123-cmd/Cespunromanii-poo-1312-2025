# What Do Romanians Say? 🇷🇴

---
**What Do Romanians Say?** is a game inspired by the famous *Family Feud*, created for those who want to relive their childhood experience in a modern and interactive way — right from the terminal.

---

## 🕹️ Main Features

- **Gameplay**: Two families compete to guess the most popular answers to fun and interesting questions.
- **Smart Answer Checking**: Uses AI (via Ollama or another local LLM) to validate players' answers not just based on literal similarity but also based on meaning.
- **Semantic Similarity**: Answers are checked not only with Levenshtein distance (which measures character-level differences) but also with the help of AI that understands the context and meaning of words.
- **Colorful and Spaced Terminal Interface**: Questions are highlighted in red, and the display of scores and answers is clean and easy to read.
- **Various Game Modes**: Choose between Normal and Special modes, each with different challenges.
- **Flexible AI Configuration**: You can enable or disable AI validation depending on your preferences or internet connection.

---

## 🤖 How Does Answer Validation Work?

Initially, the game used Levenshtein distance to compare player answers with the correct ones. This method works well for minor typos but cannot understand when two different words mean the same thing (e.g., "car" vs. "automobile").

**Now, the game uses AI to validate answers:**
- The AI analyzes the player's answer and semantically compares it with the correct ones.
- Therefore, answers with the same meaning, even if worded differently, are recognized as correct.
- If AI is not enabled, similarity checking is still used, but without context understanding.

---

## External Resources

- [cpr (1.11.0)](https://github.com/libcpr/cpr/releases/tag/1.11.0) (MIT)
- [json (3.11.3)](https://github.com/nlohmann/json/releases/tag/v3.11.3) (MIT)
- [llamafile (v0.9.1)](https://github.com/Mozilla-Ocho/llamafile) (Apache 2.0)

---

## 🛠️ Installation and AI Configuration

### Activating Ollama (AI) on Linux:
- [Complete tutorial](https://itsfoss.com/ollama-setup-linux/)
- Recommendation: Use `llama3` instead of `llama2` (`ollama pull llama3`)
- NOTE: ROLLAMA or ROGEMMA are good Romanian-language alternatives to Ollama.
- It’s up to the user which LLM model to use, but it must be local, and you need to modify the `configure.json` file under the `url_endpoint` section.

### For Windows and Mac:
- [Step-by-step guide](https://medium.com/@sridevi17j/step-by-step-guide-setting-up-and-running-ollama-in-windows-macos-linux-a00f21164bf3)

If Ollama doesn’t work, press `0` when asked for the AI server.

For other local LLMs, modify the `configure.json` file in the `url_endpoint` section.

---

## Notes

- Make sure all necessary dependencies are installed before running the game.
- For the best experience, play the game in terminals that support color and advanced formatting.

---

## Contributions

Contributions are welcome! If you'd like to add something or report an issue, please open an issue or a pull request on GitHub.

---

## Technologies Used

- **C++** for the game logic and handling of questions/answers.
- **AI/ML model** for semantic-based answer validation.

---

## Future Plans

- Develop a graphical user interface (GUI) version for a more user-friendly experience.
- I haven’t decided yet whether to use Qt or SFML for the GUI, but I hope to do it soon. :)

---

Thank you for choosing to play **What Do Romanians Say?** I hope you have fun and challenge your knowledge in an enjoyable and engaging way.  
Feel free to share your feedback!
