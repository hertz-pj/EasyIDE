#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <Qsci/qsciscintilla.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

private:
    //Menu
    QMenu *fileMenu;            //文件菜单
    QMenu *buildMenu;           //构建菜单
    QMenu *aboutMenu;           //相关菜单

    //action
    QAction *newAction;         //新建
    QAction *saveAction;        //保存
    QAction *openAction;        //打开
    QAction *runAction;         //运行
    QAction *buildAction;       //编译
    QAction *aboutAction;       //关于我们

    //toolBar
    QToolBar *fileToolBar;      //文件工具栏，新建，打开，保存
    QToolBar *buildToolBar;     //编译，运行工具栏
    QToolBar *aboutToolBar;

    //textEdit
//    QTextEdit *textEdit;
    QsciScintilla *textEdit;    //代码编辑框

    QString curFilePath;        //当前打开文件的路径

private:
    //初始化函数
    void CreateActions();           //创建动作
    void CreateMenus();             //创建菜单
    void CreateToolBars();          //创建工具栏

    void initUI();                  //初始化界面
    void deleteUI();                //清除构建的元素，防止内存泄漏
    void setTextEdit();

//槽函数
private slots:
    void NewFile();
    void SaveFile();
    void OpenFile();
    void Run();
    void Build();
    void About();
};

#endif // MAINWINDOW_H
