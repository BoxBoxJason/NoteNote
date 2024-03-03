#ifndef GUI_UTILS_PAGESWITCHER_H
#define GUI_UTILS_PAGESWITCHER_H

#include <QWidget>
#include <QStackedLayout>
#include <QVector>
#include <QPushButton>

class PageSwitcher : public QWidget
{
    Q_OBJECT

public:
    PageSwitcher(QWidget* parent = nullptr, const QStringList& pages_names=QStringList());
    ~PageSwitcher();

private:
    QVector<QPushButton*> pages_buttons;

signals:
    void changePage(int page_index);

};

#endif // GUI_UTILS_PAGESWITCHER_H
