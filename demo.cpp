#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<fstream>
#include<chrono>
using namespace std;

//function prototype
static string timer();

//functions
void sendmsg(vector<string> &msgvec){
    string msg;
    cout<<"Enter your message:";
    getline(cin,msg);
    msgvec.push_back(msg);
    cout<<"Message sent!"<<"at"<<timer();
}
void viewmsg(vector<string> &msgvec){
    for(auto itr=msgvec.begin();itr != msgvec.end();){
    cout<<*itr;
    cout<<"\n";
    itr++;
    }
}  
void savemsg(vector<string> &msgvec){
    ofstream savefile;
    savefile.open("messages.txt");
    for(const auto &msg : msgvec){
        savefile<<msg<<endl;
        msgvec.pop_back();
    }
    savefile.close();
}
void loadmsg(vector<string> &msgvec){
    string messages;
    ifstream loadfile;
    loadfile.open("messages.txt");
    while(getline(loadfile,messages)){
        msgvec.push_back(messages);
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
    vector<string> msgvec;   //vector creation
    
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