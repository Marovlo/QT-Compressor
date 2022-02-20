#ifndef FUNC_H
#define FUNC_H
#include<iostream>
#include<queue>
#include<vector>
#include<cstdlib>
#include<string>
#include"hf_node.h"
#include"cmp_g.h"
#include"qstring"
#include<qfile.h>
using namespace std;

//简单介绍一下优先队列的作用，优先队列是当用户在告知优先队列排序方法之后，所有用户存进队列的元素都会自动按照所给的方法排列
//相当于一个自动排序队列
typedef priority_queue<hf_node*, vector<hf_node*>, cmp_g> g_queue;//可以看到优先队列的三个参数
//第一个为队列中要存储的元素类型；
//第二个为队列的底层实现方法，虽然名字叫优先队列，但实质上因为涉及到排序的问题，这个东西的底层根本就不是一个队列，而是一个可以移动内部元素位置的容器，像是向量或者list都可以，这里选用的是向量vector，但是要理解的一点是，
//注意，虽然底层是向量，优先队列表面上还是一个队列的样子，只有队列的那些操作比如top（），pop（），push（），等等，而没有向量的insert（），begin（）等操作；
//第三个参数是刚才写好的如何排序的对（）进行重载的结构体

void write_head(g_queue a, QFile &fp_write);//向压缩文件中写入必要信息头的函数

hf_node* create_huffman_tree(g_queue a);//利用优先队列创建哈夫曼树的函数，返回根节点

void generate_code(hf_node* root, string coding);//利用遍历哈夫曼树生成每个叶子节点的编码的函数。

int last_valid_bit(g_queue a);//用于计算该文件在编码之后最后一个八位里面有几个位是有效的，有几个位是无效的垃圾位

void compress(string file_path);

string from_qstring(QString qstr);

QString from_string(string str);

typedef struct temp_node//一个用于临时存储ascii与weight的结构体
{
    int ascii_num;
    int times;
}temp_node;

#endif // FUNC_H
