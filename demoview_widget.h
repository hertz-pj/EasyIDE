#ifndef DEMOVIEW_WIDGET_H
#define DEMOVIEW_WIDGET_H

#include <QWidget>

#include <QFileInfoList>
#include <QListWidget>
#include <QListWidgetItem>

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

public slots:
    
    

private:
    Ui::demoView_widget *ui;
};

#endif // DEMOVIEW_WIDGET_H
