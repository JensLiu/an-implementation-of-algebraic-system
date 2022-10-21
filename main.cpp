#include <iostream>
#include <string>
#include <cstring>
#include "function.h"
#include "pair.h"
#include "input-parse.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::memcpy;

void testSet();
void testBinaryRelation();
void testFunction();
void lab1Check();

int main() {
    cout << parseToIntPair("<1,1>");
//    testSet();
//    testBinaryRelation();
//    testFunction();
//    lab1Check();
//    Function<char, char> b(_s, _s);
//    cout << b.insert(OrderedPair<char, char>('a', 'a')) << endl;
//    cout << b.insert(OrderedPair<char, char>('a', 'a')) << endl;
//    cout << b.insert(OrderedPair<char, char>('a', 'b')) << endl;
}

void lab1Check() {
//    const int BUFSIZE = 1000;
//    char buf[BUFSIZE];

    cout << "input the domain\tusage: <x1,x2, ... xn>" << endl;
    cout << "Domain = ";
    string input;
    cin >> input;
    Set<int> domain = parseToIntSet(input.c_str());
    cout << "Domain = " << domain << endl << endl;

    cout << "input the codomain\tusage: <x1,x2, ... xn>" << endl;
    cout << "Codomain = ";
    cin >> input;
    Set<int> codomain = parseToIntSet(input.c_str());
    cout << "Codomain = " << codomain << endl << endl;
}

void testSet() {
    Set<char> s;
    cout << s.insert('a') << endl;
    cout << s.insert('b') << endl;
    cout << s.insert('a') << endl;
    cout << s.insert('b') << endl;
    cout << s.remove('a') << endl;
    cout << s.remove('c') << endl;
    cout << s;
}

void testBinaryRelation() {
    Set<char> domain;
    domain.insert('a');
    domain.insert('b');
    domain.insert('c');

    Set<char> codomain;
    codomain.insert('b');
    codomain.insert('c');
    codomain.insert('d');

    BinaryRelation<char, char> binaryRelation(domain, codomain);
    binaryRelation.insert(OrderedPair<char, char>('a', 'b'));
    binaryRelation.insert(OrderedPair<char, char>('a', 'c'));
    binaryRelation.insert(OrderedPair<char, char>('a', 'b'));
    binaryRelation.insert(OrderedPair<char, char>('d', 'e'));
    binaryRelation.remove(OrderedPair<char, char>('a', 'b'));
    binaryRelation.remove(OrderedPair<char, char>('a', 'd'));
    binaryRelation.remove(OrderedPair<char, char>('d', 'e'));
    cout << binaryRelation;

}

void testFunction() {
    Set<char> domain;
    domain.insert('a');
    domain.insert('b');
    domain.insert('c');
    domain.insert('d');
    domain.insert('e');
    Set<char> codomain;
    codomain.insert('f');
    codomain.insert('g');
    codomain.insert('h');

    Function<char, char> function(domain, codomain);
    function.insert(OrderedPair<char, char>('a', 'f'));
    function.insert(OrderedPair<char, char>('b', 'f'));
    function.insert(OrderedPair<char, char>('c', 'g'));
    function.insert(OrderedPair<char, char>('d', 'h'));
    cout << function << endl;
    cout << function.isInjective();
//    cout << function.insert(OrderedPair<char, char>('a', 'a')) << endl;
//    cout << function.insert(OrderedPair<char, char>('a', 'b')) << endl;
//    cout << function << endl;
//    cout << function.insert(OrderedPair<char, char>('e', 'c')) << endl;
//    cout << function << endl;
//    cout << function.remove(OrderedPair<char, char>('a', 'b')) << endl;


}