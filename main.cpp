#include <iostream>
#include "SimpleTree.h"
struct A
{
    A(int _a, int _b) : a(_a), b(_b)
    {
        std::cout << "A(" << a <<"," <<b<<")" << std::endl;
    }


    A(const A& ot)
    {
        std::cout << "A copy(A" << ot.a <<"," <<ot.b<<")" << std::endl;
        a = ot.a;
        b = ot.b;
    }

    A(A&& ot) noexcept
    {
        std::cout << "A move(A" << ot.a <<"," <<ot.b<<")" << std::endl;
        a = std::move(ot.a);
        b = std::move(ot.b);

    }

    A& operator=(const A& ot)
    {
        a = ot.a;
        b = ot.b;
        std::cout << "copy(" << ot.a <<"," <<ot.b<<")" << std::endl;
        return *this;
    }
    A& operator=( A&& ot) noexcept
    {

        a = std::exchange(ot.a, 0);
        b = std::exchange(ot.b, 0);
        std::cout << "move(" << a <<"," <<b<<")" << std::endl;
        return *this;
    }
    ~A()
    {
        std::cout <<"~A" << std::endl;
    }
    int a;
    int b;
    friend std::ostream& operator<<(std::ostream& os, const A& dt);
};

std::ostream& operator<<(std::ostream& os, const A& dt)
{
    os << dt.a << '/' << dt.b;
    return os;
}

int main()
{
    std::cout << "Hello World!" << std::endl;
    A a(44,44);
    A* b = new A(666,666);

    TreeNode<A> tree(A(6,7));
    tree.addChild(A(6,7));
    tree.addChild(A(6,7));
    tree.addChild(A(8,9));
    tree.getChildren()[2]->addChild(A(1,1));
    tree.getChildren()[2]->addChild(A(3,42));
    tree.getChildren()[2]->getChildren()[0]->addChild(A(53,24));
    tree.print();

    tree.removeChildByIndex(2);
    tree.removeChildByIndex(3);
    tree.print();

//    TreeNode<int> tree2(5);
//    tree2.addChild(11);
//    tree2.addChild(22);
//    tree2.print();

    return 0;
}
