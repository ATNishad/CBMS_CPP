#include "my_functions.h"

int main() {
    int choice;
    vector<msgstruct> msgvec; // Vector creation

    do {
        menu();
        cin >> choice;
        cin.ignore(); // Clear newline from the input buffer
        switch (choice) {
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
                delmsg(msgvec);
                break;
            case 5:
                savemsg(msgvec);
                cout << "Messages have been saved!!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
