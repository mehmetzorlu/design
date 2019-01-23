//Notify all observers without knowing their detail

#include <iostream>
#include <vector>

using namespace std;

class FireObserver {
public:
    virtual void fireDetected() = 0;
};

class AlarmManager : public FireObserver {
public:
    void fireDetected() {
        cout << "Sound up alarm level to red .." << endl;
    }
};

class SecurityCamera : public FireObserver {
public:
    void fireDetected() {
        cout << "Pop up fire alarm warnings on the cameras.." << endl;
    }
};

class AutoPhone : public FireObserver {
public:
    void fireDetected() {
        cout << "Call firefighters and ambulance services, send messages to building residents .." << endl;
    }
};

class FireNotifier {
private:
    vector<FireObserver *> observers;

public:
    void addObserver(FireObserver * observer) {
        observers.push_back(observer);
    }

    void fireOccured() {
        for (FireObserver * observer : observers) {
            observer->fireDetected();
        }
    }
};

int main()
{
    //Setting fire notifier system
    FireNotifier fireNotifier;

    //add/define all observers to system
    fireNotifier.addObserver(new AlarmManager());
    fireNotifier.addObserver(new SecurityCamera());
    fireNotifier.addObserver(new AutoPhone());

    //suppose a time later fire occured
    fireNotifier.fireOccured();

    return 0;
}