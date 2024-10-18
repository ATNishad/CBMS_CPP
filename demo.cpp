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
msgstruct(string a,string b) : message(a),timestamp(b){}
};

//functions
void sendmsg(vector<msgstruct> &msgvec){
    string msg;
    cout<<"Enter your message:";
    getline(cin,msg);
    msgvec.push_back(msgstruct(msg,timer()));
    cout<<"Message sent at "<<timer();
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
        savefile<<msg.message+msg.timestamp<<endl;
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
void menu(){
    cout<<"-----MENU-----\n";
    cout<<"1.Send Messages.\n";
    cout<<"2.View Messages.\n";
    cout<<"3.Save & Exit\n";
    cout<<"Enter your choice:";
}
static string timer(){
    const auto now = chrono::system_clock::now();
    time_t t= chrono::system_clock::to_time_t(now);
    string timestamp=std::ctime(&t);
    return timestamp;
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
        savemsg(msgvec);
        cout<<"Messages have been saved!!\n";
        break;
    }
    }
    while(choice!=3);
}