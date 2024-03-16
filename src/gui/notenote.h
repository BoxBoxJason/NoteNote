#ifndef GUI_NOTENOTE_H
#define GUI_NOTENOTE_H

#include <QMainWindow>
#include <QCloseEvent>
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
    int user_id=-1;

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // GUI_NOTENOTE_H
