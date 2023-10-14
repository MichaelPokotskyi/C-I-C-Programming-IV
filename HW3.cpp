//
// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// HW2.cpp
// Win10, Visual C++ 2022, ISO C17

// Stream Processing Algorithm implementation

#include <iostream>
#include <sstream>
#include <cctype> // isdigit, toupper
#include <string>
#include <algorithm>  // transform
#include <exception>
using namespace std;

class StreamProcessorAlgorithm {
public:
    //Default Constructor
    StreamProcessorAlgorithm(istream& in, ostream& out) :in_(in), out_(out) {
    }
    virtual ~StreamProcessorAlgorithm() {
    }
    void process();
private:
    virtual bool filterToken(const string& token) const = 0;
    virtual void processToken(string& token) const = 0;
    istream& in_;
    ostream& out_;
};

void StreamProcessorAlgorithm::process() {
    // For each whitespace separated string (token) read from the input stream:
    while (in_) {
        string token;
        //extract input stream in to string
        in_ >> token;
        // If the token passes through the filter
        if (filterToken(token)) {
            // Process the token and output it to the output stream
            processToken(token);
            out_ << token;
        }
    }
}

// Stream Processing Algorithm to Upper Case ALL input tokens
class UppercasingSPA : public StreamProcessorAlgorithm {
public:
    UppercasingSPA(istream& in, ostream& out):StreamProcessorAlgorithm(in, out) {
    }
    ~UppercasingSPA() {
    }
private:
    bool filterToken(const string& token) const {
        // Allows ALL tokens to pass through
        return true;
    }
    void processToken(string& token) const {
        transform(token.begin(), token.end(), token.begin(), toupper);
    }
};

// Stream Processing Algorithm to strip out digits from input token
class DigitStrippingSPA : public StreamProcessorAlgorithm {
public:
    DigitStrippingSPA(istream& in, ostream& out) :StreamProcessorAlgorithm(in, out) {
    }
    ~DigitStrippingSPA() {
    }
private:
    bool filterToken(const string& token) const {
        // Allows tokens containing at least one digit to pass through
        return find_if(token.begin(), token.end(), isdigit) != token.end();
    }
    void processToken(string& token) const {
        // Erase character from string if it is a digit
        token.erase(remove_if(token.begin(), token.end(), isdigit), token.end());
    }
};
// Unit Tests:
void UppercasingSPAConstructor() {
    try {
        UppercasingSPA testSPA(cin, cout);
        clog << "testUppercasingSPAConstructor PASSED\n";
    }
    catch (...) {
        clog << "testUppercasingSPAConstructor FAILED\n";
    }
}
void UppercasingSPADestructor() {
    UppercasingSPA* testSPA = new UppercasingSPA(cin, cout);
    try {
        delete testSPA;
        clog << "testUppercasingSPADestructor PASSED\n";
    }
    catch (...) {
        clog << "testUppercasingSPADestructor FAILED\n";
    }
}
// "standard" input
void UppercasingSPAProcess1() {
    const string TEST_INPUT = "This is my 1st Test!";
    const string VALID_OUTPUT = "THISISMY1STTEST!";
    istringstream testInputStream(TEST_INPUT);
    ostringstream testOutputStream;
    UppercasingSPA testUpper(testInputStream, testOutputStream);
    testUpper.process();
    // Check if expected output is present
    if (testOutputStream.str().compare(VALID_OUTPUT) == 0)
        clog << "testUppercasingSPAProcess1 PASSED\n";
    else
        clog << "testUppercasingSPAProcess1 FAILED : Expected output "
        << VALID_OUTPUT << " instead saw " << testOutputStream.str() << "\n";
}
// non-alpha character input
void UppercasingSPAProcess2() {
    const string TEST_INPUT = "1232$*)(_*1543!";
    const string VALID_OUTPUT = TEST_INPUT;
    istringstream testInputStream(TEST_INPUT);
    ostringstream testOutputStream;
    UppercasingSPA testUpper(testInputStream, testOutputStream);
    testUpper.process();
    // Check if expected output is present
    if (testOutputStream.str().compare(VALID_OUTPUT) == 0)
        clog << "testUppercasingSPAProcess2 PASSED\n";
    else
        clog << "testUppercasingSPAProcess2 FAILED : Expected output "
        << VALID_OUTPUT << " instead saw " << testOutputStream.str() << "\n";
}
void DigitStrippingSPAConstructor() {
    try {
        DigitStrippingSPA testSPA(cin, cout);
        clog << "testDigitStrippingSPAConstructor PASSED\n";
    }
    catch (...) {
        clog << "testDigitStrippingSPAConstructor FAILED\n";
    }
}
void DigitStrippingSPADestructor() {
    DigitStrippingSPA* testSPA = new DigitStrippingSPA(cin, cout);
    try {
        delete testSPA;
        clog << "testDigitStrippingSPADestructor PASSED\n";
    }
    catch (...) {
        clog << "testDigitStrippingSPADestructor FAILED\n";
    }
}
// alpha numeric token
void DigitStrippingSPAProcess1() {
    const string TEST_INPUT = "Th1s 1s my 1st D1g1t T3st";
    const string VALID_OUTPUT = "ThssstDgtTst";
    istringstream testInputStream(TEST_INPUT);
    ostringstream testOutputStream;
    DigitStrippingSPA testSPA(testInputStream, testOutputStream);
    testSPA.process();
    // Check if expected output is present
    if (testOutputStream.str().compare(VALID_OUTPUT) == 0)
        clog << "testDigitStrippingSPAProcess1 PASSED\n";
    else
        clog << "testDigitStrippingSPAProcess1 FAILED : Expected output "
        << VALID_OUTPUT << " instead saw " << testOutputStream.str() << "\n";
}

// non-numeric token
void DigitStrippingSPAProcess2() {
    const string TEST_INPUT = "This is MY second tEst!!$";
    const string VALID_OUTPUT = "";
    istringstream testInputStream(TEST_INPUT);
    ostringstream testOutputStream;
    DigitStrippingSPA testSPA(testInputStream, testOutputStream);
    testSPA.process();
    // Check if expected output is present
    if (testOutputStream.str().compare(VALID_OUTPUT) == 0)
        clog << "DigitStrippingSPAProcess2 test PASSED\n";
    else
        clog << "DigitStrippingSPAProcess2 test FAILED : Expected output "
        << VALID_OUTPUT << " instead saw " << testOutputStream.str() << "\n";
}
int main(void) {
    cout << "\nTesting UppercasingSPA class:\n\n";
    UppercasingSPAConstructor();
    UppercasingSPADestructor();
    UppercasingSPAProcess1();
    UppercasingSPAProcess2();

    cout << "\n\nTesting DigitStrippingSPA class:\n\n";
    DigitStrippingSPAConstructor();
    DigitStrippingSPADestructor();
    DigitStrippingSPAProcess1();
    DigitStrippingSPAProcess2();
}