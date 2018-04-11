#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
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
    QAction *egebuildAction;    //编译ege程序
    QAction *demoAction;        //打开demo管理器


    //toolBar
    QToolBar *fileToolBar;      //文件工具栏，新建，打开，保存
    QToolBar *buildToolBar;     //编译，运行工具栏
    QToolBar *aboutToolBar;     //相关工作栏

    //QgridLayout
    QVBoxLayout *mainLayout;    //格子布局


    //textEdit
//    QTextEdit *textEdit;
    QsciScintilla *textEdit;    //代码编辑框
    QTextEdit *LogText;         //build log text;
    QString curFile;            //当前打开文件的路径

private:
    //初始化函数
    void CreateActions();           //创建动作
    void CreateMenus();             //创建菜单
    void CreateToolBars();          //创建工具栏

    void initUI();                  //初始化界面
    void deleteUI();                //清除构建的元素，防止内存泄漏
    void setTextEdit();             //初始化编辑器，并将代码编辑器放在窗口中间
    void initLogtext();             //初始化编译日志text

    bool SaveAs();                  //另存为
    bool SaveFile(const QString &fileName);     //根据路径将文件保存
    void setCurrentFile(const QString &fileName);   //设定当前文件路径名
    void LoadFile(const QString &fileName);         //读取文件
    bool LoadLogFile(const QString &fileName);      //读取编译信息文件
    void SeterrorMarker(int line);                  //设置错误指标
    int GeterrorLine(const QString &errorInfo);     //提取错误行数

//槽函数
private slots:
    void NewFile();
    bool Save();
    void Open();
    void Run();
    bool Build();
    bool EgeBuild();        //用于编译ege
    void RunEge();          //用于运行ege程序
    void About();
    void DemoConsole();     //打开demo控制器
};

#endif // MAINWINDOW_H
