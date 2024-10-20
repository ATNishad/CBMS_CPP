#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

struct message_structure {
  string content;
  string timestamp;
  message_structure(string A, string B) : content(A), timestamp(B) {}
};
struct sender_structure {
  string username;
  vector<message_structure> message;

  void set_sender(string name) { this->username = name; }
  void set_message(string content, string timestamp) {
    message.push_back((message_structure(content, timestamp)));
  }
};

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

void user_register(vector<sender_structure> &sender_vector) {
  string name;
  cout << "Enter name to register:";
  getline(cin, name);
  sender_structure sender_object;
  sender_object.set_sender(name);
  sender_vector.push_back(sender_object);
}

void user_login(vector<sender_structure> sender_vector,bool &global_user_logged,sender_structure *&current_user_pointer) {
  string username;
  cout << "Enter your username:";
  cin.ignore();
  getline(cin, username);
  for (auto itr = sender_vector.begin(); itr != sender_vector.end(); ++itr) {
    if (itr->username == username) {
      current_user_pointer = &(*itr);
      global_user_logged = true;
    }
  }
}

void user_display(vector<sender_structure> sender_vector){
for(auto itr : sender_vector){
  cout<<itr.username;
  cout<<",";
}
  cout<<"\n";
}

void send_message(vector<sender_structure> &sender_vector,sender_structure* current_user_pointer){
  string content;
  cout<<"Enter message:";
  getline(cin,content);
}

int main() {
  int user_choice;
  vector<sender_structure> sender_vector;
  bool global_user_logged;
  sender_structure *current_user_pointer = nullptr;

  // user_menu_do
  do {
    user_menu();
    cin >> user_choice;
    cin.ignore();
    switch (user_choice) {
    case 1:
      user_register(sender_vector);
      break;

    case 2:
      user_login(sender_vector, global_user_logged, current_user_pointer);
      break;

    case 3:
      user_display(sender_vector);
      break;
    case 4:
      cout << "Exited program.";
      return 0;
    }
  } while (!global_user_logged);

  int msg_choice;
  do {
    msg_menu();
    cin >> msg_choice;
    switch (msg_choice) {
      case 1:
      send_message(sender_vector,current_user_pointer);
      break;
      case 2:
      break;
      
      case 3:
      break;
      
      case 4:
      break;
    
      case 5:
      break;
    }
  } while (msg_choice != 5);
}
