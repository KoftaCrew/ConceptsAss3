#include <iostream>
using namespace std;

struct Shape;

struct ShapeVTable{
    double (*GetArea) (Shape*);
    void (*PrintInfo) (Shape*);
};

struct Shape{
    ShapeVTable *vTable;
};

double GetArea(Shape * shape){
    return shape->vTable->GetArea(shape);
}

void PrintInfo(Shape* shape){
    shape->vTable->PrintInfo(shape);
}

struct Circle{
    Shape parent;
    int radius;
};

struct Rectangle{
    Shape parent;
    int width, length;
};

struct Ellipse{
    Shape parent;
    int a, b;
};

double CircleGetArea(Circle *circle){
    return circle->radius*circle->radius*3.14;
}

void CirclePrintInfo(Circle *circle){
    cout << "This is a circle of radius : " << circle->radius << "\n";
}

ShapeVTable circleVTable = {
        (double (*)(Shape *)) CircleGetArea,
        (void (*)(Shape *)) CirclePrintInfo,
};

void CircleInitialize(Circle* circle, int r){
    circle->radius = r;
    circle->parent.vTable = &circleVTable;
}

double EllipseGetArea(Ellipse *e){
    return e->a * e->b * 3.14;
}

void EllipsePrintInfo(Ellipse *e){
    cout << "This is an ellipse of A : " << e->a << " and B : " << e->b << "\n";
}

ShapeVTable EllipseVTable = {
        (double (*)(Shape *)) EllipseGetArea,
        (void (*)(Shape *)) EllipsePrintInfo,
};

void EllipseInitialize(Ellipse* e, int a, int b){
    e->a = a;
    e->b = b;
    e->parent.vTable = &EllipseVTable;
}

double RectangleGetArea(Rectangle *rectangle){
    return rectangle->length * rectangle->width;
}

void RectanglePrintInfo(Rectangle *rectangle){
    cout << "This is a rectangle of length : " << rectangle->length << " and with : " << rectangle->width << "\n";
}

ShapeVTable RectangleVTable = {
        (double (*)(Shape *)) RectangleGetArea,
        (void (*)(Shape *)) RectanglePrintInfo,
};

void RectangleInitialize(Rectangle* rectangle, int l, int w){
    rectangle->parent.vTable = &RectangleVTable;
    rectangle->length = l;
    rectangle->width = w;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10
    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5
    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12
    Shape* shapes[3];
    shapes[0]=(Shape*)&circle ;
    shapes[1]=(Shape*)&rectangle ;
    shapes[2]=(Shape*)&ellipse ;
    double total_area=0;
    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }

    cout<<total_area<<endl; // check if the value is correct
    return 0;
}