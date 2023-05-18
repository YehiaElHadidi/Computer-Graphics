//
// Created by lenovo on 5/16/2023.
//

#ifndef GRAPHICSPROJECT_FILLINGALGORITHMS_H
#define GRAPHICSPROJECT_FILLINGALGORITHMS_H
// #include <Line.h>

void swap(MyPoint& P1,MyPoint& P2)
{
    MyPoint temp = P1;
    P1= P2;
    P2 = temp;
    return;
}

//Filling
typedef struct {
    int xmin,xmax;

} Table[1000];


void InitTable(Table t)
{
    for(int i =0; i<1000; i++)
    {
        t[i].xmin=INT_MAX;
        t[i].xmax=-INT_MAX;
    }
}

void Edge2Table(MyPoint P1, MyPoint P2, Table table)
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
    double invslope = (double)(P2.x-P1.x )/(P2.y-P1.y);

    while(y <P2.y)
    {
        if(x < table[y].xmin)
        {
                table[y].xmin =(int)ceil(x);
        } 
        if(x > table[y].xmax) 
        {
            table[y].xmax =(int)floor(x);
        }
        y++;
        x += invslope;
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
void Table2Screen(HDC hdc, Table table, COLORREF color)
{
        for(int i=0; i < 1000; i++)
        if(table[i].xmin < table[i].xmax)
            for(int j=table[i].xmin; j <= table[i].xmax; j++)
                SetPixel(hdc, j, i, color);
}

void ConvexFill(HDC hdc, MyPoint p[], int n, COLORREF color)
{
    Table table;
    InitTable(table);
    MyPoint v1 = p[n - 1];
    Polygon2Table(p,n,table);
    Table2Screen(hdc, table, color);
}

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


