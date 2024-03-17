#include <QHeaderView>
#include <QAction>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include "gradesdisplay.h"
#include "../../../utils/formatutils.h"

static const int EDITED_ROLE = Qt::UserRole + 1;
static const int GRADE_ID_ROLE = Qt::UserRole + 2;

GradesDisplay::GradesDisplay(QWidget* parent) : QTableWidget(parent) {
    setAlternatingRowColors(true);
    verticalHeader()->setVisible(false);
    GradesDisplayContextMenu* context_menu = new GradesDisplayContextMenu(this);
    connect(context_menu, &GradesDisplayContextMenu::addAbsenceReason, this, &GradesDisplay::setAbsenceReason);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(this, &GradesDisplay::itemChanged, this, [this](QTableWidgetItem* item) { item->setData(EDITED_ROLE,true); });
}


void GradesDisplay::contextMenuEvent(QContextMenuEvent* event) {
    context_menu->exec(event->globalPos());
}


void GradesDisplay::setAbsenceReason(const QString& reason) {
    for (QTableWidgetItem* item : selectedItems()) {
        if (item->text() != reason) {
            item->setText(reason);
        }
    }
}


QString GradesDisplay::getCSV() {
    QString csv;
    // Add headers
    for (int col = 0; col < columnCount(); ++col) {
        csv += horizontalHeaderItem(col)->text().trimmed() + ";";
    }
    csv = csv.left(csv.length() - 1) + "\n";
    // Add grades
    for (int row = 0; row < rowCount(); ++row) {
        QString row_content = verticalHeaderItem(row)->text().trimmed() + ";";
        for (int col = 0; col < columnCount(); ++col) {
            row_content += FormatUtils::formatGrade(item(row, col)->text().trimmed()) + ";";
        }
        csv += row_content.left(row_content.length() - 1) + "\n";
    }
    return csv.trimmed();
}


void GradesDisplay::displayGrades(const QString& csv_grades, const QVector<QVector<int>> grades_ids) {
    QStringList lines = csv_grades.split("\n");
    QStringList headers = lines.takeFirst().split(";");
    setColumnCount(headers.size());
    setRowCount(lines.size());
    setHorizontalHeaderLabels(headers);
    for (int row = 0; row < lines.size(); ++row) {
        QStringList row_content = lines.at(row).split(";");
        setVerticalHeaderItem(row, new QTableWidgetItem(row_content.takeFirst()));
        for (int col = 0; col < row_content.size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(row_content.at(col));
            item->setData(EDITED_ROLE, false);
            item->setData(GRADE_ID_ROLE, grades_ids[row][col]);
            setItem(row, col, item);
        }
    }
}


GradesDisplayContextMenu::GradesDisplayContextMenu(QWidget* parent) : QMenu(parent) {
    QFile variables_json_file(":enums/nontakengrades.json");
    if (variables_json_file.open(QFile::ReadOnly)) {
        QJsonObject non_taken_grades_dict = QJsonDocument::fromJson(variables_json_file.readAll()).object();
        variables_json_file.close();
        for (QJsonValue non_taken_value : non_taken_grades_dict) {
            QString non_taken_slug = non_taken_value.toString();
            QAction* action = new QAction(non_taken_grades_dict.value(non_taken_slug).toString(), this);
            connect(action, &QAction::triggered, this, [this, non_taken_slug]() { emit addAbsenceReason(non_taken_slug); });
        }
    } else {
        qCritical() << "Could not load non-taken grades settings, context menu will be disabled, please check nontakengrades.json";
    }
}
