#include <QHBoxLayout>
#include "pageswitcher.h"


PageSwitcher::PageSwitcher(QWidget* parent = nullptr, const QStringList& pages_names) : QWidget(parent) , pages_buttons(pages_names.size()) {
    QHBoxLayout layout(this);

    for (int i = 0; i < pages_names.size(); i++) {
        QPushButton button(pages_names[i]);
        pages_buttons[i] = &button;
        layout.addWidget(&button);
        connect(&button, &QPushButton::clicked, [this, i](){ emit changePage(i); });
    }
    setLayout(&layout);
}


PageSwitcher::~PageSwitcher() {
    for (auto button : pages_buttons) {
        delete button;
    }
    setParent(nullptr);
}

