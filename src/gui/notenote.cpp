#include <QMessageBox>
#include <QIcon>
#include "notenote.h"
#include "../utils/sessionmanager.hpp"

NoteNote::NoteNote(QWidget *parent) : QMainWindow(parent) {
    setWindowIcon(QIcon(":images/logo.png"));
    navigation_bar = new NavigationBar(this);
    addToolBar(navigation_bar);
    pages_manager = new PagesManagerWidget(this);
    
    connect(navigation_bar, &NavigationBar::changePage, pages_manager, &PagesManagerWidget::changePage);

    setCentralWidget(pages_manager);
    setWindowTitle("NoteNote");
}


NoteNote::~NoteNote() {
}


void NoteNote::closeEvent(QCloseEvent* event) {
    if (QMessageBox::question(this, tr("Exit"), tr("Do you want to exit?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        DatabaseManager::instance().getDatabase().close();
        qDebug() << "Exiting NoteNote...";
        event->accept();
    } else {
        event->ignore();
    }
}
