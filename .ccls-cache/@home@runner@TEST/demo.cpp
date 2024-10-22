#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<fstream>
#include<chrono>
using namespace std;

//function prototype
static string timer();

//message structure
struct msgstruct{
string message;
string timestamp;
//constructor
msgstruct(string a,string b) : message(a),timestamp(b){}};

//functions
void sendmsg(vector<msgstruct> &msgvec){
    string msg;
    cout<<"\n";
    cout<<"Enter your message:";
    getline(cin,msg);
    msgvec.push_back(msgstruct(msg,timer()));
    cout<<"Message sent at "<<timer()<<"\n";
}
void viewmsg(vector<msgstruct> &msgvec){
    for(auto itr=msgvec.begin();itr != msgvec.end();){
    cout<<itr->message<<" "<<"["<<itr->timestamp<<"]";
    cout<<"\n";
    itr++;
    }
}  
void savemsg(vector<msgstruct> &msgvec){
    ofstream savefile;
    savefile.open("messages.txt");
    for(const auto &msg : msgvec){
        savefile<<msg.message <<" ["<< msg.timestamp<<"]"<< endl;

        msgvec.pop_back();
    }
    savefile.close();
}
void loadmsg(vector<msgstruct> &msgvec){
    string messages;
    ifstream loadfile;
    loadfile.open("messages.txt");
    while(getline(loadfile,messages)){
        msgvec.push_back(msgstruct(messages,timer()));
    }
}
void editmsg(vector<msgstruct> &msgvec){
    int index;
    string edited;
    for(int i=0;i<msgvec.size();i++){
        cout<<"["<<i<<"]"<<msgvec[i].message<<msgvec[i].timestamp<<"\n";
    }
    cout<<"enter message index:";
    cin>>index;
    string to_edit = msgvec[index].message;
    cout<<"Enter new message:";
    cin>>edited;
    msgvec[index].message = edited; 
}

static string timer(){
    const auto now = chrono::system_clock::now();
    time_t t= chrono::system_clock::to_time_t(now);
    string timestamp=std::ctime(&t);
    timestamp.pop_back();
    return timestamp;
}

void menu(){
    cout<<"\n";
    cout<<"-----MENU-----\n";
    cout<<"1.Send Messages.\n";
    cout<<"2.View Messages.\n";
    cout<<"3.Edit message.\n";
    cout<<"4.Save & Exit\n";
    cout<<"Enter your choice:";
}

int main(){
    int choice;
    timer();
    vector<msgstruct> msgvec;   //vector creation

    do{
    menu();
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
        sendmsg(msgvec);
        break;

        case 2:
        viewmsg(msgvec);
        break;

        case 3:
        editmsg(msgvec);
        break;
        
        case 4:
        savemsg(msgvec);
        cout<<"Messages have been saved!!\n";
        break;
    }
    }
    while(choice!=4);
}