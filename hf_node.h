#ifndef HF_NODE_H
#define HF_NODE_H
#include<string>
using namespace  std;

class hf_node
{
public:
    int ascii;//储存该节点的ascii值
    int weight;//储存该ascii值的权重
    hf_node* rchild;//左孩子
    hf_node* lchild;//右孩子
    string code;//储存该ascii对应的字符的编码
    //结构的同名函数，用于在声明结构时候的初始化，类似于类的构造函数
    hf_node(int ascii_num, int weight);//该函数以输入的ascii值和权重初始化一个节点，其余为空
    hf_node();
};

#endif // HF_NODE_H
