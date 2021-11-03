#pragma once

#include <QWidget>

class QSpinBox;
class QLabel;

class PageSpinBox : public QWidget
{
    Q_OBJECT
public:
    explicit PageSpinBox(QWidget *parent = nullptr);

signals:
    void pageChanged(int page);

public slots:
    void onMaxPageChanged(int max_page);
    void onPageHasChanged(int page);

private:
    QSpinBox*    spin;
    QLabel*      maxPageLabel;

    void setupUi();
};
