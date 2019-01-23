//Creates objects without specifying their exact class types
#include <iostream>

using namespace std;

enum ShapeType {
    CIRCLE = 1,
    RECTANGLE,
    PENTAGON
};

class Shape {
public:
    virtual void Draw() {}
};

class Circle : public Shape {
public:
    virtual void Draw() {
        cout << "Drawing Circle..." << endl;
    }
};

class Rectangle : public Shape {
public:
    virtual void Draw() {
        cout << "Drawing Rectangle..." << endl;
    }
};

class Pentagon : public Shape {
public:
    virtual void Draw() {
        cout << "Drawing Pentagon..." << endl;
    }
};

//Factory class returns base class for all types
class ShapeFactory {
public:
    Shape* getShape(ShapeType type) {
        if (CIRCLE == type) {
            return new Circle();
        }
        else if (RECTANGLE == type) {
            return new Rectangle();
        }
        else if (PENTAGON == type) {
            return new Pentagon();
        }
        return nullptr;
    }
};

int main()
{
    //same factory draws different shapes
    ShapeFactory factory;
    Shape* shape = factory.getShape(CIRCLE);
    shape->Draw();
    shape = factory.getShape(RECTANGLE);
    shape->Draw();
    shape = factory.getShape(PENTAGON);
    shape->Draw();

    return 0;
}