//Used to seperate application concerns

#include <iostream>

using namespace std;

//Model class
class UserModel {
private:
    int id;
    string name;
    string gender;

public:
    int getId() {
        return id;
    }

    void setId(int _id) {
        id = _id;
    }

    string getName() {
        return name;
    }

    void setName(string _name) {
        name = _name;
    }

    string getGender() {
        return gender;
    }

    void setGender(string _gender) {
        gender = _gender;
    }
};

class UserView {
public:
    void updateView(UserModel user) {
        cout << "Id: " << user.getId() << endl;
        cout << "Name: " << user.getName() << endl;
        cout << "Gender: " << user.getGender() << endl;
    }
};

class UserController {
private:
    UserModel userModel;
    UserView userView;

public:
    UserController(UserModel& model, UserView& view) {
        userModel = model;
        userView = view;
    }

    void updateModel(UserModel& model) {
        userModel = model;
    }

    void updateView(UserView& view) {
        userView = view;
    }

    void renderView() {
        userView.updateView(userModel);
    }
};

int main()
{
    //suppose this model data is coming from DB
    UserModel model;
    model.setId(1);
    model.setName("John");
    model.setGender("Male");

    //define a view for the model
    UserView view;

    //create a controller for the model and view 
    //do all model and view tasks on controller
    UserController controller(model, view);
    controller.renderView();

    //update data 
    UserModel model2;
    model2.setId(2);
    model2.setName("Amanda");
    model2.setGender("Female");

    //update model and render view according to new model
    controller.updateModel(model2);
    controller.renderView();

    return 0;
}