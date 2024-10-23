#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <vector>
#include<fstream>
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

class userHandling{
public:
void user_register(vector<sender_structure> &sender_vector) {
  string name;
  while(true){
  cout << "Enter name to register:";
  getline(cin, name);
  if(!name.empty()){
  sender_structure sender_object;
  sender_object.set_sender(name);
  sender_vector.push_back(sender_object);
  cout<<"Registered successfully!\n";
  break;
  }
  else{
    cout<<"Enter valid name to register!!\n";
  }
}
}

void user_login(vector<sender_structure> &sender_vector,bool &global_user_logged,sender_structure *&current_user_pointer) {
  string username;
  cout << "Enter your username:";
  getline(cin, username);
  for (auto &sender : sender_vector) {
    if (sender.username == username) {
      current_user_pointer = &sender;
      global_user_logged = true;
      return;
    }
  }
  global_user_logged = false;
}

const void user_display(const vector<sender_structure> &sender_vector){
for(const auto itr : sender_vector){
  cout<<itr.username;
  cout<<",";
}
  cout<<"\n";
}

};

class messageHandling{
public:

const string timer() {
  const auto now = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(now);
  string timestamp = std::ctime(&t);
  timestamp.pop_back();
  return timestamp;
}

void send_message(vector<sender_structure> &sender_vector,sender_structure* current_user_pointer){
  string content;
  cout<<"Enter message:";
  getline(cin,content);
  current_user_pointer->set_message(content,timer());
  cout<<"Message sent successfully!\n";
}

const void view_message(vector<sender_structure> &sender_vector,sender_structure* current_user_pointer){
  for(const auto itr : sender_vector){
    if(itr.username == current_user_pointer->username){
      for(const auto itr : current_user_pointer->message )
      cout<<itr.content<<" "<<"["<<itr.timestamp<<"]"<<"\n";
    }
  }
}

void edit_message(vector<sender_structure> &sender_vector,sender_structure* current_user_pointer){
  int display_index = 0;
  int edit_index;
  string content;
  for(auto itr = current_user_pointer->message.begin();itr != current_user_pointer->message.end();++itr , display_index++){
    cout<<"["<<display_index<<"]"<<itr->content;
    cout<<"\n";
  }
  cout<<"Enter message index to edit:";
  cin>>edit_index;
  cin.ignore();
  cout<<"Enter new message:";
  getline(cin,content);
  int index = 0;
  for(auto &itr : current_user_pointer->message){
    if(index == edit_index){
      itr.content = content;
      cout<<"Message edited successfully!\n";
    }index++;
  }
}

void delete_message(vector<sender_structure> &sender_vector,sender_structure* current_user_pointer){
  int display_index = 0;
  int delete_index;
  string content;
  for(auto itr = current_user_pointer->message.begin();itr != current_user_pointer->message.end();++itr , display_index++){
    cout<<"["<<display_index<<"]"<<itr->content;
    cout<<"\n";
  }

  cout<<"Enter message index to delete:";
  cin>>delete_index;
  int index = 0;
  for(auto &itr : current_user_pointer->message){
    if(index == delete_index){
      current_user_pointer->message.erase(current_user_pointer->message.begin() + delete_index);
      cout<<"Message deleted successfully!\n";
    }index++;
  }
}

void search_message(vector<sender_structure> &sender_vector,sender_structure* current_user_pointer){
  string keyword;
  cout<<"Enter keyword to search:";
  getline(cin,keyword);
  for(const auto &msg : current_user_pointer->message){
    if(msg.content.find(keyword) != string::npos){
    cout<<"message found:"<<msg.content<<"["<<msg.timestamp<<"]"<<"\n";
    }
    else{
      cout<<"message not found\n";
    }
  }
}

void savefile(vector<sender_structure> &sender_vector,sender_structure* current_user_pointer){
  ofstream savefilestream;
  savefilestream.open("messages.txt");
  for(const auto itr : current_user_pointer->message){
  savefilestream<<itr.content<<"|"<<itr.timestamp<<"\n";
  }
  savefilestream.close();
  cout<<"File saved!";
}

void loadfile(vector<sender_structure> &sender_vec, sender_structure* current_user_pointer) {
    string content, timestamp, lineread;
    ifstream loadfilestream("messages.txt");
    if (!loadfilestream.is_open()) {
        cout << "Failed to load messages" << endl;
        return;
    }
    while(getline(loadfilestream, lineread)) {
        size_t delimiter_position = lineread.find("|");
        if (delimiter_position != string::npos) { 
            content = lineread.substr(0, delimiter_position);
            timestamp = lineread.substr(delimiter_position + 1);
            current_user_pointer->set_message(content, timestamp);
        }
    }
    loadfilestream.close();
    cout << "Messages loaded!" << endl;
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
  cout<<"\n-----MENU-----\n";
  cout<<"1.Send Messages.\n";
  cout<<"2.View Messages.\n";
  cout<<"3.Search Message.\n";
  cout<<"4.Edit Message.\n";
  cout<<"5.Delete Message.\n";
  cout<<"6.Save & Exit.\n";
  cout<<"Enter your choice: ";
}



int main() {
  int user_choice;
  int msg_choice;
  bool global_user_logged = false;
  vector<sender_structure> sender_vector;
  sender_structure *current_user_pointer = nullptr;
  
  userHandling userHandlingObject;
  messageHandling messageHandlingObject;
  
  // user_menu_do
  do {
    user_menu();
    cin >> user_choice;
    cin.ignore();
    switch (user_choice) {
    case 1:
      userHandlingObject.user_register(sender_vector);
      break;

    case 2:
      userHandlingObject.user_login(sender_vector, global_user_logged, current_user_pointer);
      if(global_user_logged){
      messageHandlingObject.loadfile(sender_vector,current_user_pointer);
      cout<<"LOGIN SUCCESSFULL!\n";
      }
      else{
        cout<<"LOGIN FAILED!\n";
      }
      break;

    case 3:
      userHandlingObject.user_display(sender_vector);
      break;
    case 5:
      cout << "Exited program.";
      return 0;
    }
  } while (!global_user_logged);

  //msg_menu_do
  do {
    msg_menu();
    cin >> msg_choice;
    cin.ignore();
    switch (msg_choice) {
      case 1:
      messageHandlingObject.send_message(sender_vector,current_user_pointer);
      break;

      case 2:
      messageHandlingObject.view_message(sender_vector,current_user_pointer);
      break;
      
      case 3:
      messageHandlingObject.search_message(sender_vector,current_user_pointer);
      break;

      case 4:
      messageHandlingObject.edit_message(sender_vector,current_user_pointer);
      break;
      
      case 5:
      messageHandlingObject.delete_message(sender_vector,current_user_pointer);
      break;
    
      case 6:
      messageHandlingObject.savefile(sender_vector,current_user_pointer);
      break;
    }
  } while (msg_choice != 6);
}


