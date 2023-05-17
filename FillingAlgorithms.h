//
// Created by lenovo on 5/16/2023.
//

#ifndef GRAPHICSPROJECT_FILLINGALGORITHMS_H
#define GRAPHICSPROJECT_FILLINGALGORITHMS_H

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
