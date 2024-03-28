/*
 * Program Description: This is a rational number calculator. It takes 2 rational numbers and an operation to perform it.
 *                      Supported operations: Addition, Subtraction, Multiplication, Division.

 * Last Modification Date: 18/3/2024

 * Author1 and ID and Group: Helana Wageh Edward Soltan
 * Author2 and ID and Group: Malak Reda Mohamed Esmail
 * Author3 and ID and Group: Salsabil Bahaaeldin Rohaiem
 */

#include <iostream>
#include <regex>
#include <string>

using namespace std;

// Check if the input format is valid (using regex).
bool isValid(const string& text){
    regex pattern(R"([+-]?\d+/?[+-]?\d+*\s[-+*/]\s[+-]?\d+/?[+-]?\d+*)");
    return regex_match(text, pattern);
}

// The input Rules to be valid input.
void inputRules(){
    cout << "===============================================\n";
    cout << "Please follow these input rules:\n";
    cout << "1) Don't enter a space before the first number.\n";
    cout << "2) Don't enter a space between the numbers of a fraction.\n";
    cout << "3) Don't leave a space between the number and its sign.\n";
    cout << "4) Leave a single space between before and after the operator.\n";
    cout << "5) Don't enter a space after the last number.\n";
    cout << "6) Don't put a zero in the denominator.\n";
    cout << "===============================================\n";
}

// A function to simplify the result.
string simplifyFraction(long long numerator, long long denominator) {

    long long greatestCommonFactor =  __gcd(numerator, denominator);
    numerator /= greatestCommonFactor;
    denominator /= greatestCommonFactor;

    if (numerator > 0 && denominator < 0){
        numerator *= (-1);
        denominator *= (-1);
    }

    string numSimplified;
    if (denominator == 1) {
        numSimplified = to_string(numerator);
        return numSimplified;
    }
    numSimplified = to_string(numerator) + "/" + to_string(denominator);
    return numSimplified;
}

// A function to add 2 fractions.
string addition(long long numerator1, long long denominator1, long long numerator2, long long denominator2){

    string result;
    long long numerator = (numerator1 * denominator2) + (numerator2 * denominator1);
    long long denominator = denominator1 * denominator2;

    if (numerator != 0) {
        result = simplifyFraction(numerator, denominator);
        return result;
    }
    else
        return "0";
}

// A function to subtract 2 fractions.
string subtraction(long long numerator1, long long denominator1, long long numerator2, long long denominator2){

    string result;
    long long numerator = (numerator1 * denominator2) - (numerator2 * denominator1);
    long long denominator = denominator1 * denominator2;
    result = simplifyFraction(numerator, denominator);

    if (numerator != 0) {
        result = simplifyFraction(numerator, denominator);
        return result;
    }
    else
        return "0";
}

// A function to multiply 2 fractions.
string multiplication(long long numerator1, long long denominator1, long long numerator2, long long denominator2){

    long long numerator = numerator1 * numerator2;
    long long denominator = denominator1 * denominator2;
    string result = simplifyFraction(numerator, denominator);

    return result;
}

// A function to divide 2 fractions.
string division(long long numerator1, long long denominator1, long long numerator2, long long denominator2){

    long long numerator = numerator1 * denominator2;
    long long denominator = numerator2 * denominator1;
    string result = simplifyFraction(numerator, denominator);

    return result;
}

int main() {

    while (true) {
        string input;
        string numerator1, numerator2, denominator1, denominator2;
        char operation;
        bool isFraction1 = false;
        bool isFraction2 = false;

        inputRules(); // Display the input rules.
        string choice;
        cout << "Do you want to calculate or exit the program? (Choose 1 or 2)\n";
        cout << "1) Calculate.\n";
        cout << "2) Exit the program.\n";
        cin >> choice;
        cin.ignore();

        // If the user chose to Calculate a number.
        if (choice == "1") {

            // Get the input from the user.
            cout << "Enter 2 rational numbers with an operator between them.\n";
            getline(cin, input);
            if (isValid(input)) {
                int index; // A variable used as a checkpoint in the input string.

                // A loop to extract the first numerator.
                for (int i = 0; i < input.size(); ++i) {
                    if (input[i] == '/') {
                        isFraction1 = true;
                        index = i + 1;
                        break;
                    } else if (input[i] == ' ') {
                        index = i + 1;
                        break;
                    } else {
                        numerator1 += input[i];
                    }
                }

                // A loop to extract the first denominator (if exists).
                if (isFraction1) {
                    // Reject the input if the denominator = 0.
                    if ((input[index] == '0' && input[index + 1] == ' ') || ((input[index] == '+' || input[index] == '-') && input[index + 1] == '0')){
                        cout << "Invalid input. You can't divide by 0." << endl;
                        continue;
                    }
                    for (int i = index; i < input.size(); ++i) {
                        if (isspace(input[i])) {
                            index = i + 1;
                            break;
                        } else {
                            denominator1 += input[i];
                        }
                    }
                } else {
                    denominator1 = "1";
                }

                // To extract the operation used.
                operation = input[index];
                index += 2;
                if (operation == '/') {
                    if (input[index] == '0') { // Reject the input if the denominator = 0.
                        cout << "Invalid input. You can't divide by 0." << endl;
                        continue;
                    }
                }

                // A loop to extract the second numerator.
                for (int i = index; i < input.size(); ++i) {
                    if (input[i] == '/') {
                        isFraction2 = true;
                        index = i + 1;
                        break;
                    } else if (input[i] == ' ' || i == input.size()) {
                        break;
                    } else {
                        numerator2 += input[i];
                    }
                }

                // A loop to extract the second denominator (if exists).
                if (isFraction2) {
                    // Reject the input if the denominator = 0.
                    if ((input[index] == '0' && input[index + 1] == ' ') || ((input[index] == '+' || input[index] == '-') && input[index + 1] == '0')){
                        cout << "Invalid input. You can't divide by 0." << endl;
                        continue;
                    }
                    for (int i = index; i < input.size(); ++i) {
                        denominator2 += input[i];
                    }
                } else { // If the number is an integer, put denominator = 1.
                    denominator2 = "1";
                }

                // Convert the numbers from strings to integers.
                long long numeratorInt1 = stoll(numerator1);
                long long denominatorInt1 = stoll(denominator1);
                long long numeratorInt2 = stoll(numerator2);
                long long denominatorInt2 = stoll(denominator2);

                // Calculate and display the result.
                switch (operation) {
                    case '+':
                        cout << "The result = " << addition(numeratorInt1, denominatorInt1, numeratorInt2, denominatorInt2) << endl;
                        break;
                    case '-':
                        cout << "The result = " << subtraction(numeratorInt1, denominatorInt1, numeratorInt2, denominatorInt2) << endl;
                        break;
                    case '*':
                        cout << "The result = " << multiplication(numeratorInt1, denominatorInt1, numeratorInt2, denominatorInt2) << endl;
                        break;
                    case '/':
                        cout << "The result = " << division(numeratorInt1, denominatorInt1, numeratorInt2, denominatorInt2) << endl;
                        break;
                    default:
                        cout << "Invalid operation." << endl;
                }

            } else { // If the user didn't follow the input rules.
                cout << "Invalid input. Please follow the input rules.\n";
            }

        } else if (choice == "2") { // If the user chose to exit the program.
            cout << "Exiting the program. Bye!" << endl;
            break;

        } else { // If the user entered a choice rather than 1 and 2.
            cout << "Please enter a valid choice (1 or 2)." << endl;
        }
    }

    return 0;
    }
