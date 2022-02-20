#include "func.h"

hf_node* create_huffman_tree(g_queue a)//这是根据优先队列创建哈夫曼树的函数，从这个函数可以看出使用优先队列对于建立哈夫曼树的独特便捷性
//我们知道哈夫曼树的建立是将权值最小的两个节点相连并和为一个权值相加的新的父亲节点，那么如何从队列里面得到权值最小的两个节点呢，这时候
//按照权值早已排好序的优先队列便有极大的优势
{
    hf_node* root = nullptr;//建立一个空的根节点
    if (a.empty())//当队列为空时，返回当根节点
    {
        return root;
    }
    int i = -1;//新建一个为-1（即表示不存在的ascii值），用于存到所有不是叶子节点的节点中，以表示这不是叶子节点
    while (a.size() > 1)//当队列还剩一个节点之前
    {
        hf_node* ltemp_child = a.top();//取出队列中最顶上的元素作为左孩子
        a.pop();//删除这个元素
        hf_node* rtemp_child = a.top();//取出队列现在最顶上的元素作为右孩子
        a.pop();//删除这个元素
        hf_node* parent = new hf_node(i, ltemp_child->weight + rtemp_child->weight);//新建一个父亲节点，调用构造函数，使用i作为
        //其ascii码以表示并不是一个编码节点，不是一个叶子节点，他的权重是刚才取出来的两个孩子节点的和
        parent->lchild = ltemp_child;//将父亲节点与孩子节点相连接
        parent->rchild = rtemp_child;
        a.push(parent);//将该父亲节点放会优先队列中去，继续生成树，注意，此刻在放入新的父亲节点的那一刻，优先队列会自动帮你排序，
        //找到适合这个新的父亲节点的位置，使得下次循环时取出来的两个节点依然是权值最小的两个节点

        i--;

        //注意注意注意，非常重要的地方出现啦，看似一个毫无作用的i--，实际上确是相当重要的，没有这一步，整个解压将无法进行

        //为什么呢，因为虽然我们在优先队列的仿函数里面写了先以权重，即字符出现次数排序，若出现次数相同，再以ascii的大小进行排序

        //因为每个节点的权重可能相同，但ascii不可能相同，这就保证了优先队列排序的唯一性，不会出现每次打开程序，输入相同的东西却得到不同的结果的问题

        //可是为什么还要i--呢，因为我们在创建树的时候会生成一些父亲节点，这些节点的不代表任何编码，他们的ascii码为负值，可是如果他们的ascii都为-1，再加上他们权重也偶然的相同的话

        //在优先队列上就会出现无法预测的结果，我们无法知道一个ascii为-1权重为10的父亲节点和另一个ascii码为-1权重为10的完全相同的节点，谁会在前，谁会在后

        //而这两个父亲节点身上所背的孩子又是不一样的，这就会导致在压缩的时候和解压的时候，明明用于创建哈夫曼树的优先队列是一模一样的，然而创建出来的

        //哈夫曼树却会大不相同（归根结底时优先队列使用快速排序这种不稳定的排序方式，无法预测相同节点的位置），导致在解压时爬树的操作得到完全不同的结果，这样的话能压缩也能解压，但是解出来的东西和原来就完全不同了

        //所以我们在创建父亲节点的时候，给每个父亲节点一个不同的负的ascii码值，这样就不会存在不确定排序所造成的问题，不管是解压还是加压

        //用同一个优先队列调用的同一个建树函数所得到的哈夫曼树就完全一样了
    }
    root = a.top();//当队列中只剩下一个节点时，这就是我们需要的根节点，哈夫曼树就建好了
    a.pop();
    return root;
}

void generate_code(hf_node* root, string coding)//利用建好的哈夫曼树生成编码的函数，这是个递归函数
{
    string temp = coding;//记录当前coding状态，很重要
    if (root == nullptr)//树空则返回
    {
        return;
    }
    if (root->lchild != nullptr)//对每个节点进行遍历，如果当前节点的左孩子不为空，则向左遍历
    {
        coding += '0';//根据哈夫曼树的规则，编码加0
        generate_code(root->lchild, coding);//继续遍历左孩子
        coding = temp;//函数调用结束后，从左子树出来之后恢复到进入左子树之前的状态
    }//再进入右子树
    if (root->rchild != nullptr)
    {
        coding += '1';//同上，右子树不为空，编码加1
        generate_code(root->rchild, coding);
        coding = temp;//回复调用函数之前的状态
    }
    else if (root->lchild == nullptr && root->rchild == nullptr)//若左右孩子都为空，则我们到了一个叶子节点，该节点的ascii应该是大于等于零的
    {
        root->code = temp;//将得到的编码写入当前节点的编码中
        return;//当前函数调用结束
    }
}

void write_head(g_queue a, QFile &fp_write)//向文件中写头的函数
{
    QString head = "code_numbers:" + QString::number(a.size()) + " last_valid:"+QString::number(last_valid_bit(a)) + " ";
    fp_write.write(head.toUtf8());
    while (!a.empty())//当优先队列不为空时
    {
        head = QString::number(a.top()->ascii) + "+" + QString::number(a.top()->weight)+" ";
        fp_write.write(head.toUtf8());
        //将队列里面的第一个节点的ascii码，权值，和编码写入压缩文件中，为解压做准备
        a.pop();
    }
}

int last_valid_bit(g_queue a)//计算最后有效位的函数
{
    int sum = 0;//
    while (!a.empty())//当优先队列不为空
    {
        sum += a.top()->code.size() * a.top()->weight;//sum等于sum加当前节点的编码的长度乘以当前节点在文件中出现的次数
        sum %= 8;//sum模八，因为最后有效位数处于0到8之间
        a.pop();
    }
    return (sum == 0) ? 8 : sum;//不存在0个有效，若最后模8为0，则为8位有效；
}

QString from_string(string str)
{
    QString qstr=QString::fromLocal8Bit(str.c_str());
    return qstr;
}

string from_qstring(QString qstr)
{
    string str=(const char*)qstr.toLocal8Bit();
    return str;
}

