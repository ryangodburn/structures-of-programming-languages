// FORTH Lexer Implementation
// Ryan Godburn and Matthew Williams
// A lexical analyzer for FORTH programming language

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <iomanip>

using namespace std;

// ============================================================
// Type Definitions
// ============================================================

// Enumeration for different token types in FORTH
enum TokenType {
    WORD,      // General FORTH words/commands
    NUMBER,    // Numeric literals (all digits)
    STRING     // String literals (enclosed in quotes)
};

// Enumeration for lexer state machine states
enum StateType {
    START,              // Initial state, ready for new token
    DONE,              // Processing complete
    ACQUIRING_TOKEN,   // Building a token character by character
    ACQUIRING_COMMENT, // Processing a comment
    ACQUIRING_STRING,  // Processing a string literal
    SLASH_PENDING,     // Saw '\', checking for comment
    PAREN_PENDING,     // Saw '(', checking for comment
    ACQUIRING_SLASH,   // Processing line comment
    ACQUIRING_PAREN    // Processing parenthetical comment
};

// ============================================================
// Token Class
// ============================================================

class Token {
private:
    string name;           // The actual token text
    TokenType type;        // Type of the token
    int referenceCount;    // Number of occurrences

public:
    // Constructor initializes token with name and type
    Token(const string& tokenName, TokenType tokenType) 
        : name(tokenName), type(tokenType), referenceCount(1) {
    }

    // Print token information in a formatted table row
    void print(ofstream& output) const {
        // Convert type enum to readable string
        string typeStr;
        switch(type) {
            case WORD:   typeStr = "WORD";   break;
            case NUMBER: typeStr = "NUMBER"; break;
            case STRING: typeStr = "STRING"; break;
        }
        
        // Output in neat columns: name, type, count
        output << left << setw(20) << name 
               << setw(10) << typeStr 
               << setw(5) << referenceCount << endl;
    }

    // Increment the occurrence counter for this token
    void incrementCounter() {
        referenceCount++;
    }

    // Getter for token name (needed for map operations)
    string getName() const { return name; }
};

// ============================================================
// Lexer Class
// ============================================================

class Lexer {
private:
    StateType state;              // Current state machine state
    ifstream inputFile;           // Input source file
    ofstream outputFile;          // Output results file
    map<string, Token> tokenMap;  // Symbol table
    char currentChar;             // Current character being read
    string tokenString;           // Token being built
    TokenType currentTokenType;   // Type of current token
    string inputFileName;         // Name of input file

public:
    // Constructor opens files and initializes lexer
    Lexer(const string& fileName) 
        : state(START), tokenString(""), inputFileName(fileName) {
        
        // Open input file for reading
        inputFile.open(fileName);
        if (!inputFile) {
            cerr << "Error: Cannot open input file " 
                 << fileName << endl;
            exit(1);
        }

        // Create output filename by adding .out extension
        string outFileName = "output.txt";
        outputFile.open(outFileName);
        if (!outputFile) {
            cerr << "Error: Cannot create output file " 
                 << outFileName << endl;
            exit(1);
        }

        // Write header information to output file
        outputFile << "FORTH Lexer Output" << endl;
        outputFile << "Assignment 3" << endl;
        outputFile << "By: Ryan Godburn & Matthew Williams" << endl;
        outputFile << "Input File: " << fileName << endl;
        outputFile << endl << "Comments:" << endl;
        outputFile << "---------" << endl;
    }

    // Destructor closes files
    ~Lexer() {
        if (inputFile.is_open()) {
            inputFile.close();
        }
        if (outputFile.is_open()) {
            outputFile.close();
        }
    }

