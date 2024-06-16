#ifndef KMAP_SOLVER_H
#define KMAP_SOLVER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string toBinary(int number, int width);
int countOnes(const string &s);
bool combine(const string &a, const string &b, string &result);
vector<string> minimizeKMap(int numInputs, const vector<int> &minterms);
string formatImplicant(const string &implicant, int numInputs);

#endif
