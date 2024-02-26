#include <QApplication>
#include "./gui/notenote.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    NoteNote notenote;
    notenote.setWindowTitle("NoteNote");
    notenote.resize(800, 600);
    notenote.show();

    return app.exec();
}
