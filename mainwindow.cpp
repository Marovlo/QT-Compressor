#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qmessagebox.h>
#include<qdebug.h>
#include<QProgressDialog>
#include<qfiledialog.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->zip->setDefault(true);
    connect(this->ui->zip,SIGNAL(clicked()),this,SLOT(zip_clicked()));
    connect(this->ui->unzip,SIGNAL(clicked()),this,SLOT(unzip_clicked()));
    connect(this->ui->actionabout,SIGNAL(triggered()),this,SLOT(about_triggered()));
    connect(this->ui->actiontips,SIGNAL(triggered()),this,SLOT(tips_triggered()));
    ui->le->setFocus();
    connect(this->ui->le,SIGNAL(returnPressed()),this->ui->zip,SLOT(click()));
    connect(this->ui->pb_choose,&QPushButton::clicked,this,&MainWindow::pb_choose_chlicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pb_choose_chlicked()
{
    QFileDialog filedio;
    filedio.setWindowTitle("选择文件");
    filedio.setDirectory("d:\\");
    QStringList filename;
    if(filedio.exec())
    {
        filename=filedio.selectedFiles();
    }
    if(filename.size()!=0)
    {
        this->ui->le->clear();
        this->ui->le->setText(filename[0]);
    }
}

void MainWindow::zip_clicked()
{
    QString file_path=this->ui->le->text();//防止出现中文乱码
    QString file_name;//用于得到新生成的文件名
    g_queue hf_tree_queue;//作为全局变量声明一个优先队列用于储存哈夫曼树的节点
    file_name=file_path;
    file_name += ".msy";//将文件名后面打上专属文件格式.msy（我才不会告诉你是我女朋友的名字，夹带私货）；
    QFile fp_read(file_path);
    QFile fp_write(file_name);
    if(file_path=="")
    {
        QMessageBox::warning(this,"警告","您未输入任何路径！",QMessageBox::Ok);
        return;
    }
    cout << file_path.toStdString().c_str();
    if (!fp_read.open(QIODevice::ReadOnly))
    {
       QMessageBox::critical(this, "错误", file_path.toStdString().c_str(), "OK");
       return;
    }
    if (!fp_write.open(QIODevice::WriteOnly))
    {
       QMessageBox::critical(this, "错误", "无法在指定文件夹创建压缩文件，请检查读写权限且请不要在C盘中操作", "OK");
       return;
    }
    unsigned char ch;//采用int存储char类型，这样不会出现中文的ascii码为负值的问题，从0到255，一共256个字符
    temp_node ascii[256];//创建一个临时储存256个字符出现次数的数组
    for (int i = 0; i < 256; i++)
    {
        ascii[i].ascii_num = i;//先将这数组的256个元素初始化为对应的ascii码
        ascii[i].times = 0;//出现次数现在都是0
    }
    this->ui->lb_status->setText("读取文件中，请稍候。。。");
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    qlonglong sum_length = 0;
    qlonglong len = 0;
    qlonglong gap = 10000;
    QByteArray content;
    while (!fp_read.atEnd())
    {
       content = fp_read.read(gap);
       len = content.length();
       sum_length += len;
       QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
       for (int i = 0; i < len; ++i)
       {
          ch = content[i];
          ascii[ch].times++;
       }
    }
    this->ui->lb_status->setText("构建哈夫曼树中，请稍后。");
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    for (temp_node i : ascii)//范围for，遍历ascii数组中的所有temp_node节点
    {
        if (i.times != 0)//当该节点的出现次数不为0时（为零的话没有统计的意义）
        {
            hf_node* temp = new hf_node(i.ascii_num, i.times);//以new的方式新建一个hf_node节点，调用其带参数的构造函数
            //使用当前临时节点的ascii值和出现次数来构造节点
            hf_tree_queue.push(temp);//将新得到的节点压入优先队列中，注意这里，每次压入一个节点，优先队列就会自动排序一次，保证整个队列从队列顶到队列尾从小到大排列
        }
    }
    if (hf_tree_queue.size() == 1)//判断当前优先队列的大小，如果等于一的话，退出，因为无意义
    {
        QMessageBox::StandardButton result=QMessageBox::question(this,"提示","对仅有一种字符的文件进行压缩无意义，您确定继续吗！",QMessageBox::Yes|QMessageBox::No);
        switch (result) {
        case QMessageBox::Yes:
        {
            break;
        }
        case QMessageBox::No:
        default:
        {
           fp_read.close();
           if (!fp_write.remove())
           {
              QMessageBox::information(this, "提示", "临时解压文件删除失败，请手动删除", QMessageBox::Ok);
           }
           this->ui->lb_status->setText("准备好了^_^");
           return;
        }
        }
    }
    if (hf_tree_queue.size() == 0)//优先队列为空，即读入的文件为空
    {
        QMessageBox::critical(this,"错误","待压缩文件为空，压缩取消!",QMessageBox::Yes);
        fp_read.close();
        fp_write.close();
        return;
    }
    hf_node* root = create_huffman_tree(hf_tree_queue);//调用函数，使用获得的优先队列建立哈夫曼树
    this->ui->lb_status->setText("生成哈夫曼编码中，请稍后。。。");
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    generate_code(root, "");//调用函数，遍历得到的树，生成对应ascii码的编码
    g_queue temp = hf_tree_queue;//复制一遍我们的优先队列，以便得到队列中每个字符的编码而不对原来的队列造成影响
    string codes[256];//创建一个字符串数组，用于存储每个ascii对应的编码串，采取以空间换时间的方式，使查找对应ascii的编码变成o（1）的复杂度
    while (!temp.empty())
    {
        codes[temp.top()->ascii] = temp.top()->code;//将temp中的每一个ascii对应的编码存到codes数组中
        temp.pop();//存完一个释放一个节点
    }
    ///*
    int flag = 0;//用于位运算的辅助操作数
    char _8_byte = 0x00;//一个要输入到文件中的字符，初始化为全零
    write_head(hf_tree_queue, fp_write);//先向文件中写入必要的头，方便关闭程序后再打开还能够解压，只需要得到文件的所有编码信息就可
    QProgressDialog process;
    process.setWindowTitle("压缩");
    process.setLabelText("压缩中，请稍后");
    process.setCancelButtonText("取消");
    process.setRange(0,sum_length);
    process.setModal(true);
    process.show();
    this->ui->lb_status->setText("压缩中，请稍后。。。");
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    qlonglong now = 0;
    int pos = fp_read.pos();
    fp_read.seek(0);
    pos = fp_read.pos();
    while (!fp_read.atEnd())
    {
       content = fp_read.read(gap);
       len = content.length();
       for (int i = 0; i < len; ++i)
       {
          ch = content[i];
          string now_code = codes[ch];//先从编码字符串数组中取出当前读到的字符对应的编码
          for (char i : now_code)//遍历当前编码字符串
          {
             if (i == '1')//如果为1
             {
                _8_byte |= (1 << (flag ^ 7));//将当前flag对应的那一位设置为1
             }
             flag++;//flag向后指，指向下一位
             if (flag == 8)//当flag==8的时候，表示我们已经把_8_byte的八个位都做了改动，已经是一个经过编码的字符了
                 //可以将他输出到文件中了
             {
                flag = 0;//将flag重新置为零
                fp_write.write(&_8_byte, 1);
                //fwrite(&_8_byte, sizeof(char), 1, fp_write);//向文件中写入得到的编码字符
                _8_byte = 0x00;//初始化_8_byte为0
             }
          }
       }
       now += len;
       process.setValue(now);
       if (process.wasCanceled())
       {
          if (!fp_write.remove())
          {
             QMessageBox::information(this, "提示", "临时解压文件删除失败，请手动删除", QMessageBox::Ok);
          }
          this->ui->lb_status->setText("准备好了^_^");
          return;
       }
       QApplication::processEvents();
    }
    if (flag != 0)//当文件读完之后，如果flag！=0表示最后还剩一些不足八位的编码需要写入，我们还是得把他们写入进文件
        //即使最后几个0会是垃圾位，到时候再来处理即可
    {
        //fwrite(&_8_byte, sizeof(unsigned char), 1, fp_write);
        fp_write.write(&_8_byte, 1);
        _8_byte = 0x00;
    }
    process.setValue(now);
    //至此压缩便完成了
    fp_write.close();
    fp_read.close();
    /*fclose(fp_read);
    fclose(fp_write);*/
    this->ui->lb_status->setText("准备好了^_^");
    QMessageBox::warning(this,"完成","压缩完成！",QMessageBox::Ok);
    this->ui->le->setText(file_name);
    this->ui->zip->setDefault(false);
    this->ui->unzip->setDefault(true);
}

void MainWindow::unzip_clicked()
{
    QString file_path=this->ui->le->text();//防止出现中文乱码
    QString file_name;
    QString old_name;
    if(file_path=="")
    {
        QMessageBox::warning(this,"警告","您未输入任何路径！",QMessageBox::Ok);
        return;
    }
    if (!file_path.contains(".msy"))
    {
        QMessageBox::critical(this,"错误","文件格式不支持，请使用标准的.msy格式压缩文件！",QMessageBox::Ok);
        return ;
    }
    else
    {
        file_name=file_path;
        file_name = file_name.replace(file_name.length()-4,4,"");
        //从文件路径中提取出文件名，并删去最后的.msy
        old_name=file_name;
        file_name.insert(file_name.lastIndexOf("/")+1, "unzipped_");//加上解压出的以示区分
    }
    QFile fp_read(file_path);
    QFile fp_write(file_name);
    if (!fp_read.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"错误","无法打开文件，请检查文件路径是否正确！");
        return;
    }
    if (!fp_write.open(QIODevice::WriteOnly))
    {
       QMessageBox::critical(this, "错误", "无法创建解压文件，请检查操作权限且请勿在C盘操作！");
       return;
    }
    int code_numbers = 0;
    int last_valid = 0;
    char tp[1];
    QByteArray content;
    int blank_count = 0;
    while (blank_count!=2)
    {
       fp_read.read(tp, 1);
       content.append(tp,1);
       if (tp[0] == ' ')blank_count++;
    }
    QString head(content);
    sscanf(content.toStdString().c_str(), "code_numbers:%d last_valid:%d ", &code_numbers, &last_valid);
    if (code_numbers == 0)//若没有字符
    {
        QMessageBox::critical(this,"错误","压缩文件为空，解压取消！",QMessageBox::Ok);
        fp_read.close();
        if (!fp_write.remove())
        {
           QMessageBox::information(this, "提示", "临时解压文件删除失败，请手动删除", QMessageBox::Ok);
        }
        return;
    }
    g_queue codes;//新建一个优先队列
    int ascii = 0;
    int weight = 0;
    this->ui->lb_status->setText("读取文件中，请稍后。。。");
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    qlonglong sum_char=0;
    for (int i = 0; i < code_numbers; i++)
    {
        content.clear();
        while (true)
        {
           fp_read.read(tp, 1);
           content.append(tp, 1);
           if (tp[0] == ' ')break;
        }
        sscanf(content.toStdString().c_str(), "%d+%d ", &ascii, &weight);
        hf_node* temp = new hf_node;
        temp->ascii = ascii;
        temp->weight = weight;
        sum_char+=weight;
        codes.push(temp);//利用从文件中读到的信息还原优先队列，必须确保和原来的优先队列完全一模一样，以保证建立的哈夫曼树的一模一样
    }
    this->ui->lb_status->setText("还原哈夫曼树中，请稍后。。。");
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    hf_node* root = create_huffman_tree(codes);//使用优先队列建立哈夫曼树
    int ch_next = 0;
    this->ui->lb_status->setText("解压中，请稍后。。。");
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    QProgressDialog process;
    process.setWindowTitle("解压");
    process.setLabelText("解压中，请稍后");
    process.setCancelButtonText("取消");
    process.setRange(0,sum_char);
    process.setModal(true);
    process.show();
    qlonglong gap = 10000;
    int len = 0;
    int ch = 0;
    int flag = 8;
    char to_write;
    qlonglong now = 0;
    hf_node* temp = root;
    int ff;
    while (!fp_read.atEnd())
    {
       content = fp_read.read(gap);
       len = content.length();
       flag = 8;
       for (int i = -1; ; )
       {
          if (flag == 8)
          {
             ++i;
             if (i == len)break;
             ch = content[i];
             flag = 0;
          }    
          int _now_bit = 1 << (flag ^ 7);//取出当前flag所对应的那个位的值，判断是零是一
          if ((ch & _now_bit) == 0)//是零的话，从树根向左孩子移动（哈夫曼树的生成方式）
          {
             temp = temp->lchild;
          }
          else if ((ch & _now_bit) == _now_bit)//是一的话向右孩子移动
          {
             temp = temp->rchild;
          }
          if (temp->ascii >= 0)//移动之后，判断当前节点是不是一个叶子节点
              //（即ascii码大于等于零，其他非叶子节点的ascii码在我们生成树的时候都设置为比0小的值，详情请见下面的生成树的函数），
              //若是叶子节点，则表示刚才的一番移动让我们来到了当前编码对应的节点，该节点里面存的ascii就是当前我们读过的编码对应的字符的ascii码
          {
             to_write = temp->ascii;
             fp_write.write(&to_write, 1);
             ff = flag + 1;
             if (fp_read.atEnd() && i == len - 1 && ff == last_valid)break;
             temp = root;//每次解码出一个字符后，重新回到树根重新开始
          }
          flag++;//移动完一次flag向后移一位
       }
       now += len;
       process.setValue(now);
       if (process.wasCanceled())
       {
          if (!fp_write.remove())
          {
             QMessageBox::information(this, "提示", "临时解压文件删除失败，请手动删除", QMessageBox::Ok);
          }
          this->ui->lb_status->setText("准备好了^_^");
          fp_read.close();
          return;
       }
       QApplication::processEvents();
    }
    fp_read.close();
    fp_write.close();
    process.setValue(sum_char);
    QMessageBox::information(this,"完成","解压完成！",QMessageBox::Ok);
    this->ui->lb_status->setText("准备好了^_^");
    this->ui->zip->setDefault(true);
    this->ui->le->setText(old_name);
}

void MainWindow::about_triggered()
{
    QMessageBox::information(this,"info","Author: Marovlo Yukiatsu ",QMessageBox::Ok);
}

void MainWindow::tips_triggered()
{
    QMessageBox::information(this,"小贴士","1：由于哈夫曼压缩算法本身的效率较为低下，对于txt文件压缩率较高，对其他已压缩过的文件效果不佳。\n2：由于文件头的写入，会发生在压缩很小的文件时，压缩后反而文件变大的问题。");
}
