#include <QHBoxLayout>
#include "pageswitcher.h"


PageSwitcher::PageSwitcher(QWidget* parent, const QStringList& pages_names) : QWidget(parent) , pages_buttons(pages_names.size()) {
    QHBoxLayout* layout = new QHBoxLayout(this);

    for (int i = 0; i < pages_names.size(); i++) {
        QPushButton* button = new QPushButton(pages_names[i]);
        pages_buttons[i] = button;
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, [this, i](){ emit changePage(i); });
    }
    setLayout(layout);
}


PageSwitcher::~PageSwitcher() {
}