    // Main lexing function - implements state machine
    void doLex() {
        // Process input character by character until EOF
        while (inputFile.get(currentChar)) {
            
            // State machine switch
            switch (state) {
                case START:
                    doStart();
                    break;
                    
                case SLASH_PENDING:
                    // Check if backslash starts a comment
                    if (isspace(currentChar)) {
                        state = ACQUIRING_SLASH;
                    } else {
                        // Not a comment, treat as token
                        state = ACQUIRING_TOKEN;
                    }
                    break;
                    
                case ACQUIRING_SLASH:
                    // Process line comment until newline
                    outputFile << currentChar;
                    while (currentChar != '\n' && 
                           inputFile.get(currentChar)) {
                        outputFile << currentChar;
                    }
                    outputFile << endl;
                    state = START;
                    break;
                    
                case PAREN_PENDING:
                    // Check if parenthesis starts a comment
                    if (isspace(currentChar)) {
                        state = ACQUIRING_PAREN;
                    } else {
                        // Not a comment, treat as token
                        state = ACQUIRING_TOKEN;
                    }
                    break;
                    
                case ACQUIRING_PAREN:
                    // Process paren comment until ')'
                    outputFile << "( ";
                    while (currentChar != ')' && 
                           inputFile.get(currentChar)) {
                        outputFile << currentChar;
                    }
                    outputFile << " )" << endl;
                    state = START;
                    break;
                    
                case ACQUIRING_TOKEN:
                    // Build token until whitespace
                    while (!isspace(currentChar)) {
                        tokenString += currentChar;
                        if (!inputFile.get(currentChar)) {
                            break;
                        }
                    }
                    
                    // Determine token type and process
                    if (isAllDigits(tokenString)) {
                        doToken(tokenString, NUMBER);
                    } else if (tokenString == ".\"") {
                        // Start of string literal
                        doToken(tokenString, WORD);
                        state = ACQUIRING_STRING;
                        tokenString = "";
                        continue;  // Don't reset to START
                    } else {
                        doToken(tokenString, WORD);
                    }
                    state = START;
                    break;
                    
                case ACQUIRING_STRING:
                    // Read string until closing quote
                    while (inputFile.get(currentChar) && 
                           currentChar != '"') {
                        tokenString += currentChar;
                    }
                    doToken(tokenString, STRING);
                    state = START;
                    break;
                    
                default:
                    break;
            }
        }
    }

    // Print the symbol table to output file
    void print() {
        outputFile << endl;
        outputFile << "--------------------------------" << endl;
        outputFile << "Symbol Table:" << endl;
        outputFile << "--------------------------------" << endl;
        outputFile << left << setw(20) << "Token" 
                   << setw(10) << "Type" 
                   << setw(5) << "Count" << endl;
        outputFile << "--------------------------------" << endl;
        
        // Print each token in the map
        for (auto& pair : tokenMap) {
            pair.second.print(outputFile);
        }
    }

private:
    // Helper: Process identified token
    void doToken(const string& name, TokenType tt) {
        // Search for existing token in map
        auto iter = tokenMap.find(name);
        
        if (iter != tokenMap.end()) {
            // Token exists, increment counter
            iter->second.incrementCounter();
        } else {
            // New token, add to map
            Token temp(name, tt);
            tokenMap.insert(make_pair(name, temp));
        }
        
        // Clear token string for next token
        tokenString = "";
    }

    // Helper: Handle START state logic
    void doStart() {
        if (isspace(currentChar)) {
            // Skip whitespace
            return;
        } else if (currentChar == '\\') {
            // Potential line comment
            state = SLASH_PENDING;
        } else if (currentChar == '(') {
            // Potential parenthetical comment
            state = PAREN_PENDING;
        } else {
            // Start of a regular token
            state = ACQUIRING_TOKEN;
            tokenString += currentChar;
        }
    }

    // Helper: Check if string contains only digits
    bool isAllDigits(const string& str) {
        if (str.empty()) return false;
        
        for (char ch : str) {
            if (!isdigit(ch)) {
                return false;
            }
        }
        return true;
    }
};

// ============================================================
// Main Program
// ============================================================

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    // Create lexer instance with input filename
    Lexer lexer(argv[1]);
    
    // Process the input file
    cout << "Processing file: " << argv[1] << endl;
    lexer.doLex();
    
    // Output the symbol table
    lexer.print();
    
    cout << "Lexical analysis complete." << endl;
    cout << "Results written to: " << argv[1] << ".txt" << endl;
    
    return 0;
}