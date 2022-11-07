#include <iostream>
#include <string>
#include <cstring>
#include "binary-function.h"
#include "pair.h"
#include "triple.h"
#include "input-parse.h"
//#include "binary-operation.h"
#include "algebraic-system-with-single-binary-operation.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::memcpy;

void testSet();
void testBinaryRelation();
void testFunction();
void functionCheck();
void testOperation();
void groupCheck();

int main() {
    functionCheck();
}

void functionCheck() {
    cout << "*** Function Check ***" << endl;
    cout << "input the domain\tusage: {x1,x2, ... xn}" << endl;
    cout << "Domain = ";
    string input;
    cin >> input;
    Set<int> domain = parseToIntSet(input.c_str());
    cout << "Domain = " << domain << endl << endl;

    cout << "input the codomain\tusage: {x1,x2, ... xn}" << endl;
    cout << "Codomain = ";
    cin >> input;
    Set<int> codomain = parseToIntSet(input.c_str());
    cout << "Codomain = " << codomain << endl << endl;

    cout << "input the relation on\ndomain: " << domain << "\ncodomain: " << codomain << "\n"
            "usage: {<x1,y1>,<x2,y2>, ... <xn,xn>}" << endl;
    cout << "relation = ";
    cin >> input;
    Set<OrderedPair<int, int>> pairSet = parseToIntPairSet(input.c_str());
    BinaryRelation<int, int> relation(domain, codomain);
    for (auto p : pairSet.getElements()) {
        relation.insert(p);
    }
    cout << "relation: " << endl << relation << endl;
    BinaryFunction<int, int> function(relation);
    if (function.isFunction()) {
        cout << "is a function" << endl;
        int isInjective = function.isInjective();
        int isSurjective = function.isSurjective();
        if (isInjective && isSurjective) {
            cout << "is bijective" << endl;
        } else if (isInjective) {
            cout << "is injective, not surjective" << endl;
        } else if (isSurjective){
            cout << "is surjective, not injective" << endl;
        }
    } else {
        cout << "is not a function" << endl;
    }

}

void groupCheck() {
    cout << "*** Group Check ***" << endl;
    cout << "set: [usage: {x1, x2, ..., }]" << endl;
    string input;
    cin >> input;
    Set<int> s = parseToIntSet(input.c_str());


    AlgebraicSystem<int> as(s);
    cout << "define algebraic system on set " << s << endl;
    std::vector<int> v = s.getVector();
    for (int x : v) {
        for (int y : v) {
            cout << "<" << x << ", " << y << ">: ";
            int z;
            cin >> z;
            as.alter(Triple<int, int, int>(x, y, z));
        }
    }
    cout << endl << as << endl;

    if (!as.isClosed()) {
        cout << "not closed" << endl;
    } else {
        cout << "closed" << endl;
        if (!as.isSemigroup()) {
            cout << "is not semigroup" << endl;
        } else {
            cout << "is semigroup" << endl;
            if (!as.isMonoid())  {
                cout << "is not monoid" << endl;
            } else {
                int identity;
                as.identityElement(identity);
                cout << "is monoid, identity element " << identity << endl;
                if (!as.isGroup()) {
                    cout << "is not group" << endl;
                } else {
                    cout << "is group" << endl;
                }
            }
        }

    }



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

    BinaryRelation<char, char> relation(domain, codomain);
    relation.insert(OrderedPair<char, char>('a', 'f'));
    relation.insert(OrderedPair<char, char>('b', 'f'));
    relation.insert(OrderedPair<char, char>('c', 'f'));
    relation.insert(OrderedPair<char, char>('d', 'f'));
    relation.insert(OrderedPair<char, char>('e', 'f'));
//    relation.insert(OrderedPair<char, char>('e', 'h'));


    cout << relation << endl;
    BinaryFunction<char, char> function(relation);
    cout << function;
//    cout << function.isInjective();
//    cout << function.insert(OrderedPair<char, char>('a', 'a')) << endl;
//    cout << function.insert(OrderedPair<char, char>('a', 'b')) << endl;
//    cout << function << endl;
//    cout << function.insert(OrderedPair<char, char>('e', 'c')) << endl;
//    cout << function << endl;
//    cout << function.remove(OrderedPair<char, char>('a', 'b')) << endl;


}

void testOperation() {
    Set<char> domain;
    domain.insert('a');
    domain.insert('b');
    domain.insert('c');

    Set<char> codomain;
    codomain.insert('d');
    codomain.insert('e');
    codomain.insert('f');

    Triple<char, char, char> t11('a', 'a', 'd');
    Triple<char, char, char> t12('a', 'b', 'e');
    Triple<char, char, char> t13('a', 'c', 'f');

    Triple<char, char, char> t21('b', 'a', 'e');
    Triple<char, char, char> t22('b', 'b', 'd');
    Triple<char, char, char> t23('b', 'c', 'f');

    Triple<char, char, char> t31('c', 'a', 'f');
    Triple<char, char, char> t32('c', 'b', 'e');
    Triple<char, char, char> t33('c', 'c', 'e');

//    Set<OrderedPair<char, char>> set = BinaryOperation<char, char>::getDomainCartesianProduct(domain);
//    cout << set;
//    BinaryOperation<char, char> binaryOperation(set, codomain);
//    binaryOperation.insertSafely(t11);


//    BinaryOperation<char, char, char> operation();
}