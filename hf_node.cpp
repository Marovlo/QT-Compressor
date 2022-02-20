#include "hf_node.h"

hf_node::hf_node(int ascii_num, int weight)//该函数以输入的ascii值和权重初始化一个节点，其余为空
{
    this->ascii = ascii_num;
    this->weight = weight;
    this->rchild = nullptr;
    this->lchild = nullptr;
}
hf_node::hf_node()//该函数将节点全部置空
{
    this->ascii = -1;//不存在的ascii码
    this->weight = -1;//不存在的权值
    this->rchild = nullptr;
    this->lchild = nullptr;
}
