#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

void printIntro() {
    cout << "Welcome to the Codename Search!\n";
    cout << "Please enter the name of the file in which the codenames are stored. \n";
}

void updateDatabase(const string &name_in, map<string, vector<string>> &codenames, const string &filename) {
    ofstream fileOut(filename, fstream::app);
   

    string code_in;
    fileOut << "\n(" << name_in << ")";
    cout << "Enter codenames to fill database. Once completed, type \"Q\": \n";

    while (getline(cin, code_in) && code_in != "Q") {
        codenames[name_in].push_back(code_in);
        fileOut << code_in << "\n";
    }

    fileOut.close();
    cout << "Database updated successfully.\n";
}

int main() {
    map<string, vector<string>> codenames;
    string filename;
    printIntro();
    cin >> filename;

    ifstream inputFile(filename);

    /*
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file: " << filename << endl;
        return 1;
    }
    */

   if (!inputFile.is_open()) {
    inputFile.open("fake.txt");
    filename = "fake.txt";
   }

    string inputLine;
    string name = "";

    while (getline(inputFile, inputLine)) {
        if (inputLine.empty()) {
            continue;
        } else if (inputLine[0] == '(') {
            name = inputLine.substr(1, inputLine.length() - 2);
        } else {
            codenames[name].push_back(inputLine);
        }
    }
    inputFile.close();

    string name_in = "";
    while (name_in != "QUIT") {
        cout << "Enter a name to see their codenames or enter \"QUIT\": \n"; 
        cin >> name_in;

        for (char &c : name_in) {
            c = static_cast<char>(toupper(c));
        }

        if (name_in == "QUIT") {
            cout << "Thank you for using this program. Goodbye.\n";
        } else if (codenames.find(name_in) == codenames.end()) {
            string choice;
            cout << "There is no codename recorded for this name. Would you like to add one? (Y/N): ";
            cin >> choice;
            if (choice == "Y" || choice == "y") {
                updateDatabase(name_in, codenames, filename);
            }
        } else {
            cout << "Codenames for " << name_in << ": \n";
            for (const string &element : codenames[name_in]) {
                cout << "  " << element << "\n";
            }
        }
    }

    return 0;
}
