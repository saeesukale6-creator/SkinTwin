
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class SkinProfile {
private:
    string name;
    string skinType;
    string concern;
    double budget;

public:
    // Function to collect the user's skincare profile
    void inputProfile() {
        cout << "\n===== SKINTWIN SKIN PROFILE =====\n";

        cout << "Enter your name: ";
        getline(cin, name);

        cout << "\nChoose your skin type:\n";
        cout << "1. Oily\n";
        cout << "2. Dry\n";
        cout << "3. Combination\n";
        cout << "4. Normal\n";
        cout << "Enter choice (1-4): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: skinType = "Oily"; break;
            case 2: skinType = "Dry"; break;
            case 3: skinType = "Combination"; break;
            case 4: skinType = "Normal"; break;
            default: skinType = "Normal";
        }

        cout << "\nChoose your main skin concern:\n";
        cout << "1. Acne and bumps\n";
        cout << "2. Dryness\n";
        cout << "3. Uneven skin tone\n";
        cout << "4. Dullness\n";
        cout << "Enter choice (1-4): ";

        int concernChoice;
        cin >> concernChoice;

        switch (concernChoice) {
            case 1: concern = "Acne and bumps"; break;
            case 2: concern = "Dryness"; break;
            case 3: concern = "Uneven skin tone"; break;
            case 4: concern = "Dullness"; break;
            default: concern = "Dullness";
        }

        cout << "\nEnter your monthly skincare budget (Rs): ";
        cin >> budget;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Display the user's profile
    void displayProfile() const {
        cout << "\n===== YOUR SKINTWIN PROFILE =====\n";
        cout << "Name: " << name << "\n";
        cout << "Skin type: " << skinType << "\n";
        cout << "Main concern: " << concern << "\n";
        cout << "Monthly budget: Rs " << budget << "\n";
    }

    // Generate a basic rule-based skincare routine
    void recommendRoutine() const {
        cout << "\n===== YOUR PERSONALIZED ROUTINE =====\n";

        cout << "\nMORNING ROUTINE\n";
        cout << "1. Gentle cleanser suitable for your skin type.\n";

        if (skinType == "Oily") {
            cout << "2. Lightweight, non-comedogenic moisturizer.\n";
        } else if (skinType == "Dry") {
            cout << "2. Moisturizer that supports the skin barrier.\n";
        } else {
            cout << "2. Moisturizer suited to your skin's needs.\n";
        }

        cout << "3. Broad-spectrum SPF 30+ sunscreen.\n";

        cout << "\nEVENING ROUTINE\n";
        cout << "1. Gentle cleanser.\n";
        cout << "2. Moisturizer suitable for your skin type.\n";

        cout << "\nFOCUS FOR YOUR MAIN CONCERN\n";

        if (concern == "Acne and bumps") {
            cout << "Look for non-comedogenic products.\n";
            cout << "Consider discussing acne treatments with a dermatologist.\n";
        } else if (concern == "Dryness") {
            cout << "Look for moisturizing ingredients such as glycerin or ceramides.\n";
        } else if (concern == "Uneven skin tone") {
            cout << "Use sunscreen consistently and introduce new products carefully.\n";
        } else {
            cout << "Focus on gentle cleansing, moisturizing and daily sunscreen.\n";
        }

        cout << "\nBUDGET TIP\n";

        if (budget < 500) {
            cout << "Prioritize a basic cleanser, moisturizer and sunscreen.\n";
            cout << "Compare prices and product sizes before purchasing.\n";
        } else if (budget < 1500) {
            cout << "Prioritize the basics first, then consider one targeted product.\n";
        } else {
            cout << "Build a simple routine first; more products are not always better.\n";
        }

        cout << "\nNote: These are general suggestions, not a diagnosis.\n";
        cout << "Stop using products that cause irritation and seek professional advice if needed.\n";
    }
};

int main() {
    cout << "====================================\n";
    cout << "       Welcome to SkinTwin!\n";
    cout << " Your Personal Skincare Assistant\n";
    cout << "====================================\n";

    SkinProfile user;

    user.inputProfile();
    user.displayProfile();
    user.recommendRoutine();

    cout << "\nThank you for using SkinTwin!\n";

    return 0;
}
