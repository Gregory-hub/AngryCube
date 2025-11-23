#pragma once

class Widget
{
private:
    static int nextId;
    int id;

public:
    Widget();
    virtual ~Widget() = 0;

    int GetId() const;
    virtual void Render() const = 0;
    virtual void Reset() { };
};

inline Widget::~Widget() = default;
