#include <iostream>

class Animal {
public:
    void say () {
        std::cout << "I'm an ordinary animal" << std::endl;
    }
    virtual void eat () {
        std::cout << "oridinaryly eating" << std::endl;
    }
};

class Cat : public Animal {
public:
    void say () {
        std::cout << "meow~" << std::endl;
    }
    void say (const std::string& word) {
        std::cout << "meow~ " << word << std::endl;
    }
    void eat () {
        std::cout << "eating fish" << std::endl;
    }
};

int main () {

    Animal* animal = new Animal;
    animal->say();
    animal->eat();

    Animal* cat = new Cat;
    cat->say();
    // cat->say("world"); // Compile Error!
    cat->eat();

    Cat* real_cat = (Cat*)cat;
    real_cat->say();
    real_cat->say("world");

    delete animal;
    delete cat;

    return 0;
}
