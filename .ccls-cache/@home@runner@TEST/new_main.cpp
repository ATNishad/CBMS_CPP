#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct msgstruct {
    string message;
    string timestamp;
    // Constructor
    msgstruct(string a, string b) : message(a), timestamp(b) {}
};
struct user_msgStruct{
string username;
vector<msgstruct> user_and_msg_vec;
};

void user_menu(){
  cout<<"\n";
  cout<<"-----MENU-----\n";
  cout<<"1.REGISTER-new user.\n";
  cout<<"2.LOGIN-existing user.\n";
  cout<<"3.Display users.\n";
  cout<<"4.EXIT.\n";
  cout<<"Enter your choice:";  
}
void user_Register(){
  string username;
  cout<<"Enter username:";
  getline(cin,username);
  usersvec.push_back(username);
  cout<<"User "<<"["<<username<<"]"<<" registered successfully!";
}

int main(){
  int user_choice;
  vector<user_msgStruct> um_vec;
  do{
  user_menu();
  cin>>user_choice;
  switch(user_choice){
    
    case 1:
    user_Register();
    break;
  }
}
    }