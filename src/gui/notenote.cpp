#include "notenote.h"

NoteNote::NoteNote(QWidget *parent)
    : QMainWindow(parent)
{
    NavigationBar navigation_bar_instance(this);
    navigation_bar = &navigation_bar_instance;
    addToolBar(navigation_bar);

    PagesManagerWidget pages_manager_instance(this);
    pages_manager = &pages_manager_instance;
    setCentralWidget(pages_manager);

    setWindowTitle("NoteNote");
}


NoteNote::~NoteNote()
{
    setParent(nullptr);
    delete navigation_bar;
    delete pages_manager;
}

