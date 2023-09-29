//Добавить в иерархию посетителей (см. пример в презентации)
//ещё один класс посетителя DrawVisitor.Он должен уметь
//рисовать фигуры(для Circle просто в виде сообщения “Drawing Circle”)

#include <iostream>
#include <vector>

class Square;
class Circle;
class Rectangle;

//Абстрактный класс посетитель
class Visitor {
public:
    virtual void visit(Square& square)abstract;
    virtual void visit(Circle& circle)abstract;
    virtual void visit(Rectangle& rectangle)abstract;
};

//Абстрактный класс фигуры
class Shape {
public:
    virtual void accept(Visitor& visitor)abstract;
};

//Конкретные классы фигур
class Square :public Shape {
    double m_side;
public:
    Square(double side):m_side(side){}
    double area()const { return m_side * m_side; }
    void accept(Visitor& visitor)override {
        visitor.visit(*this);
    }
    double getM_side() {
        return m_side;
    }
};

class Circle :public Shape {
    double m_radius;
public:
    Circle(double radius) :m_radius(radius) {}
    double area()const { return 3.14159265359 * m_radius * m_radius; }
    void accept(Visitor& visitor)override {
        visitor.visit(*this);
    }
    double getM_radius() {
        return m_radius;
    }
};

class Rectangle :public Shape {
    double m_width;
    double m_height;
public:
    Rectangle(double width, double height) :m_width(width), m_height(height) {}
    double area()const { return  m_width * m_height; }
    void accept(Visitor& visitor)override {
        visitor.visit(*this);
    }
    double getM_width() {
        return m_width;
    }
    double getM_height() {
        return m_height;
    }
};

//Конкретный класс посетителя, реализующий операцию расчета периметра для
//каждой фигуры
class PerimeterVisitor :public Visitor {
    double m_perimeter = 0.0;
public:
    void visit(Square& square)override {
        m_perimeter += 4 * square.getM_side();
    }
    void visit(Circle& circle)override {
        m_perimeter += 2 * 3.14159265359 * circle.getM_radius();
    }
    void visit(Rectangle& rectangle)override {
        m_perimeter += 2 * (rectangle.getM_width() + rectangle.getM_height());
    }
    double perimeter()const { return m_perimeter; }
};

//Класс посетителя, реализующий рисование фигур
class DrawVisitor :public Visitor {
public:
    void visit(Square& square)override {
        for (int i = 0; i < square.getM_side(); i++) {
            for (int j = 0; j < square.getM_side(); j++) {
                if (i == 0 || i == (square.getM_side() - 1)) {
                    std::cout << "- ";
                }
                else if (j == 0 || j == (square.getM_side() - 1)) {

                    std::cout << "| ";
                }
                else {
                    std::cout << "  ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void visit(Rectangle& rectangle)override {
        for (int i = 0; i < rectangle.getM_width(); i++) {
            for (int j = 0; j < rectangle.getM_height(); j++) {
                if (i == 0 || i == (rectangle.getM_width() - 1)) {
                    std::cout << "- ";
                }
                else if (j == 0 || j == (rectangle.getM_height() - 1)) {

                    std::cout << "| ";
                }
                else {
                    std::cout << "  ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void visit(Circle& circle)override {
        std::cout << "Drawing a circle with a side " << circle.getM_radius() << "\n\n";
    }
};

int main()
{
    std::vector<Shape*>shapes = { new Square(10), new Circle(7), new Rectangle(9,15) };
    
    PerimeterVisitor perimeterVisitor;
    for (auto shape : shapes) {
        shape->accept(perimeterVisitor);
    }
    std::cout << "Total perimetr: " << perimeterVisitor.perimeter() << "\n\n";

    DrawVisitor drawVisitor;
    for (auto shape : shapes) {
        shape->accept(drawVisitor);
    }

    //Очистка памяти
    for (auto shape : shapes) {
        delete shape;
    }
}
