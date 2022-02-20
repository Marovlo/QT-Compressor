#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"func.h"
#include"hf_node.h"
#include"cmp_g.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void zip_clicked();
    void unzip_clicked();
    void about_triggered();
    void tips_triggered();
    void pb_choose_chlicked();


private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
