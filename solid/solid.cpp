//SOLID Principles were developed by Robert C. Martin,
//which makes support programmer to develop easily maintainable and
//extandable softwares, also helps programmer to avoid code smells and
//easily refactor code.
//S: Single Responsibility Principle
//O: Open-Closed Principle
//L: Liskov Substitution Principle
//I: Interface Segragation Principle
//D: Dependency Inversion Principle

#include <iostream>
#include <vector>

using namespace std;

enum ShapeType {
    Triangle = 1,
    Rectangle,
    Circle,
    Unknown
};

//base shape class for the SOLID principles' examples
class Shape {
protected:
    ShapeType type;
public:
    ShapeType getType() {
        return this->type;
    }

    virtual double getArea() {
        return 0;
    }
};

class Triangle : public Shape {
private:
    double height;
    double baseWidth;
public:
    Triangle() {
        type = ShapeType::Triangle;
    }

    virtual double getArea() override {
        return height * baseWidth / 2;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
public:
    Rectangle() {
        type = ShapeType::Rectangle;
    }

    virtual double getArea() override {
        return height * width;
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle() {
        type = ShapeType::Circle;
    }

    virtual double getArea() override {
        return 3.14 * radius * radius;
    }
};

//Single Responsibility Principle (SRP)
//A class should have one, and only one, reason to change
//meaning that a class should have only one job.
class AreaCalculator {
protected:
    vector<Shape> shapes;
public:
    vector<Shape> getShapes() {
        return this->shapes;
    }

    virtual double getTotalArea() {
        double totalArea = 0;
        for (Shape s : shapes) {
            totalArea += s.getArea();
        }
        return totalArea;
    }

    //This conflicts with SRP because this class created for the area calculation
    //principle is saying not use it for the other jobs
    double getTotalPerimeter() {
        return 0;
    }
};

//Open-Closed Principle (OCP)
//Software entities(Classes, modules, functions) should be open for extension,
//and closed for the modification
//In this class totalArea depends directly types of the shapes. If we add more shapes
//we need to update our class code bases, but in AreaCalculator we don't need to update our codes
class BadDesignAreaCalculator : public AreaCalculator {
public:
    virtual double getTotalArea() override {
        double totalArea = 0;
        for (Shape s : shapes) {
            if (s.getType() == ShapeType::Triangle || s.getType() == ShapeType::Rectangle || s.getType() == ShapeType::Circle) {
                totalArea += s.getArea();
            }
        }
        return totalArea;
    }
};

//Liskov Substitution Principle (LSP)
//A sub-class must be substitutable for its super-class
//a subclass should override the parent class methods in a way that does
//not break functionality from a client’s point of view.
//If we don't implement getArea() functionality,
//it couln't give same functionality to client
class Pentagon {
private:
    double length;
public:
    //It doesn't implement area calculation with same Interface
    double calculateArea() {
        return 0;
    }
};

//Interface Segragation Principle (ISP)
//A client should never be forced to implement an interface that it doesn't use or
//clients shouldn't be forced to depend on methods they do not use.
//Many client-specific interfaces are better than one general-purpose interface.
class Reporter { //interface
public:
    virtual ~Reporter() {}
    virtual void report(string str) = 0; //pure virtual function
};

class DataManager {
public:
    virtual ~DataManager() {}
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool read() = 0;
    virtual bool write() = 0;
};

class ContentManagement : public DataManager, public Reporter {
public:
    virtual void report(string str) {
        cout << str << endl;
    }

    virtual bool open() {
        //...
        return true;
    }

    virtual bool close() {
        //...
        return true;
    }

    virtual bool read() {
        //...
        return true;
    }

    virtual bool write() {
        //...
        return true;
    }
};

//Dependency Inversion Principle (DIP)
//High-level modules should not depend on low-level modules. Both should depend on abstractions.
//Abstractions should not depend on details. Details should depend on abstractions.
//Logger class should not directly depends OracleDBConnection, may be in future we want to change
//our DB with SQL server
class DBConnection {
public:
    virtual ~DBConnection() {}
    virtual void connect() = 0;
    virtual void query(string str) = 0;
    virtual void disconnect(string str) = 0;
};

class OracleDBConnection : public DBConnection {
public:
    virtual void connect() {
        //..
        cout << "Connected to Oracle DB!" << endl;
    }

    virtual void query(string str) override {
        //...
    }

    virtual void disconnect(string str) override{
        //...
    }
};

class Logger {
public:
    //High-level modules should not depend on low-level modules. Both should depend on abstractions.
    /*Logger(OracleDBConnection dbConnection) {

    }*/
    Logger(DBConnection * dbConnection) {
        dbConnection->connect();
    }
};

int main()
{
    //Single Responsibility Principle (SRP)
    //Class should be created for only one job
    //don't add perimeter calculation
    AreaCalculator areaCalculator;
    cout << areaCalculator.getTotalArea() << endl;

    //Open-Closed Principle (OCP)
    BadDesignAreaCalculator badAreaCalculator;
    cout << badAreaCalculator.getTotalArea() << endl;

    //Liskov Substitution Principle (LSP)
    Pentagon pentagon;
    cout << pentagon.calculateArea() << endl;

    //Interface Segragation Principle (ISP)
    //Our content management class implements different classes according its needs
    ContentManagement contentManagement;
    contentManagement.report("ISP");

    //Dependency Inversion Principle (DIP)
    //High-level modules should not depend on low-level modules. Both should depend on abstractions.
    OracleDBConnection oracleDBConnection ;
    Logger logger(&oracleDBConnection);

    return 0;
}