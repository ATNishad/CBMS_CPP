#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

// Function prototype
const string timer();

// Message structure
struct msgstruct {
  string message;
  string timestamp;
  // Constructor
  msgstruct(string a, string b) : message(a), timestamp(b) {}
};

// Function declarations
void sendmsg(vector<msgstruct> &msgvec);
void viewmsg(const vector<msgstruct> &msgvec);
void savemsg(const vector<msgstruct> &msgvec);
void loadmsg(vector<msgstruct> &msgvec);
void editmsg(vector<msgstruct> &msgvec);
void menu();

#endif // MESSAGE_MANAGER_H
