#include "demoview_widget.h"
#include "ui_demoview_widget.h"

#include <QDir>

demoView_widget::demoView_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::demoView_widget)
{
    ui->setupUi(this);

    QString rootStr = "/";
    QDir rootDir(rootStr);
    QStringList stringlist;
    stringlist << "*";
    QFileInfoList list;
    list = rootDir.entryInfoList(stringlist);

//    rootDir.entryInfoList();
}

demoView_widget::~demoView_widget()
{
    delete ui;
}
