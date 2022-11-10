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
void lab1Check();
void testOperation();
void groupCheck();
void groupTest();

int main() {
    groupTest();
//    groupCheck();
//    testOperation();

//    string s = "{,<123,-1>,<123,-1>,}";
//    Set<OrderedPair<int, int>> set = parseToIntPairSet(s.c_str());
//    cout << set;

//    cout << parseToIntPair("<1,1>");
//    testSet();
//    testFunction();
//    testBinaryRelation();
//    testFunction();
//    lab1Check();
//    BinaryFunction<char, char> b(_s, _s);
//    cout << b.insert(OrderedPair<char, char>('a', 'a')) << endl;
//    cout << b.insert(OrderedPair<char, char>('a', 'a')) << endl;
//    cout << b.insert(OrderedPair<char, char>('a', 'b')) << endl;
}

void groupTest() {

    Set<int> s;
    s.insert(0);
    s.insert(60);
    s.insert(120);
    s.insert(180);
    s.insert(240);
    s.insert(300);

    AlgebraicSystem<int> as(s);
    using t_triple = Triple<int, int, int>;
    as.alter(t_triple (0,0,0));
    as.alter(t_triple (0,60,60));
    as.alter(t_triple (0,120,120));
    as.alter(t_triple (0,180,180));
    as.alter(t_triple (0,240,240));
    as.alter(t_triple (0,300,300));

    as.alter(t_triple (60,0,60));
    as.alter(t_triple (60,60,120));
    as.alter(t_triple (60,120,180));
    as.alter(t_triple (60,180,240));
    as.alter(t_triple (60,240,300));
    as.alter(t_triple (60,300,0));

    as.alter(t_triple (120,0,120));
    as.alter(t_triple (120,60,180));
    as.alter(t_triple (120,120,240));
    as.alter(t_triple (120,180,300));
    as.alter(t_triple (120,240,0));
    as.alter(t_triple (120,300,60));

    as.alter(t_triple (180,0,180));
    as.alter(t_triple (180,60,240));
    as.alter(t_triple (180,120,300));
    as.alter(t_triple (180,180,0));
    as.alter(t_triple (180,240,60));
    as.alter(t_triple (180,300,120));

    as.alter(t_triple (180,0,180));
    as.alter(t_triple (180,60,240));
    as.alter(t_triple (180,120,300));
    as.alter(t_triple (180,180,0));
    as.alter(t_triple (180,240,60));
    as.alter(t_triple (180,300,120));

    as.alter(t_triple (240,0,240));
    as.alter(t_triple (240,60,300));
    as.alter(t_triple (240,120,0));
    as.alter(t_triple (240,180,60));
    as.alter(t_triple (240,240,120));
    as.alter(t_triple (240,300,180));

    as.alter(t_triple (300,0,300));
    as.alter(t_triple (300,60,0));
    as.alter(t_triple (300,120,60));
    as.alter(t_triple (300,180,120));
    as.alter(t_triple (300,240,180));
    as.alter(t_triple (300,300,240));

    cout << as << endl;

    int i;
    if (as.nullElement(i)) {
        cout << "null " << i << endl;
    }
    if (as.identityElement(i)) {
        cout << "identity element:" << i << endl;
    }
    for (auto idem : as.idempotentElements()) {
        cout << "idempotent element:" << idem << endl;
    }
    for (auto elem : as.getElements()) {
        int inverse;
        if (as.inverseElement(elem, inverse)) {
            cout << elem << " inverse element: " << inverse << endl;
        }
    }
    if (as.isClosed()) {
        cout << "closed" << endl;
    } else {
        cout << "not closed" << endl;
    }
    if (as.isAssociative()) {
        cout << "associative" << endl;
    } else {
        cout << "not associative" << endl;
    }
    if (as.isCommutative()) {
        cout << "commutative" << endl;
    } else {
        cout << "not commutative" << endl;
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

void lab1Check() {

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



}

void testSet() {
    Set<char> s;
    cout << "insert 'a' " << s.insert('a') << endl;
    cout << s << endl;
    cout << "insert 'b' " << s.insert('b') << endl;
    cout << s << endl;
    cout << "insert 'a' " << s.insert('a') << endl;
    cout << s << endl;
    cout << "insert 'b' " << s.insert('b') << endl;
    cout << s << endl;
    cout << "remove 'a' " << s.remove('a') << endl;
    cout << s << endl;
    cout << "remove 'c' " << s.remove('c') << endl;
    cout << s << endl;
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

//void testOperation() {
//    Set<char> domain;
//    domain.insert('a');
//    domain.insert('b');
//    domain.insert('c');
//
//    Set<char> codomain;
//    codomain.insert('d');
//    codomain.insert('e');
//    codomain.insert('f');
//
//    Triple<char, char, char> t11('a', 'a', 'd');
//    Triple<char, char, char> t12('a', 'b', 'e');
//    Triple<char, char, char> t13('a', 'c', 'f');
//
//    Triple<char, char, char> t21('b', 'a', 'e');
//    Triple<char, char, char> t22('b', 'b', 'd');
//    Triple<char, char, char> t23('b', 'c', 'f');
//
//    Triple<char, char, char> t31('c', 'a', 'f');
//    Triple<char, char, char> t32('c', 'b', 'e');
//    Triple<char, char, char> t33('c', 'c', 'e');
//
//    Set<OrderedPair<char, char>> set = BinaryOperation<char, char>::getDomainCartesianProduct(domain);
////    cout << set;
//    BinaryOperation<char, char> binaryOperation(set, codomain);
////    binaryOperation.insertSafely(t11);
//
//
////    BinaryOperation<char, char, char> operation();
//}