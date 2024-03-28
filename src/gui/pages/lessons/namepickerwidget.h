#ifndef GUI_PAGES_LESSONS_NAMEPICKERWIDGET_H
#define GUI_PAGES_LESSONS_NAMEPICKERWIDGET_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QPushButton>

class NamePickerWidget : public QWidget {
    /**
     * @class NamePickerWidget
     * @brief An UI based widget to pick a name for a new file or directory.
     * @details The widget provides a way to pick a name for a new file or directory.
    */
    Q_OBJECT

public:
    NamePickerWidget(QWidget* parent = nullptr);

public slots:
    void setIncorrectInput(const QString& error_message = "");
    void setCorrectInput();
    void setSuffix(bool is_dir, const QString& suffix);

private slots:
    /**
     * @brief Slot to submit the creation.
    */
    void submitCreation();

private:
    bool is_directory;
    // Input field to enter the file name.
    QLineEdit* file_name_input;
    // Validation button to create the file.
    QPushButton* create_button;

signals:
    /**
     * @brief Signal to send the picked name.
     * @param is_directory Flag to check if the selected extension is a directory.
     * @param file_name The picked file name.
    */
    void namePicked(bool is_directory,const QString& file_name);
    void nameChanged(const QString& file_name);
};

#endif // GUI_PAGES_LESSONS_NAMEPICKERWIDGET_H
