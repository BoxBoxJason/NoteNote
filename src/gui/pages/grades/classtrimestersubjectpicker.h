#ifndef GUI_PAGES_GRADES_CLASSTRIMESTERSUBJECTPICKER_H
#define GUI_PAGES_GRADES_CLASSTRIMESTERSUBJECTPICKER_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>

class ClassTrimesterSubjectPicker : public QWidget
{
    Q_OBJECT

public:
    ClassTrimesterSubjectPicker(QWidget* parent = nullptr);
    ~ClassTrimesterSubjectPicker();

private slots:
    void classSelected(const QString& class_id);
    void subjectOrDivisionSelected();

private:
    QComboBox* class_picker;
    QComboBox* subject_picker;
    QComboBox* division_picker;
    QLabel* division_label;

signals:
    void classPicked(const QString& class_id, const QString& subject_id, int trimester);

};

#endif // GUI_PAGES_GRADES_CLASSTRIMESTERSUBJECTPICKER_H
