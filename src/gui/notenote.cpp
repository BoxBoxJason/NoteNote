#include "notenote.h"

NoteNote::NoteNote(QWidget *parent)
    : QMainWindow(parent) {
    navigation_bar = new NavigationBar(this);
    addToolBar(navigation_bar);

    pages_manager = new PagesManagerWidget(this);
    setCentralWidget(pages_manager);

    setWindowTitle("NoteNote");
}


NoteNote::~NoteNote() {
}
