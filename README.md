# 🥗 AI Calorie & Nutrition Tracker

A multimodal calorie and macronutrient tracking system that integrates **C++** system logic with **Python & Google Gemini Vision API** for automated food analysis from photographs.

> **Note:** The in-console interactive menu and CLI prompts are in Turkish.

---

## ⚡ Features

- **AI-Powered Food Recognition:** Analyzes food images using Google Gemini Vision to automatically extract meal names, calories, protein, carbohydrates, and fats.
- **BMR & BMI Computation:** Calculates Basal Metabolic Rate and Body Mass Index based on user biometrics, gender, and activity levels.
- **Dynamic HTML Dashboard:** Compiles daily caloric intake, macro breakdowns, and progress bars into a dark-themed local web report (`rapor.html`).
- **Dual-Language IPC Architecture:** The C++ core handles user state and console workflows, invoking Python as a sub-process engine via system calls and file streams.

---

## 🛠️ Built With

- **C++ (C++17):** Core state machine, mathematical calculations, console interface, HTML report generation.
- **Python 3:** Google Generative AI (Gemini Vision API), Pillow (Image processing), Regular Expressions.
- **HTML5 & CSS3:** Dark-mode web dashboard interface.

---

## 🚀 Getting Started

### 1. Prerequisites
Ensure you have **Python 3.8+** and a **C++ compiler** (Visual Studio MSVC or MinGW/GCC) installed.

Install the required Python dependencies:
```bash
pip install google-generativeai pillow
```
### 2. Configure API Key 

The visual recognition module requires a Google Gemini API key:
- Obtain a free API key from Google AI Studio.
- Open ai_motoru.py and assign your key to the variable:
```bash
GOOGLE_API_KEY = "YOUR_GEMINI_API_KEY_HERE"
  ```
### 3. Build & Run
**Option A: Visual Studio (Recommended)**
- Open kalori uygulaması.sln in Visual Studio.
- Set the build configuration to Release / x64.
- Press Ctrl + F5 to compile and run.

---

## 📸 Analyzing Your Own Food Images

- **Place Image in Root Folder:** Copy your food photograph (e.g., `lunch.jpg`) directly into the project root directory alongside the executable.
- **Trigger Vision Module:** Launch the application and select `[5] AI Kamera/Fotoğraf Analizi` from the console menu.
- **Input Image Name:** When prompted by the CLI, enter the exact image filename (e.g., `lunch.jpg` or default samples like `pizza.jpg`, `salata.jpg`, `sarma.jpg`).
- **Auto-Log to Daily Progress:** Review the Gemini-generated calorie and macronutrient breakdown, then confirm (`E/H`) to append the meal to your daily tracking log.
