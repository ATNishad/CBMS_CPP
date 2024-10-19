#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

namespace user_handling{
void user_Register(vector<string> &usersvec);
void user_Login(vector<string> &usersvec);
void user_View(vector<string> &usersvec);

//user menu
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
void user_Register(vector<string> &usersvec){
  string username;
  cout<<"Enter username:";
  getline(cin,username);
  usersvec.push_back(username);
  cout<<"User "<<"["<<username<<"]"<<" registered successfully!";
}
//function to login
void user_Login(vector<string> &usersvec,bool &user_logged){
  string username;
  cin.ignore();
  cout<<"Enter your username:";
  getline(cin,username);
  for(auto itr_user : usersvec){
    if(itr_user == username){
      user_logged = true;
      cout<<"Logged in successfully!!\n";
      return;
    }
  }
    user_logged = false;
    cout<<"Can\'t Login!,Check username\n";
  }
//function to list users
void user_View(vector<string> &usersvec){
  for(auto itr : usersvec){
    cout<<itr;
    cout<<"\n";
  }
}

}

//user_handling main
int main(){
  int user_choice;
  bool user_Logged;
  vector<string> usersvec;
  do{
  user_handling::user_menu();
  cin>>user_choice;
  cin.ignore();
  switch(user_choice){
    case 1:
    user_handling::user_Register(usersvec);
    break;

    case 2:
    user_handling::user_Login(usersvec,user_Logged);
    break;

    case 3:
    user_handling::user_View(usersvec);
    break;

    case 4:
    break;

    default:
    cout<<"Invalid choice!!";
  }
  }while(user_choice!=4);
}


/*struct user_n_msg{
string username;
vector<msg_handling::msgstruct> user_and_msg_vec;
};*/