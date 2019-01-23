// Abstract factory pattern works as a parent factory of other factories.
// firstly we select a diner, then order a food
#include <iostream>

using namespace std;

//Diner type
enum DinerType {
    MEAT = 1,
    VEGETABLE
};

//what you want to eat
enum FoodType {
    HAMBURGER = 1,
    STEAK,
    BROCCOLI,
    CAULIFLOWER
};

class Food {
public:
    virtual void order() = 0; //pure virtual function
};

class Meat : public Food {
public:
    virtual void order() {};
};

class Hamburger : public Meat {
public:
    void order() {
        cout << "Preparing Hamburger .." << endl;
    };
};

class Steak : public Meat {
public:
    void order() {
        cout << "Preparing Steak .." << endl;
    };
};

class Vegetable : public Food {
public:
    virtual void order() {};
};

class Broccoli : public Vegetable {
public:
    void order() {
        cout << "Preparing Broccoli .." << endl;
    };
};

class Cauliflower : public Meat {
public:
    void order() {
        cout << "Preparing Cauliflower .." << endl;
    };
};

class AbstractFoodFactory {
public:
    virtual Food* selectFood(FoodType type) = 0; //pure virtual function
};

class MeatFoodFactory : public AbstractFoodFactory {
public:
    Food* selectFood(FoodType type) {
        if (type == HAMBURGER) {
            return new Hamburger();
        }
        else if (type == STEAK) {
            return new Steak();
        }
        return nullptr;
    }
};

class VegetableFoodFactory : public AbstractFoodFactory {
public:
    Food* selectFood(FoodType type) {
        if (type == BROCCOLI) {
            return new Broccoli();
        }
        else if (type == CAULIFLOWER) {
            return new Cauliflower();
        }
        return nullptr;
    }
};

class FoodFactory {
public:
    static AbstractFoodFactory* selectFoodFactory(DinerType type) {
        if (type == MEAT) {
            return new MeatFoodFactory();
        }
        return new VegetableFoodFactory();
    }
};

int main()
{
    //Firstly we want to go a meat food diner
    AbstractFoodFactory* foodFactory = FoodFactory::selectFoodFactory(MEAT);
    //order a hamburger
    Food* food = foodFactory->selectFood(HAMBURGER);
    food->order();

    //Hamburger is not successful, now order a steak dish
    food = foodFactory->selectFood(STEAK);
    food->order();

    //So much meat is not healthy, go to vegetable food diner
    foodFactory = FoodFactory::selectFoodFactory(VEGETABLE);
    //order broccoli dish
    food = foodFactory->selectFood(BROCCOLI);
    food->order();

    //we couldn't eat broccoli, now try cauliflower dish
    food = foodFactory->selectFood(CAULIFLOWER);
    food->order();

    return 0;
}