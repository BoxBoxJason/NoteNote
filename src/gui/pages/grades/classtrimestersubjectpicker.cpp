#include <QGridLayout>
#include "classtrimestersubjectpicker.h"
#include "../../../controllers/classescontroller.h"
#include "../../../utils/formatutils.h"

const QHash<QString,QStringList> DIVISIONS = {
    {"trimester", {"T1", "T2", "T3"}},
    {"semester", {"S1", "S2"}}
};


ClassTrimesterSubjectPicker::ClassTrimesterSubjectPicker(QWidget* parent) : QWidget(parent) {
    QGridLayout* layout = new QGridLayout(this);

    // Class picker section
    QLabel *class_label = new QLabel(tr("Class"), this);
    class_label->setAlignment(Qt::AlignCenter);
    class_label->setObjectName("picker_label");
    layout->addWidget(class_label, 0, 0, 1, 1, Qt::AlignHCenter | Qt::AlignBottom);

    class_picker = new QComboBox(this);
    class_picker->setObjectName("picker_combobox");
    connect(class_picker, &QComboBox::currentTextChanged, this, &ClassTrimesterSubjectPicker::classSelected);
    layout->addWidget(class_picker, 1, 0, 1, 1, Qt::AlignHCenter | Qt::AlignTop);

    // Subject picker section
    QLabel *subject_label = new QLabel(tr("Subject"), this);
    subject_label->setAlignment(Qt::AlignCenter);
    subject_label->setObjectName("picker_label");
    layout->addWidget(subject_label, 0, 1, 1, 1, Qt::AlignHCenter | Qt::AlignBottom);

    subject_picker = new QComboBox(this);
    subject_picker->setObjectName("picker_combobox");
    connect(subject_picker, &QComboBox::currentTextChanged, this, &ClassTrimesterSubjectPicker::subjectOrDivisionSelected);
    layout->addWidget(subject_picker, 1, 1, 1, 1, Qt::AlignHCenter | Qt::AlignTop);

    // Trimester picker section
    division_label = new QLabel(tr("Trimester"), this);
    division_label->setObjectName("picker_label");
    layout->addWidget(division_label, 0, 2, 1, 1, Qt::AlignHCenter | Qt::AlignBottom); 

    division_picker = new QComboBox(this);
    division_picker->setObjectName("picker_combobox");
    connect(division_picker, &QComboBox::currentTextChanged, this, &ClassTrimesterSubjectPicker::subjectOrDivisionSelected);
    layout->addWidget(division_picker, 1, 2, 1, 1, Qt::AlignHCenter | Qt::AlignTop);

    setLayout(layout);
}


void ClassTrimesterSubjectPicker::updateClassList() {
    class_picker->clear();
    class_picker->addItems(ClassesController::getClasses());
}


void ClassTrimesterSubjectPicker::classSelected(const QString& class_name) {
    subject_picker->clear();
    division_picker->clear();

    if (! class_name.isEmpty()){
        QHash<QString,QVariant> class_data = ClassesController::getClassSubjectsAndDivision(class_name);
        subject_picker->addItems(FormatUtils::formatStringList(class_data["subjects"].toString()));

        QString division = class_data["division"].toString();
        division_label->setText(FormatUtils::capitalize(division));
        division_picker->addItems(DIVISIONS[division]);
    }
}


void ClassTrimesterSubjectPicker::subjectOrDivisionSelected() {
    if (! (subject_picker->currentData().isNull() || division_picker->currentData().isNull() || class_picker->currentData().isNull())){
        emit classPicked(class_picker->currentText(), subject_picker->currentText(), division_picker->currentIndex());
    }
}
