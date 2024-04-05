#ifndef GUI_PAGES_GRADES_GRADESDISPLAY_H
#define GUI_PAGES_GRADES_GRADESDISPLAY_H

#include <QTableWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QJsonObject>
#include <QString>

class GradesDisplayContextMenu : public QMenu {
    Q_OBJECT

public:
    GradesDisplayContextMenu(QWidget* parent = nullptr);

signals:
    void addAbsenceReason(const QString& reason);

};


class GradesDisplay : public QTableWidget {
    Q_OBJECT

public:
    GradesDisplay(QWidget* parent = nullptr);
    QString getCSV();

public slots:
    void displayGrades(const QString& csv_grades, const QVector<QVector<int>> grades_ids);

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    GradesDisplayContextMenu* context_menu;

private slots:
    void setAbsenceReason(const QString& reason);

};

#endif // GUI_PAGES_GRADES_GRADESDISPLAY_H
