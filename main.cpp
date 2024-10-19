#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//structures
struct msgstruct {
    string message;
    string timestamp;
    // Constructor
    msgstruct(string a, string b) : message(a), timestamp(b) {}
};
struct user_msg_struct{
string username;
vector<msgstruct> user_and_msg_vec;
//constructor
user_msg_struct(string a,vector<msgstruct> b) : username(a),user_and_msg_vec(b){}
};

//function to display menus
void msg_menu() {
    cout << "\n-----MENU-----\n";
    cout << "1. Send Messages.\n";
    cout << "2. View Messages.\n";
    cout << "3. Edit Message.\n";
    cout << "4. Delete Message.\n";
    cout << "5. Save & Exit.\n";
    cout << "Enter your choice:";
}
void user_menu(){
  cout<<"\n";
  cout<<"-----MENU-----\n";
  cout<<"1.REGISTER-new user.\n";
  cout<<"2.LOGIN-existing user.\n";
  cout<<"3.Display users.\n";
  cout<<"4.EXIT.\n";
  cout<<"Enter your choice:";  
}

//user handling functions
void user_Register(vector<user_msg_struct> &um_vec,vector<msgstruct> &msgvec){
  cout<<"Enter username to register:";
  string username;
  cin.ignore();
  getline(cin,username);
  um_vec.push_back(user_msg_struct(username,msgvec));
}
void user_Login(vector<user_msg_struct> &um_vec,bool &user_logged){
  string checkname;
  cin.ignore();
  while(!user_logged){
  cout<<"Enter your username:";
  getline(cin,checkname);
  user_logged = false;
  for(auto itr = um_vec.begin();itr != um_vec.end();++itr){
    if(itr->username == checkname){
      user_logged=true;
      cout<<"Logged In successfully\n";
      msg_menu();
      break;
    }
    }if(!user_logged){
      cout<<"Failed to login,Try again\n";}
  }
  }
void user_Display(vector<user_msg_struct> um_vec){
  for(auto itr : um_vec){
    cout<<itr.username;
    cout<<",";
  }
}



int main(){
  int user_choice;
  int msg_choice;
  bool user_logged;
  vector<user_msg_struct> um_vec;
  vector<msgstruct> msgvec;
  
  do{
  user_menu();
  cin>>user_choice;
  switch(user_choice){
    case 1:
      user_Register(um_vec,msgvec);
    break;

    case 2:
      user_Login(um_vec,user_logged);
      user_choice = 4;
      cin>>msg_choice;
    break;

    case 3:
      user_Display(um_vec);
    break;

  }
}while(user_choice!=4);
}