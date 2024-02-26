#ifndef GUI_NOTENOTE_H
#define GUI_NOTENOTE_H

#include <QMainWindow>
#include "./navigation/navigationbar.h"
#include "./navigation/pagesmanagerwidget.h"

class NoteNote : public QMainWindow
{
    Q_OBJECT

public:
    NoteNote(QWidget *parent = nullptr);
    ~NoteNote();

private:
    NavigationBar* navigation_bar;
    PagesManagerWidget* pages_manager;
};

#endif // GUI_NOTENOTE_H
