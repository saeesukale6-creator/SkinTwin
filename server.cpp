
#include "httplib.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// Safely format text for a JSON response.
string jsonEscape(const string& input) {
    string output;

    for (char c : input) {
        switch (c) {
            case '"':  output += "\\\""; break;
            case '\\': output += "\\\\"; break;
            case '\n': output += "\\n"; break;
            case '\r': output += "\\r"; break;
            case '\t': output += "\\t"; break;
            default:
                if (static_cast<unsigned char>(c) >= 32) {
                    output += c;
                }
        }
    }

    return output;
}

string jsonArray(const string items[], int count) {
    string result = "[";

    for (int i = 0; i < count; i++) {
        if (i > 0) result += ",";
        result += "\"" + jsonEscape(items[i]) + "\"";
    }

    result += "]";
    return result;
}

int main() {
    httplib::Server server;

    // Allow the local website to call this API.
    server.set_default_headers({
        {"Access-Control-Allow-Origin", "*"},
        {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
        {"Access-Control-Allow-Headers", "Content-Type"}
    });

    server.Options("/recommend", [](const httplib::Request&,
                                    httplib::Response& res) {
        res.status = 204;
    });

    // Quick health check to confirm the server is running.
    server.Get("/", [](const httplib::Request&,
                       httplib::Response& res) {
        res.set_content(
            R"({"status":"online","app":"SkinTwin API"})",
            "application/json"
        );
    });

    // Receive a profile from the website and return recommendations.
    server.Post("/recommend", [](const httplib::Request& req,
                                 httplib::Response& res) {
        string name = req.get_param_value("name");
        string skinType = req.get_param_value("skinType");
        string concern = req.get_param_value("concern");
        string budgetText = req.get_param_value("budget");

        // Validate the submitted values.
        if (name.empty() ||
            (skinType != "Oily" &&
             skinType != "Dry" &&
             skinType != "Combination" &&
             skinType != "Normal" &&
             skinType != "Sensitive") ||
            (concern != "Acne and bumps" &&
             concern != "Dryness" &&
             concern != "Uneven skin tone" &&
             concern != "Dullness" &&
             concern != "Sensitivity") ||
            (budgetText != "500" &&
             budgetText != "1000" &&
             budgetText != "1500" &&
             budgetText != "2500")) {
            res.status = 400;
            res.set_content(
                R"({"error":"Please provide a valid skincare profile."})",
                "application/json"
            );
            return;
        }

        int budget = stoi(budgetText);

        string morning[3] = {
            "Gently cleanse your face.",
            "Apply a moisturizer suited to your skin.",
            "Finish with broad-spectrum SPF 30+ sunscreen."
        };

        string evening[2] = {
            "Cleanse to remove sunscreen and daily buildup.",
            "Apply a moisturizer suited to your skin."
        };

        if (skinType == "Oily") {
            morning[1] = "Use a lightweight, non-comedogenic moisturizer.";
        } else if (skinType == "Dry") {
            morning[1] = "Use a moisturizer that supports your skin barrier.";
            evening[1] = "Use a richer moisturizer if your skin feels dry.";
        } else if (skinType == "Sensitive") {
            morning[0] = "Use a gentle cleanser if tolerated.";
            evening[0] = "Cleanse gently with a fragrance-free product if tolerated.";
        } else if (skinType == "Combination") {
            morning[1] = "Use a lightweight moisturizer; adjust to dry areas.";
        }

        string skinNote;

        if (concern == "Acne and bumps") {
            skinNote = "Choose non-comedogenic products and avoid harsh scrubbing. Consider a dermatologist if acne persists.";
        } else if (concern == "Dryness") {
            skinNote = "Focus on gentle cleansing and moisturizing. Glycerin and ceramides may help support the skin barrier.";
        } else if (concern == "Uneven skin tone") {
            skinNote = "Use sunscreen consistently and introduce targeted products gradually.";
        } else if (concern == "Dullness") {
            skinNote = "Keep cleansing, moisturizing and daily sunscreen consistent. Introduce new products slowly.";
        } else {
            skinNote = "Keep the routine simple, choose gentle products and patch-test new products.";
        }

        string budgetTip;

        if (budget <= 500) {
            budgetTip = "Prioritize a cleanser, moisturizer and sunscreen.";
        } else if (budget <= 1000) {
            budgetTip = "Build the basics first, then consider one targeted product.";
        } else if (budget <= 1500) {
            budgetTip = "Maintain the basics before spending on optional extras.";
        } else {
            budgetTip = "A larger budget does not require more products. Choose only what you need.";
        }

        string response =
            "{"
            "\"name\":\"" + jsonEscape(name) + "\","
            "\"skinType\":\"" + jsonEscape(skinType) + "\","
            "\"concern\":\"" + jsonEscape(concern) + "\","
            "\"budget\":" + to_string(budget) + ","
            "\"morning\":" + jsonArray(morning, 3) + ","
            "\"evening\":" + jsonArray(evening, 2) + ","
            "\"skinNote\":\"" + jsonEscape(skinNote) + "\","
            "\"budgetTip\":\"" + jsonEscape(budgetTip) + "\""
            "}";

        res.set_content(response, "application/json");
    });

    cout << "====================================\n";
    cout << "       SkinTwin C++ Backend\n";
    cout << "====================================\n";
    cout << "API address: http://localhost:8080\n";
    cout << "Keep this terminal open while testing.\n";
    cout << "Press Ctrl+C to stop the server.\n\n";
const char* port_env = std::getenv("PORT");
int port = port_env ? std::stoi(port_env) : 8080;

if (!server.listen("0.0.0.0", port)) {
    cerr << "Could not start the server on port "
         << port << ".\n";
    return 1;
}

    return 0;
}
