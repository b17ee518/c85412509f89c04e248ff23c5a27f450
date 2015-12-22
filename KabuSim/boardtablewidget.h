#ifndef BOARDTABLEWIDGET_H
#define BOARDTABLEWIDGET_H

#include <QTableWidget>

class BoardTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit BoardTableWidget(QWidget *parent = 0);
    ~BoardTableWidget();

signals:

public slots:
};

#endif // BOARDTABLEWIDGET_H
