#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <windows.h>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

#include <Qsci/qsciapis.h>
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

    mainLayout = new QVBoxLayout;
    //设置代码编辑框
    this->setTextEdit();
    //设置bulid log text；
//    this->initLogtext();


//    mainLayout->addWidget(textEdit);
////    mainLayout->addWidget(LogText);
//    setLayout(mainLayout);
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
    connect(openAction, SIGNAL(triggered()), this, SLOT(Open()));

    //保存
    saveAction = new QAction(QIcon(":/images/filesave.png"), tr("&保存"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("保存文件"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(Save()));

    //运行
    runAction = new QAction(QIcon(":/images/run.png") ,tr("&运行"), this);
    runAction->setStatusTip(tr("运行该程序"));
    connect(runAction, SIGNAL(triggered()), this, SLOT(Run()));

    //构建
    buildAction = new QAction(QIcon(":/images/compile.png"), tr("&编译"), this);
    buildAction->setStatusTip(tr("构建该程序"));
    connect(buildAction, SIGNAL(triggered()), this, SLOT(Build()));

    //相关
    aboutAction = new QAction(QIcon(":/images/about.png") ,tr("&关于"), this);
    aboutAction->setStatusTip(tr("关于我们"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(About()));
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
    QsciLexerCPP *textLexer = new QsciLexerCPP;     //C++词法分析器
//    textLexer->setColor(QColor(Qt:: yellow),QsciLexerCPP::CommentLine);    //设置自带的注释行为绿色
    textEdit->setLexer(textLexer);      //添加c++词法分析器
    textEdit->setAutoIndent(true);      //添加自动缩进

    //使用utf-8编码
    textEdit->setUtf8(true);

    //自动补齐
    QsciAPIs *apis = new QsciAPIs(textLexer);
    apis->add(QString("int"));
    apis->prepare();

    textEdit->setAutoCompletionSource(QsciScintilla::AcsAPIs);
    textEdit->setAutoCompletionCaseSensitivity(true);
    textEdit->setAutoCompletionThreshold(1);
    textEdit->setAutoCompletionFillupsEnabled(true);

    //设置行数区域
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
//    mainLayout->addWidget(textEdit);
}

void MainWindow::NewFile()
{
    textEdit->clear();
}

/**
 * @brief MainWindow::Save
 * 该函数实现保存到当前路径操作，如果该文件未保存过，调用SaveAs;
 * @return bool
 */
bool MainWindow::Save()
{
    if (curFile.isEmpty())
    {
        SaveAs();
    }
    else
    {
        return SaveFile(curFile);
    }
}

void MainWindow::Open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        LoadFile(fileName);
    }
}

/**
 * @brief MainWindow::Run
 * 运行程序
 */
void MainWindow::Run()
{
    QString destFile = curFile;
    destFile.replace(".cpp", "");
    QString Bcmd = "g++ -o "+ destFile + " " +curFile;
    QString Rcmd = "cmd /c " + destFile;
    qDebug() << Rcmd;
//    system(command.toStdString().data());
    WinExec(Rcmd.toStdString().data(), SW_NORMAL);
}

/**
 * @brief MainWindow::Build
 * 构建程序
 */
void MainWindow::Build()
{
    Save();     //对改动的代码进行保存
    QString destFile = curFile;
    destFile.replace(".cpp", "");       //去除后缀

    //调用g++编译命令并将编译信心输出到.log文件
    QString command = "cmd /c g++ -o "+ destFile + " " +curFile
            + " 2> " + destFile +".log";
    qDebug() << command;
    WinExec(command.toStdString().data(), SW_HIDE);     //SW_HIDE参数隐藏dow框

}

/**
 * @brief MainWindow::About
 * 编译程序
 */
void MainWindow::About()
{
    QMessageBox::about(this, tr("关于我们"),
                       tr("这是一个简易的c语言编辑器"
                          "主要面向中小学生初学者"
                          "请联系我xxxxx@foxmail.com"));
}

/**
 * @brief MainWindow::SaveAs
 * @return 存储成功返回true，失败返回false
 * 另存为
 */
bool MainWindow::SaveAs()
{
    //通过对话框获取文件名路径
    QString fileName = QFileDialog::getSaveFileName(this,
            "", //对话框标题
            "", //默认路径
            tr("C++文件 (*.cpp)"));
    if (fileName.isEmpty())
        return false;

    return SaveFile(fileName);
}

/**
 * @brief MainWindow::SaveFile
 * 实现将文件保存至fileName路径
 * @param fileName
 * @return bool
 */
bool MainWindow::SaveFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly))
    {
        QMessageBox::warning(this, tr("简易编辑器"),
                             tr("不能存储文件 %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    //写入文件操作
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->text();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);       //设定当前文件内容

    return true;
}

/**
 * @brief MainWindow::LoadFile
 * 该函数用于读取文档
 * @param fileName
 */
void MainWindow::LoadFile(const QString &fileName)
{
    QFile file(fileName);

    //判断文件是否打开，没打开不执行
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("简易编辑器"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    //读取文件内容
    QTextStream in(&file);

    //设置光标
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
}

void MainWindow::initLogtext()
{
    LogText = new QTextEdit;
    LogText->setReadOnly(true);     //设置日志编辑器不可编辑

    mainLayout->addWidget(LogText);
}
