#include "cmp_g.h"

bool cmp_g::operator()(hf_node* a, hf_node* b) //重载（）操作符
{
    if (a->weight != b->weight)//在优先队列中首先判断两节点的权重，从小到大储存，越小的越靠近队列的顶部
    {
        return a->weight > b->weight;
    }
    else//若权重相同，则以ascii码的先后顺序从小到大储存
    {
        return a->ascii > b->ascii;
    }
}
