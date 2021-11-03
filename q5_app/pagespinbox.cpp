#include "pagespinbox.h"

#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>

PageSpinBox::PageSpinBox(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void PageSpinBox::setupUi()
{
    auto horizontalLayout = new QHBoxLayout(this);
    auto label = new QLabel(this);
    label->setText(tr("Page:"));
    horizontalLayout->addWidget(label);

    spin = new QSpinBox(this);
    spin->setRange(0, 0);
    horizontalLayout->addWidget(spin);

    maxPageLabel = new QLabel(this);
    maxPageLabel->setText("/0");
    horizontalLayout->addWidget(maxPageLabel);

    connect(spin, SIGNAL(valueChanged(int)), this, SIGNAL(pageChanged(int)));
}

void PageSpinBox::onMaxPageChanged(int max_page) {
    maxPageLabel->setText(QString("/%1").arg(max_page));
    spin->setRange(1, max_page);
}

void PageSpinBox::onPageHasChanged(int page) {
    spin->blockSignals(true);
    spin->setValue(page);
    spin->blockSignals(false);
}
