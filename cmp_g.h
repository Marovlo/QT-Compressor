#ifndef CMP_G_H
#define CMP_G_H
#include"hf_node.h"

struct cmp_g //重载优先队列中的判断方法的仿函数，注意说是函数实质上是一个结构体，所以叫仿函数
{//重写仿函数
    bool operator()(hf_node* a, hf_node* b); //重载（）操作符
};

#endif // CMP_G_H
