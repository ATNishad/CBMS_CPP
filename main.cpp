#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
using namespace std;

struct message_structure {
    string content;
    string timestamp;
    message_structure(string A,string B) : content(A), timestamp(B) {}
};

struct sender_structure {
    string username;
    vector<message_structure> inbox;
    vector<message_structure> message;

    void set_sender(string name) { this->username=name; }
    void set_message(string content, string timestamp) {
        message.push_back((message_structure(content,timestamp)));
    }
    void set_inbox(string content,string timestamp){
      inbox.push_back(message_structure(content,timestamp));
    }
};

class userHandling {
public:

    // used this function inside user_register
    const bool name_check(const vector<sender_structure>& sender_vector,string name) {
        for (const auto& itr : sender_vector) {
            if (name==itr.username) {
                return true;
            }
        }
        return false;
    }

    void user_register(vector<sender_structure>& sender_vector) {
        string name;
        while (true) {
            cout<<"Enter name to register: ";
            getline(cin,name);

            if (name.empty()) {
                cout<<"Enter valid name to register!!\n";
            }
            else if (name_check(sender_vector,name)) {
                cout<<"Username already exists. Try with a different name.\n";
            }
            else {
                sender_structure sender_object;
                sender_object.set_sender(name);
                sender_vector.push_back(sender_object);
                cout<<"Registered successfully!\n";
                break;
            }
        }
    }

    void user_login(vector<sender_structure>& sender_vector,bool& is_global_user_logged,sender_structure*& current_user_pointer) {
        string username;
        cout<<"Enter your username: ";
        getline(cin,username);
        for (auto& sender : sender_vector) {
            if (sender.username==username) {
                current_user_pointer=&sender;
                is_global_user_logged=true;
                return;
            }
        }
        is_global_user_logged=false;
    }

    const void user_display(const vector<sender_structure>& sender_vector) {
        for (const auto& itr : sender_vector) {
            cout<<itr.username;
            cout<<",";
        }
        cout<<"\n";
    }

    void user_menu() {
        cout<<"\n";
        cout<<"-----MENU-----\n";
        cout<<"1. REGISTER-new user.\n";
        cout<<"2. LOGIN-existing user.\n";
        cout<<"3. Display users.\n";
        cout<<"4. EXIT.\n";
        cout<<"Enter your choice: ";
    }

};

class messageHandling {
public:

    const string timer() {
        const auto now=chrono::system_clock::now();
        time_t t=chrono::system_clock::to_time_t(now);
        string timestamp=std::ctime(&t);
        timestamp.pop_back();
        return timestamp;
    }

    void send_message(vector<sender_structure>& sender_vector,sender_structure* current_user_pointer) {
        string content;
        string r_name;
        cout<<"Enter recipient name:";
        getline(cin,r_name);
        for(auto &itr : sender_vector){
          if(itr.username == r_name){
            cout<<"Enter message:";
            getline(cin,content);
            itr.set_inbox(content,timer());
            current_user_pointer->set_message(content,timer());
            cout<<"Message sent successfully!\n";
          }
          else{
            cout<<"Recipient doesnt exist.\n";
          }
        }
  }
        

    const void view_message(vector<sender_structure>& sender_vector,sender_structure* current_user_pointer) {
        for (const auto& itr : sender_vector) {
            if (itr.username==current_user_pointer->username) {
              cout<<"SENT MESSAGES:\n";
                for(const auto &msg : current_user_pointer->message){
                    cout<<msg.content<<" "<< "["<<msg.timestamp<<"]"<<"\n";}
              cout<<"INBOX:\n";
                for(const auto &ib : current_user_pointer->inbox){
                  cout<<ib.content<<" "<< "["<<ib.timestamp<<"]"<<"\n";
                }
            }
        }
    }

    void edit_message(vector<sender_structure>& sender_vector,sender_structure* current_user_pointer) {
        int display_index=0;
        int edit_index;
        string content;
        for (auto itr=current_user_pointer->message.begin();itr!=current_user_pointer->message.end();++itr,display_index++) {
            cout<<"["<<display_index<<"]"<<itr->content;
            cout<<"\n";
        }
        cout<<"Enter message index to edit: ";
        cin>>edit_index;
        cin.ignore();
        cout<<"Enter new message: ";
        getline(cin,content);
        int index=0;
        for (auto& itr : current_user_pointer->message) {
            if (index==edit_index) {
                itr.content=content;
                cout<<"Message edited successfully!\n";
                return; 
            }
            index++;
        }
        cout<<"Invalid index provided for editing.\n"; 
    }

