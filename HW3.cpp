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
#include <string>
#include <algorithm>
using namespace std;

class StreamProcessorAlgorithm {
public:
    // constructor
    StreamProcessorAlgorithm(istream& in, ostream& out) :in_(in), out_(out) {
    }
    // destructor
    virtual ~StreamProcessorAlgorithm() {
    }
    void process();
private:
    virtual bool filterToken(const string& token) const = 0;
    virtual void processToken(string& token) const = 0;
    istream& in_; // input stream by reference
    ostream& out_; // output stream by reference
};
void StreamProcessorAlgorithm::process() {
    // for each whitespace separated string (token) read from the input stream:
    while (in_) {
        string token;
        in_ >> token;
        // if the token passes through the filter (filterToken() returns TRUE)
        if (filterToken(token)) {
            // process the token and output it to the output stream
            processToken(token);
            out_ << token;
        }
    }
}
// UppercasingSPA 
class UppercasingSPA : public StreamProcessorAlgorithm {
public:
    // constructor
    UppercasingSPA(istream& in, ostream& out):StreamProcessorAlgorithm(in, out) {
    }
    // destructor
    ~UppercasingSPA() {
    }
private:
    bool filterToken(const string& token) const {
        // all tokens will pass
        return true;
    }
    void processToken(string& token) const {
        // all to uppercase
        transform(token.begin(), token.end(), token.begin(), toupper);
    }
};
// DigitStrippingSPA
class DigitStrippingSPA : public StreamProcessorAlgorithm {
public:
    // constructor
    DigitStrippingSPA(istream& in, ostream& out) :StreamProcessorAlgorithm(in, out) {
    }
    // destructor
    ~DigitStrippingSPA() {
    }
private:
    bool filterToken(const string& token) const {
        // at least one digit to pass
        return find_if(token.begin(), token.end(), isdigit) != token.end();
    }
    void processToken(string& token) const {
        // remove digits from string
        token.erase(remove_if(token.begin(), token.end(), isdigit), token.end());
    }
};
//**********//
//All tests://
void UppercasingSPAConstructor() {
    try {
        UppercasingSPA testSPA(cin, cout);
        clog << "UppercasingSPAConstructor test PASSED\n";
    }
    catch (...) {
        clog << "UppercasingSPAConstructor test FAILED\n";
    }
}
void UppercasingSPADestructor() {
    UppercasingSPA* testSPA = new UppercasingSPA(cin, cout);
    try {
        delete testSPA;
        clog << "UppercasingSPADestructor test PASSED\n";
    }
    catch (...) {
        clog << "UppercasingSPADestructor test FAILED\n";
    }
}
void UppercasingSPAProcessOne() {
    const string TEST_INPUT = "this is a test string";
    const string VALID_OUTPUT = "THISISATESTSTRING";
    istringstream testInputStream(TEST_INPUT);
    ostringstream testOutputStream;
    UppercasingSPA testUpper(testInputStream, testOutputStream);
    testUpper.process();
    if (testOutputStream.str().compare(VALID_OUTPUT) == 0)
        clog << "UppercasingSPAProcessOne test PASSED\n";
    else
        clog << "UppercasingSPAProcessOne test FAILED -> Expected output "
        << VALID_OUTPUT << " but instead have " << testOutputStream.str() << "\n";
}
void UppercasingSPAProcessTwo() {
    const string TEST_INPUT = "1234567890!?()*&_+=abcdef";
    const string VALID_OUTPUT = "1234567890!?()*&_+=ABCDEF";
    istringstream testInputStream(TEST_INPUT);
    ostringstream testOutputStream;
    UppercasingSPA testUpper(testInputStream, testOutputStream);
    testUpper.process();
    if (testOutputStream.str().compare(VALID_OUTPUT) == 0)
        clog << "UppercasingSPAProcessTwo test PASSED\n";
    else
        clog << "UppercasingSPAProcessTwo test FAILED -> Expected output "
        << VALID_OUTPUT << " but instead have " << testOutputStream.str() << "\n";
}
void DigitStrippingSPAConstructor() {
    try {
        DigitStrippingSPA testSPA(cin, cout);
        clog << "DigitStrippingSPAConstructor test PASSED\n";
    }
    catch (...) {
        clog << "DigitStrippingSPAConstructor test FAILED\n";
    }
}
void DigitStrippingSPADestructor() {
    DigitStrippingSPA* testSPA = new DigitStrippingSPA(cin, cout);
    try {
        delete testSPA;
        clog << "DigitStrippingSPADestructor test PASSED\n";
    }
    catch (...) {
        clog << "DigitStrippingSPADestructor test FAILED\n";
    }
}
void DigitStrippingSPAProcessOne() {
    const string TEST_INPUT = "0String 0with 0zero 0append 0to 0each 0word and no zero word.";
    const string VALID_OUTPUT = "Stringwithzeroappendtoeachword";
    istringstream testInputStream(TEST_INPUT);
    ostringstream testOutputStream;
    DigitStrippingSPA testSPA(testInputStream, testOutputStream);
    testSPA.process();
    if (testOutputStream.str().compare(VALID_OUTPUT) == 0)
        clog << "DigitStrippingSPAProcessOne test PASSED\n";
    else
        clog << "DigitStrippingSPAProcessOne test FAILED -> Expected output "
        << VALID_OUTPUT << " but instead have" << testOutputStream.str() << "\n";
}
void DigitStrippingSPAProcessTwo() {
    const string TEST_INPUT = "0String1 0with2 0zero3 0append4 0to5 0each6 0word7 and no zero word.";
    const string VALID_OUTPUT = "Stringwithzeroappendtoeachword";
    istringstream testInputStream(TEST_INPUT);
    ostringstream testOutputStream;
    DigitStrippingSPA testSPA(testInputStream, testOutputStream);
    testSPA.process();
    if (testOutputStream.str().compare(VALID_OUTPUT) == 0)
        clog << "DigitStrippingSPAProcessTwo test PASSED\n";
    else
        clog << "DigitStrippingSPAProcessTwo test FAILED -> Expected output "
        << VALID_OUTPUT << " but instead have " << testOutputStream.str() << "\n";
}
int main(void) {
    // running test cases
    cout << "Testing UppercasingSPA class:\n";
    UppercasingSPAConstructor();
    UppercasingSPADestructor();
    UppercasingSPAProcessOne();
    UppercasingSPAProcessTwo();
    cout << "\n\nTesting DigitStrippingSPA class:\n";
    DigitStrippingSPAConstructor();
    DigitStrippingSPADestructor();
    DigitStrippingSPAProcessOne();
    DigitStrippingSPAProcessTwo();
}