//returns single object for the class

#include <iostream>

using namespace std;

class Singleton {
private:
    Singleton() {}

    static Singleton* singleton;

public:
    static Singleton* getInstance() {
        //create object in first creation
        if (nullptr == singleton) {
            singleton = new Singleton();
        }
        //return same object for the other cases
        return singleton;
    }
};

Singleton* Singleton::singleton = nullptr;

int main()
{
    //Singleton class returns only one instance
    Singleton * firstInstance = Singleton::getInstance();
    Singleton * secondInstance = Singleton::getInstance();

    //both instances should point same address
    if (firstInstance == secondInstance) {
        cout << "Singleton object returns same object" << endl;
    }
    else {
        cout << "There is a problem about Singleton implementation" << endl;
    }

    return 0;
}