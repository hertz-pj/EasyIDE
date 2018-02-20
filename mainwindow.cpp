#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化UI
    initUI();

    //生成菜单，工具栏等
    this->CreateActions();
    this->CreateMenus();
    this->CreateToolBars();

    //设置代码编辑框
    this->setTextEdit();
}

MainWindow::~MainWindow()
{
    delete ui;
    deleteUI();
}

/**
 * @brief MainWindow::CreateActions
 * 创建Action，并连接信号槽
 */
void MainWindow::CreateActions()
{
    //新建
    newAction = new QAction(QIcon(":/images/filenew.png"), tr("&新建"), this);
    newAction->setStatusTip(tr("创建一个新的文件"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(NewFile()));

    //打开
    openAction = new QAction(QIcon(":/images/fileopen.png"), tr("&打开..."), this);
    openAction->setStatusTip(tr("打开一个现有文件"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(OpenFile()));

    //保存
    saveAction = new QAction(QIcon(":/images/filesave.png"), tr("&保存"), this);
    saveAction->setStatusTip(tr("保存文件"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(SaveFile()));

    runAction = new QAction(QIcon(":/images/run.png") ,tr("&运行"), this);
    buildAction = new QAction(QIcon(":/images/compile.png"), tr("&编译"), this);
    aboutAction = new QAction(QIcon(":/images/about.png") ,tr("&关于"), this);
}

/**
 * @brief MainWindow::CreateMenus
 * 创建菜单
 */

void MainWindow::CreateMenus()
{
    //文件菜单
    fileMenu = menuBar()->addMenu(tr("&文件"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    //构建菜单
    buildMenu = menuBar()->addMenu((tr("&构建")));
    buildMenu->addAction(buildAction);
    buildMenu->addAction(runAction);

    //关于菜单
    aboutMenu = menuBar()->addMenu(tr("&其他.."));
    aboutMenu->addAction(aboutAction);
}

/**
 * @brief MainWindow::CreateToolBars
 * 创建工具栏
 */
void MainWindow::CreateToolBars()
{
    //文件工具栏
    fileToolBar = addToolBar(tr("&文件"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    //构建工具栏
    buildToolBar = addToolBar(tr("&编译"));
    buildToolBar->addAction(buildAction);
    buildToolBar->addAction(runAction);

    //创建about工具栏
    aboutToolBar = addToolBar(tr("&相关"));
    aboutToolBar->addAction(aboutAction);
}

/**
 * @brief MainWindow::initUI
 * 初始化UI，设置窗口大小及位置
 */
void MainWindow::initUI()
{
//    this->setVisible(false);        //先设置不可见
    this->setWindowTitle(QObject::tr("简洁c语言编辑器"));
    this->setWindowIcon(QIcon(":/images/windowIcon.png"));

    QDesktopWidget *desktop = QApplication::desktop();

    //获取系统默认桌面大小
    QRect deskRect = desktop->screenGeometry(desktop->primaryScreen());

    float multiple = 3.0/5;
    this->setMinimumSize(multiple*deskRect.width(),
                       multiple*deskRect.height());             // 设置大小为3/5
    this->move(0.5*(1-multiple) * deskRect.width(),
               0.5 * (1 - multiple) * deskRect.height());       // 移动窗口位置
}

void MainWindow::deleteUI()
{
    //QT自己的资源会自己释放，不需要再次释放。
//    delete newAction;         //新建
//    delete saveAction;        //保存
//    delete openAction;        //打开
//    delete runAction;         //运行
//    delete buildAction;       //编译
//    delete aboutAction;       //关于我们
}

/**
 * @brief MainWindow::setTextEdit
 * 该函数用于初始化编辑框
 */
void MainWindow::setTextEdit()
{
    //编辑框
    textEdit = new QsciScintilla;
    QsciLexerCPP *textLexer = new QsciLexerCPP;
    textLexer->setColor(QColor(Qt:: yellow),QsciLexerCPP::CommentLine);    //设置自带的注释行为绿色
    textEdit->setLexer(textLexer);

    //设置行数
    textEdit->setMarginType(0, QsciScintilla::NumberMargin);
    textEdit->setMarginLineNumbers(0, true);
    textEdit->setMarginWidth(0,30);

    //自动折叠区域
//    textEdit->setMarginType(3, QsciScintilla::SymbolMargin);
//    textEdit->setMarginLineNumbers(3, false);
//    textEdit->setMarginWidth(3, 15);
//    textEdit->setMarginSensitivity(3, true);

    //将编辑框设置到窗口中间部分
    this->setCentralWidget(textEdit);
}

void MainWindow::NewFile()
{

}

void MainWindow::SaveFile()
{

}

void MainWindow::OpenFile()
{

}

void MainWindow::Run()
{

}

void MainWindow::Build()
{

}

void MainWindow::About()
{

}
