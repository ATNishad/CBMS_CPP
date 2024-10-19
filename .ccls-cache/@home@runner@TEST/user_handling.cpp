#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void user_Register(vector<string> &users);
void user_LOGIN(vector<string> &users);
void user_View(vector<string> &users);

void user_menu(){
  cout<<"\n";
  cout<<"-----MENU-----\n";
  cout<<"1.REGISTER-new user.\n";
  cout<<"2.LOGIN-existing user.\n";
  cout<<"3.Display users.\n";
  cout<<"4.EXIT.\n";
  cout<<"Enter your choice:";
}

//function to register new user
void user_Register(vector<string> &users){
  string username;
  cout<<"Enter username:";
  getline(cin,username);
  users.push_back(username);
}
void user_LOGIN(vector<string> &users){}
void user_View(vector<string> &users){
  for(auto itr = users.begin(); itr != users.end();){
    cout<<*itr;
    cout<<"\n";
  }
}

int main(){
  int user_choice;
  vector<string> users;
  do{
  user_menu();
  cin>>user_choice;
  cin.ignore();
  switch(user_choice){
    case 1:
    user_Register(users);
    break;
    case 2:
    break;
    case 3:
    user_View(users);
    break;
    case 4:
    break;
    default:
    cout<<"Invalid choice!!";
  }
  }while(user_choice!=4);
}