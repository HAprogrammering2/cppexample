// A small sample of some of the new features in C++ as compared with C.
// Compile with:  g++ -std=c++14 hello_world.cpp

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

int main(){
    string selection;
    int choice;
    vector<string> menu_items = {"add", "delete", "print", "quit"};
    list<string> history;
    map<string, int> histogram;

    cout << "Hello world!" << endl;

    do{
        auto i = 1;
        for (auto m : menu_items) {
            cout << i << ". " << m << endl;
            i++;
        }

        cout << "Your choice: ";
        cin >> choice;

        if (cin.fail() || choice > 4) {
            cout << "Wrong!" << endl;
            return EXIT_FAILURE;
        }
        selection = menu_items[choice-1];

        cout << "I don't want to " << selection << endl;
        history.push_back(selection);

    } while (selection != "quit");

    cout << "Your command history:";
    for (auto it=history.begin(); it != history.end(); ++it){
        cout << " " << *it;
    }
    cout << endl;

    history.sort();
    cout << "Your sorted command history:";
    for (auto item : history){
        cout << " " << item;
        
        if (histogram.find(item) != histogram.end()){
            histogram[item]++;
        }
        else {
            histogram[item]=1;
        }
    }
    cout << endl;

    cout << "Command usage statistics: " << endl;
    for(auto p : histogram){
        cout << "  " << p.first << " : " << p.second << endl;
    }
}