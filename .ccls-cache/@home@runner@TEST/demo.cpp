#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<fstream>
using namespace std;

void sendmsg(vector<string> &msgvec){
    string msg;
    cout<<"Enter your message:";
    getline(cin,msg);
    msgvec.push_back(msg);
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
int main(){
    int choice;
    vector<string> msgvec;
    loadmsg(msgvec);
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