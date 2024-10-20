#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

struct message {
  string sender;
  string content;
  string timestamp;

  void set_sender(string &name) { this->sender = name; }
  void set_content(string &content) { this->content = content; }
  void set_timestamp(string &timestamp) { this->timestamp = timestamp; }
};

const string timer() {
  const auto now = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(now);
  string timestamp = std::ctime(&t);
  timestamp.pop_back();
  return timestamp;
}

void user_menu() {
  cout << "\n";
  cout << "-----MENU-----\n";
  cout << "1.REGISTER-new user.\n";
  cout << "2.LOGIN-existing user.\n";
  cout << "3.Display users.\n";
  cout << "4.EXIT.\n";
  cout << "Enter your choice:";
}
void msg_menu() {
  cout << "\n-----MENU-----\n";
  cout << "1. Send Messages.\n";
  cout << "2. View Messages.\n";
  cout << "3. Edit Message.\n";
  cout << "4. Delete Message.\n";
  cout << "5. Save & Exit.\n";
  cout << "Enter your choice: ";
}

void user_register(vector<message> &UM_VEC, message &msgObject) {
  string username;
  cout << "Enter name to register:";
  getline(cin, username);
  msgObject.set_sender(username);
  UM_VEC.push_back(msgObject);
}
void user_login(vector<message> &UM_VEC, bool &global_user_logged,string &logged_user) {
  string username;
  bool logged_in = false;
  do {
    cout << "Enter username to login:";
    getline(cin, username);
    for (auto &itr : UM_VEC) {
      if (itr.sender == username) {
        logged_in = true;
        logged_user=username;
        global_user_logged = true;
        cout << "Logged in successfully!!\n";
        break;
      }
    }
    if (!logged_in) {
      cout << "Failed to Login, Try Again!\n";
    }
  } while (!logged_in);
}
void user_display(vector<message> UM_VEC) {
  for (auto itr : UM_VEC) {
    cout << itr.sender;
    cout << ",";
  }
  cout << "\n";
}

void send_msg(vector<message> &UM_VEC,message &msgObject,string logged_user){
  string content;
  cout<<"Enter message to sent:";
  cin.ignore();
  getline(cin,content);
  for(auto itr : UM_VEC){
    if(itr.sender == logged_user){
      itr.content= content;
      itr.timestamp = timer();
      cout<<"Message sent!!\n";
    }
  }
}



int main() {
  int user_choice;
  vector<message> UM_VEC;
  message msgObject;
  bool global_user_logged = false;
  string logged_user;

  // user_menu_do
  do {
    user_menu();
    cin >> user_choice;
    cin.ignore();
    switch (user_choice) {
    case 1:
      user_register(UM_VEC, msgObject);
      break;

    case 2:
      user_login(UM_VEC, global_user_logged,logged_user);
      user_choice = 4;
      break;

    case 3:
      user_display(UM_VEC);
      break;

    default:
      cout << "INVALID CHOICE!!\n";
    }
  } while (user_choice != 4 && !global_user_logged);

  int msg_choice;
  do {
    msg_menu();
    cin >> msg_choice;
    switch (msg_choice) {
    case 1:
      send_msg(UM_VEC,msgObject,logged_user);
      break;
    case 2:
      break;
    case 3:
      break;
    }
  } while (msg_choice != 5);
}
