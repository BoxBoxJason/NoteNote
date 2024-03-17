#ifndef GUI_PAGES_GRADES_GRADESDISPLAY_H
#define GUI_PAGES_GRADES_GRADESDISPLAY_H

#include <QTableWidget>

class GradesDisplay : public QTableWidget {
    Q_OBJECT

public:
    GradesDisplay(QWidget* parent = nullptr);
    
};

#endif // GUI_PAGES_GRADES_GRADESDISPLAY_H
