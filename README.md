
# SkinTwin 🌸

[🌐 **Live Website — Try SkinTwin Here!**](https://velvety-empanada-f82151.netlify.app/)

### A C++-Based Personalized Skincare Recommendation System


SkinTwin is a web-based skincare recommendation prototype that generates simple, personalized skincare routines based on a user's skin type, primary skin concern, and budget.

The project combines a web-based user interface with a C++ backend to demonstrate how programming concepts can be used to build a practical recommendation system.

## ✨ Features

- **Personalized skincare guidance:** Accepts a user's skin type and primary concern.
- **Morning and evening routines:** Generates basic routine recommendations.
- **Budget-based advice:** Adjusts guidance according to the selected budget.
- **Interactive website:** Provides a simple and user-friendly interface.
- **C++ backend:** Processes user information and generates recommendations.
- **HTTP API:** Connects the frontend to the backend.
- **Input validation:** Checks submitted profile information.
- **Responsive design:** Uses web technologies to present the interface across different screen sizes.

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Backend recommendation logic |
| HTML | Website structure |
| CSS | Website styling |
| JavaScript | Form handling and API communication |
| cpp-httplib | C++ HTTP server |
| JSON | Structured API responses |
| Visual Studio Code | Development environment |

## 📁 Project Structure

```text
SkinTwin/
├── main.cpp
├── website/
│   ├── index.html
│   ├── style.css
│   └── script.js
└── backend/
    ├── server.cpp
    └── httplib.h
```

## ⚙️ How It Works

1. The user opens the SkinTwin website.
2. The user enters their name, skin type, primary concern, and budget.
3. JavaScript sends the profile to the C++ backend through an HTTP request.
4. The backend validates the information and applies predefined recommendation rules.
5. The backend returns a JSON response.
6. The website displays the generated morning and evening routines, skin-concern guidance, and budget advice.

## 🚀 Running the Project Locally

### Prerequisites

- Visual Studio Code
- A C++ compiler such as GCC
- A local website server, such as the VS Code Live Server extension
- The `httplib.h` header file in the `backend` directory

### Start the C++ Backend

Open a terminal in the project directory and run:

```powershell
cd backend
g++ server.cpp -o server.exe -lws2_32 -lwsock32
.\server.exe
```

Keep the backend terminal open while using the website.

To check the backend, open:

```text
http://localhost:8080/
```

The expected response is:

```json
{"status":"online","app":"SkinTwin API"}
```

### Open the Website

1. Open `website/index.html` in Visual Studio Code.
2. Right-click the file and select **Open with Live Server**.
3. Fill in the skincare profile and select **Create my routine**.

The backend must be running for the complete recommendation workflow to work.

## 🧠 Recommendation Method

SkinTwin currently uses a **rule-based recommendation engine**. Predefined conditional rules determine the guidance shown for different skin types, concerns, and budgets.

The current prototype does not use a trained machine-learning model or automatic skin-image analysis.

## 🎯 Project Objectives

- Demonstrate the application of C++ programming to a practical problem.
- Integrate a C++ backend with a web-based frontend.
- Implement rule-based decision-making and input validation.
- Generate basic skincare routine guidance according to user-provided preferences.
- Build a foundation for future enhancements.

## 🔮 Future Scope

- Integration of a verified skincare product database.
- Secure user accounts and persistent profile storage.
- Deployment of the website and backend for public access.
- Evaluation of a suitable machine-learning model using an appropriate dataset.
- Optional image-based skin analysis with suitable validation and privacy safeguards.
- Expanded testing and evaluation of recommendation quality.

## ⚠️ Disclaimer

SkinTwin is an educational prototype that provides general skincare information. Its recommendations are rule-based and are not medical diagnoses or a substitute for professional medical advice. Individual results may vary.

## 👩‍💻 Project Information

- **Project:** SkinTwin
- **Category:** C++ Project-Based Learning
- **Purpose:** Educational software development project
- **Developer(s):** Add the names of the project team members here.

## 📄 License

No open-source license has been specified yet. All rights are reserved by default unless a license is added to this repository.
