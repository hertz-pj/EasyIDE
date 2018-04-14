#include "demoview_widget.h"
#include "ui_demoview_widget.h"

#include <QDir>
#include <QDebug>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <mainwindow.h>

demoView_widget::demoView_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::demoView_widget)
{
    ui->setupUi(this);

    QString rootStr = "D:/graduation_project/EasyIDE/build-EasyIDE-Desktop_Qt_5_10_0_MinGW_32bit-Release/release/demo";
    qDebug() << rootStr;
    QStringList filter;         //过滤器
    filter << "*.cpp";          //只读取cpp文件

    model = new QFileSystemModel;

    model->setRootPath(rootStr);
    model->setNameFilterDisables(false);
    model->setNameFilters(filter);

    treeView = new QTreeView(this);
    treeView->setModel(model);
    treeView->setRootIndex(model->index(rootStr));

    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);

    treeView->header()->hide();     //隐藏header

    this->createButton();

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(exitButton);
    layout->addWidget(treeView);
    layout->addLayout(buttonLayout);
    setLayout(layout);
}

demoView_widget::~demoView_widget()
{
    delete ui;
}

/**
 * @brief demoView_widget::createButton
 * 创建按钮函数
 */
void demoView_widget::createButton()
{
    openButton = new QPushButton(tr("Open"), this);
    exitButton = new QPushButton(tr("Exit"), this);

    connect(openButton, SIGNAL(clicked()),
            this, SLOT(OpenDemo()));
    connect(exitButton, SIGNAL(clicked()),
            this, SLOT(Exit()));
}

void demoView_widget::OpenDemo()
{
    QModelIndex index = treeView->currentIndex();   //获取当前选中的文件

    if(!index.isValid() || model->fileInfo(index).isDir())
    {
        return;
    }
    QString path = model->filePath(index);
    qDebug() << path;

    emit SendPath(path);
    this->close();
}

void demoView_widget::Exit()
{
    this->close();
}
