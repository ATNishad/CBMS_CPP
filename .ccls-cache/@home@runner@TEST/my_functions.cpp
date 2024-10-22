#include "my_functions.h"

// Function to get the current timestamp
const string timer() {
    const auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    string timestamp = std::ctime(&t);
    timestamp.pop_back();
    return timestamp;
}

// Function to send messages
void sendmsg(vector<msgstruct>& msgvec) {
    string msg;
    cout << "\nEnter your message: ";
    getline(cin, msg);
    msgvec.push_back(msgstruct(msg, timer()));
    cout << "Message sent at " << timer() << "\n";
}

// Function to view messages
void viewmsg(const vector<msgstruct>& msgvec) {
    for (auto itr = msgvec.begin(); itr != msgvec.end(); itr++) {
        cout << itr->message << " [" << itr->timestamp << "]\n";
    }
}

// Function to save messages to a file
void savemsg(const vector<msgstruct>& msgvec) {
    ofstream savefile;
    savefile.open("messages.txt");
    for (const auto& msg : msgvec) {
        savefile << msg.message << " [" << msg.timestamp << "]" << endl;
    }
    savefile.close();
}

// Function to load messages from a file
void loadmsg(vector<msgstruct>& msgvec) {
    string messages;
    ifstream loadfile;
    loadfile.open("messages.txt");
    while (getline(loadfile, messages)) {
        msgvec.push_back(msgstruct(messages, timer()));
    }
}

// Function to edit messages
void editmsg(vector<msgstruct>& msgvec) {
    int index;
    string edited;
    for (int i = 0; i < msgvec.size(); i++) {
        cout << "[" << i << "] " << msgvec[i].message << " " << msgvec[i].timestamp << "\n";
    }
    cout << "Enter index to be edited: ";
    cin >> index;
    cin.ignore();
    cout << "Enter new message: ";
    getline(cin, edited);
    msgvec[index].message = edited;
    cout << "Edited successfully!\n";
}

//function to delete message
void delmsg(vector<msgstruct> &msgvec){
    cout<<"\n";
    int index;
    for (int i = 0; i < msgvec.size(); i++) {
        cout << "[" << i << "] " << msgvec[i].message << " " << msgvec[i].timestamp << "\n";
    }
    cout<<"Select the index to be deleted:";
    cin>>index;
    msgvec.erase(msgvec.begin() + index);
    cout<<"Message at index "<<"["<<index<<"]"<<"has been deleted!\n";
}

// Function to display the menu
void menu() {
    cout << "\n-----MENU-----\n";
    cout << "1. Send Messages.\n";
    cout << "2. View Messages.\n";
    cout << "3. Edit Message.\n";
    cout << "4. Delete Message.\n";
    cout << "5. Save & Exit.\n";
    cout << "Enter your choice: ";
}