    void delete_message(vector<sender_structure>& sender_vector,sender_structure* current_user_pointer) {
        int display_index=0;
        int delete_index;
        for (const auto& itr : current_user_pointer->message) {
            cout<<"["<<display_index<<"]"<<itr.content;
            cout<<"\n";
            display_index++;
        }

        cout<<"Enter message index to delete: ";
        cin>>delete_index;
        cin.ignore(); 

        if (delete_index<0||delete_index>=current_user_pointer->message.size()) { 
            cout<<"Enter a valid index to delete\n";
        }
        else {
            current_user_pointer->message.erase(current_user_pointer->message.begin()+delete_index);
            cout<<"Message deleted successfully!\n";
        }
    }

    void search_message(vector<sender_structure>& sender_vector,sender_structure* current_user_pointer) {
        string keyword;
        bool keyword_found=false;
        cout<<"Enter keyword to search: ";
        getline(cin,keyword);
        for (const auto& msg : current_user_pointer->message) {
            if (msg.content.find(keyword)!=string::npos) {
                cout<<"Message found: "<<msg.content<<"["<<msg.timestamp<<"]"<<"\n";
                keyword_found=true;
            }
        }
        if (!keyword_found) {
            cout<<"Message with \'"<<keyword<<"\' not found\n";
        }
    }

    void savefile(vector<sender_structure>& sender_vector,sender_structure* current_user_pointer) {
        ofstream save_sentfilestream;
        save_sentfilestream.open(current_user_pointer->username+"_sent_messages.txt");
        for(const auto& msg : current_user_pointer->message) {
        save_sentfilestream<<msg.content<<"|"<<msg.timestamp<<"\n";
        }
        save_sentfilestream.close();

        ofstream save_inboxfilestream;
        save_inboxfilestream.open(current_user_pointer->username+"_inbox_messages.txt");
         for(const auto& msg : current_user_pointer->inbox) {
        save_inboxfilestream<<msg.content<<"|"<<msg.timestamp<<"\n";
        }
        save_inboxfilestream.close();
        cout<<"File saved!\n"; 
        }

    void loadfile(vector<sender_structure>& sender_vector, sender_structure* current_user_pointer) {
    ifstream load_sentfilestream(current_user_pointer->username + "_sent_messages.txt");
    string content,timestamp,lineread;

    if (!load_sentfilestream.is_open()) {
        cout<<"Failed to load sent messages.\n";
        return;
    }

    while(getline(load_sentfilestream, lineread)) {
        size_t delimiter_position = lineread.find("|");
        if (delimiter_position != string::npos) {
            content = lineread.substr(0, delimiter_position);
            timestamp = lineread.substr(delimiter_position + 1);
            current_user_pointer->set_message(content,timestamp);
        }
    }
    load_sentfilestream.close();
    cout<<"Sent messages loaded.\n";

    ifstream load_inboxfilestream(current_user_pointer->username +"_inbox_messages.txt");

    if(!load_inboxfilestream.is_open()){
      cout<<"Failed to load inbox messages.\n";
      return;
    }

    while(getline(load_inboxfilestream,lineread)){
      size_t delimiter_pos = lineread.find("|");
      if(delimiter_pos != string::npos){
        content=lineread.substr(0,delimiter_pos);
        timestamp=lineread.substr(delimiter_pos + 1);
        current_user_pointer->set_inbox(content,timestamp);
      }
    }
    load_inboxfilestream.close();
    cout << "Inbox messages loaded!" << endl;
}


    void msg_menu() {
        cout<<"\n-----MENU-----\n";
        cout<<"1. Send Messages.\n";
        cout<<"2. View Messages.\n";
        cout<<"3. Search Message.\n";
        cout<<"4. Edit Message.\n";
        cout<<"5. Delete Message.\n";
        cout<<"6. Save & Exit.\n";
        cout<<"Enter your choice: ";
    }

};

int main() {
    int user_choice;
    bool is_global_user_logged=false;
    vector<sender_structure> sender_vector;
    sender_structure* current_user_pointer=nullptr;

    userHandling userHandlingObject;
    messageHandling messageHandlingObject;

    // user_menu_do
    do {
        userHandlingObject.user_menu();
        cin>>user_choice;
        cin.ignore();
        switch (user_choice) {
            case 1:
                userHandlingObject.user_register(sender_vector);
                break;

            case 2:
                userHandlingObject.user_login(sender_vector,is_global_user_logged,current_user_pointer);
                if (is_global_user_logged) {
                    messageHandlingObject.loadfile(sender_vector,current_user_pointer);
                    cout<<"LOGIN SUCCESSFUL!\n";

                    // msg_menu_do
                    int msg_choice;
                     do {
                      messageHandlingObject.msg_menu();
                      cin>>msg_choice;
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
                              cout<<"Exiting message menu.\n"; 
                              break;
                              }
                            } while (msg_choice != 6); 
                    }
                else {
                    cout<<"LOGIN FAILED!\n";
                }
                break;

            case 3:
                userHandlingObject.user_display(sender_vector);
                break;
            case 4: 
                cout<<"Exited program.";
                return 0;
        }
    } while (true);
}
