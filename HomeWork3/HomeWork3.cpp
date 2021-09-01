#include <iostream>
#include <cmath>
#include <string>
#include "Card.h"

//>> First task
class Figure {
protected:
    std::string* _name;
public:
    virtual double area() = 0;
    virtual std::string* const getName() = 0;
    virtual ~Figure() {};
};

class Parallelogram : public Figure {
private:
    std::string* const _name = new std::string("Parallelogram");
protected:
    double _a = 0, _h = 0;
public:
    Parallelogram(double a, double h) : _a(a), _h(h) {};
    virtual double area() override {
        return _a * _h;
    };
    virtual std::string* const getName() override {
        return _name;
    };
    virtual ~Parallelogram() override {};
};

class Circle : public Figure {
private:
    double _r = 0;
    double const _pi = std::acos(-1);
    std::string* const _name = new std::string("Circle");
public:
    Circle(double r) : _r(r) {};
    virtual double area() override {
        return _pi * pow(_r, 2);
    };
    virtual std::string* const getName() override {
        return _name;
    };
    virtual ~Circle() override {};
};

class Rectangle : public Parallelogram {
private:
    std::string* const _name = new std::string("Rectangle");
public:
    Rectangle(double a, double b) : Parallelogram(a, b) {};
    virtual double area() override {
        return _a * _h;
    };
    virtual std::string* const getName() override {
        return _name;
    };
    virtual ~Rectangle() override {};
};

class Square : public Parallelogram {
private:
    std::string* const _name = new std::string("Square");
public:
    Square(double a) : Parallelogram(a, a) {};
    virtual double area() override {
        return pow(_a, 2);
    };
    virtual std::string* const getName() override {
        return _name;
    };
    virtual ~Square() override {};
};

class Rhombus : public Parallelogram {
private:
    std::string* const _name = new std::string("Rhombus");
public:
    Rhombus(double a, double h) : Parallelogram(a, h) {};
    virtual double area() override {
        return _a * _h;
    };
    virtual std::string* const getName() override {
        return _name;
    };
    virtual ~Rhombus() override {};
};

void FirstTask() {
    int const arrayAmount = 5;
    Figure* figures[arrayAmount] {
        new Rhombus(1,5),
        new Square(6),
        new Rectangle(4,1),
        new Parallelogram(4,7),
        new Circle(2)
    };
    for (int i = 0; i < arrayAmount; i++)
    {
        std::cout << *(figures[i]->getName()) << ": " << figures[i]->area() << std::endl;
        delete figures[i];
    }
   
}
//<< First task

//>> Second task
class Car {
protected:
    std::string* _company;
    std::string* _model;
public:
    Car(std::string* const company, std::string* const model) : _company(company), _model(model) {
        std::cout << "Car" << std::endl;
    };
    std::string* const getCompany() {
        return _company;
    };
    std::string* const getModel() {
        return _model;
    };
    ~Car() {
        std::cout << "~Car" << std::endl;
    };
};
class PassengerCar : virtual public Car {
public:
    PassengerCar(std::string* const company, std::string* const model) : Car(company, model) {
        std::cout << "PassengerCar" << std::endl;
    };
    ~PassengerCar() {
        std::cout << "~PassengerCar" << std::endl;
    };
};
class Bus : virtual public Car {
public:
    Bus(std::string* const company, std::string* const model) : Car(company, model) {
        std::cout << "Bus" << std::endl;
    };
    ~Bus() {
        std::cout << "~Bus" << std::endl;
    };
};
class Minivan : public Bus, public PassengerCar {
public:
    Minivan(std::string* const company, std::string* const model) : Bus(company, model), PassengerCar(company, model), Car(company, model) {
        std::cout << "Minivan" << std::endl;
    };
    ~Minivan() {
        std::cout << "~Minivan" << std::endl;
    };
};

void SecondTask() {
    std::string company = "Volkswagen";
    std::string model = "Multivan";
    Minivan testCar(&company,&model);
    std::cout << "Minivan info: " << *testCar.getCompany() << ", " << *testCar.getModel() << std::endl;
};
//<< Second task
//>>Third task

