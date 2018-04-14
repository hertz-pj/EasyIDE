#ifndef DEMOVIEW_WIDGET_H
#define DEMOVIEW_WIDGET_H

#include <QWidget>

#include <QFileInfoList>
#include <QListWidget>
#include <QListWidgetItem>

#include <QTreeView>
#include <QPushButton>
#include <QFileSystemModel>


namespace Ui {
class demoView_widget;
}

class demoView_widget : public QWidget
{
    Q_OBJECT

public:
    explicit demoView_widget(QWidget *parent = 0);
    ~demoView_widget();
    
    void showFileInfoList(QFileInfo);
    void createButton();

public slots:
    void OpenDemo();        //打开demo文件
    void Exit();            //关闭窗口函数
    

private:
    Ui::demoView_widget *ui;

    QTreeView *treeView;        //树形视图，用以显示demo
    QFileSystemModel *model;    //qt自带的文件管理model

    QPushButton *openButton;
    QPushButton *exitButton;

signals:
    void SendPath(const QString &filePath);
};

#endif // DEMOVIEW_WIDGET_H
