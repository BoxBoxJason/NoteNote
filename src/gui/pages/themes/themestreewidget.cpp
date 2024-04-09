#include <QJsonObject>
#include "gui/pages/themes/themestreewidget.h"

ThemesTreeWidget::ThemesTreeWidget(QWidget* parent) : QTreeWidget(parent) {
    // Headers
    setColumnCount(5);
    setHeaderLabels(QStringList{"Theme","Description","Start","End","Level"});

    // Options
    setDragDropMode(QAbstractItemView::NoDragDrop);
    setDragEnabled(false);
    setAcceptDrops(false);
    setDropIndicatorShown(false);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::AllEditTriggers);

    // Context Menu
    context_menu = new ThemesContextMenu(this);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTreeWidget::customContextMenuRequested, this, &ThemesTreeWidget::showContextMenu);
}


void ThemesTreeWidget::showContextMenu(const QPoint& pos) {
    context_menu->prepareMenu(selectedItems().size() > 0 ? selectedItems().at(0) : invisibleRootItem());
    context_menu->exec(mapToGlobal(pos));
}


void ThemesTreeWidget::displayThemes(QTreeWidgetItem& parent_item, const QJsonArray& json_themes) {
    for (const QJsonValue& theme_value : json_themes) {
        QJsonObject theme_object = theme_value.toObject();
        QTreeWidgetItem* new_item = new QTreeWidgetItem(&parent_item);
        new_item->setFlags(new_item->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        new_item->setText(0, theme_object["name"].toString());
        new_item->setText(1, theme_object["description"].toString());
        new_item->setText(2, theme_object["start"].toString());
        new_item->setText(3, theme_object["end"].toString());
        new_item->setText(4, theme_object["level"].toString());
        parent_item.addChild(new_item);
        if (theme_object.contains("children")) {
            displayThemes(*new_item, theme_object["children"].toArray());
        }
    }
}


void ThemesTreeWidget::onItemChanged(QTreeWidgetItem* item, int column) {
    if ( 2 <= column <= 3) {
        // Check if the start date is before the end date
        QDate start_date = QDate::fromString(item->text(2), "yyyy-MM-dd");
        QDate end_date = QDate::fromString(item->text(3), "yyyy-MM-dd");
        if (start_date > end_date) {
            item->setText(3, item->text(2));
        }
    }
}