class Fraction {
private:
    int _numerator;
    int _denominator;
public:
    Fraction(int numerator, int denominator) : _numerator(numerator), _denominator(denominator == 0 ? 1 : denominator) {};

    std::string* const toString() {
        return new std::string(_numerator == 0 ? "0" : (std::to_string(_numerator) + "/" + std::to_string(_denominator)));
    };

    Fraction operator- () const {
        return Fraction(-_numerator, _denominator);
    };

    Fraction operator-= (const Fraction& f2) const {
        if (_denominator == f2._denominator) {
            return Fraction(_numerator - f2._numerator, _denominator);
        }
        return Fraction(_numerator * f2._denominator - f2._numerator * _denominator, _denominator * f2._denominator);
    };

    Fraction operator+= (const Fraction& f2) const {
        if (_denominator == f2._denominator) {
            return Fraction(_numerator + f2._numerator, _denominator);
        }
        return Fraction(_numerator * f2._denominator + f2._numerator * _denominator, _denominator * f2._denominator);
    };

    friend Fraction operator+ (const Fraction& f1,const Fraction& f2) {
        if (f1._denominator == f2._denominator) {
            return Fraction(f1._numerator + f2._numerator, f1._denominator);
        }
        return Fraction(f1._numerator * f2._denominator + f2._numerator * f1._denominator, f1._denominator * f2._denominator);
    };

    friend Fraction operator- (const Fraction& f1, const Fraction& f2) {
        if (f1._denominator == f2._denominator) {
            return Fraction(f1._numerator - f2._numerator, f1._denominator);
        }
        return Fraction(f1._numerator * f2._denominator - f2._numerator * f1._denominator, f1._denominator * f2._denominator);
    };

    friend Fraction operator/ (const Fraction& f1, const Fraction& f2) {
        return Fraction(f1._numerator * f2._denominator, f1._denominator * f2._numerator);
    };

    friend Fraction operator* (const Fraction& f1, const Fraction& f2) {
        return Fraction(f1._numerator * f2._numerator , f1._denominator * f2._denominator);
    };

    friend bool operator== (const Fraction& f1, const Fraction& f2) {
        return (f1._numerator * f2._denominator == f2._numerator * f1._denominator);
    };

    friend bool operator!= (const Fraction& f1, const Fraction& f2) {
        return (f1._numerator * f2._denominator != f2._numerator * f1._denominator);
    };

    friend bool operator< (const Fraction& f1, const Fraction& f2) {
        return (f1._numerator * f2._denominator < f2._numerator * f1._denominator);
    };

    friend bool operator> (const Fraction& f1, const Fraction& f2) {
        return !(f1<f2);
    };

    friend bool operator<= (const Fraction& f1, const Fraction& f2) {
        return (f1._numerator * f2._denominator <= f2._numerator* f1._denominator);
    };

    friend bool operator>= (const Fraction& f1, const Fraction& f2) {
        return !(f1<=f2);
    };
};

void ThirdTask() {
    Fraction f1(1, 8);
    Fraction f2(2, 16);
    std::cout << "+: " << *(f1 + f2).toString() << std::endl;
    std::cout << "-: " << *(f1 - f2).toString() << std::endl;
    std::cout << "*: " << *(f1 * f2).toString() << std::endl;
    std::cout << "/: " << *(f1 / f2).toString() << std::endl;
    std::cout << "<: " << (f1 < f2) << std::endl;
    std::cout << "<=: " << (f1 <= f2) << std::endl;
    std::cout << ">: " << (f1 > f2) << std::endl;
    std::cout << ">=: " << (f1 >= f2) << std::endl;
    std::cout << "==: " << (f1 == f2) << std::endl;
    std::cout << "!=: " << (f1 != f2) << std::endl;
    std::cout << "-: " << *(-f1).toString() << std::endl;
};
//<<Third task

int main()
{
    //FirstTask();
    //SecondTask();
    //ThirdTask();
}

