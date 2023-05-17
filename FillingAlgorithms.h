//
// Created by lenovo on 5/16/2023.
//

#ifndef GRAPHICSPROJECT_FILLINGALGORITHMS_H
#define GRAPHICSPROJECT_FILLINGALGORITHMS_H
// #include <Line.h>

typedef struct {
    int x_min,x_max;

} Table[1000];

// struct ConvexPoint
// {
//     int x, y;
//     ConvexPoint(int x=0,int y=0):x(x),y(y){}

// } ;

void InitTable(Table t)
{
    for(int i =0; i<1000; i++)
    {
        t[i].x_max=INT_MAX;
        t[i].x_min=-INT_MAX;
    }
}

void swap(MyPoint& P1,MyPoint& P2)
{
    MyPoint temp = P1;
    P1= P2;
    P2 = temp;
    return;
}
void Edge2Table(MyPoint P1,MyPoint P2, Table table)
{
    // Horizontal Case
    if(P1.y==P2.y) return;

    if(P1.y > P2.y)
    {
        swap(P1,P2);
        // swap(P1.x,P2.x);
        // swap(P1.y,P2.y);
    }

    double x = P1.x;
    int y=P1.y;
    double slope = (P2.x-P1.x )/(P2.y-P1.y);

    while(y <P2.y)
    {
        if(x < table[y].x_min) 
            table[y].x_min =(int)ceil(x);
        if(x > table[y].x_max) 
            table[y].x_max =(int)floor(x);
        y++;
        x += slope;
    }

}

void Polygon2Table(MyPoint points[], int size, Table table)
{
    MyPoint v1 = points[size-1];

    for(int i=0; i < size; i++)
    {
        MyPoint v2= points[i];
        Edge2Table(v1, v2, table);
        v1 = v2;
    }
}

void Table2Screen(HDC hdc,Table table, COLORREF c)
{
    for(int i=0; i < 200; i++)
        if(table[i].x_min<table[i].x_max)
            for(int j=table[i].x_min; j <= table[i].x_max; j++)
                SetPixel(hdc, j, i, c);

}
void ConvexFilling(HDC hdc,MyPoint points[], int size, COLORREF color)
{
    Table table;
    InitTable(table);
    cout << "No Error 1" <<endl;
    Polygon2Table(points, size, table);
    cout << "No Error 2" <<endl;
    Table2Screen(hdc, table, color);
    cout << "No Error 3" <<endl;
}

// void ConvexFillInterface(HDC hdc, int size, COLORREF color,UINT message, LPARAM lParam)
// {
//     static MyPoint points[size];
//     static int count=0;
//     switch
//     points[count].x = LOWORD(lp)

// }

void RecursiveFloodFill(HDC hdc, int x, int y, COLORREF Cb, COLORREF Cf)
{
    COLORREF C = GetPixel(hdc, x, y);
    if (C == Cb || C == Cf)return;
    SetPixel(hdc, x, y, Cf);
    RecursiveFloodFill(hdc, x + 1, y, Cb, Cf);
    RecursiveFloodFill(hdc, x - 1, y, Cb, Cf);
    RecursiveFloodFill(hdc, x, y + 1, Cb, Cf);
    RecursiveFloodFill(hdc, x, y - 1, Cb, Cf);

}
struct Vertex
        {
    double x, y;
    Vertex(int x1 = 0, int y1 = 0)
    {
        x = x1;
        y = y1;
    }
        };
void NonRecursiveFloodFill(HDC hdc, int x, int y, COLORREF Cb, COLORREF Cf)
{
    stack<Vertex> myStack;

    myStack.push(Vertex(x, y));
    while (!myStack.empty())
    {
        Vertex v = myStack.top();
        myStack.pop();
        COLORREF c = GetPixel(hdc, v.x, v.y);
        if (c == Cb || c == Cf)continue;
        SetPixel(hdc, v.x, v.y, Cf);
        myStack.push(Vertex(v.x + 1, v.y));
        myStack.push(Vertex(v.x - 1, v.y));
        myStack.push(Vertex(v.x, v.y + 1));
        myStack.push(Vertex(v.x, v.y - 1));
    }
}



#endif //GRAPHICSPROJECT_FILLINGALGORITHMS_H


