#include "pch.h"
#include "Widget.h"


int Widget::nextId = 0;

Widget::Widget()
{
    id = nextId++;
}

int Widget::GetId() const
{
    return id;
}
