#include "dialog.h"
#include "XColorDialog.h"
#include "XColorSquare.h"
#include <QApplication>

void launchDialog() {
    Dialog *w = new Dialog;
    w->show();
}

void launchStandalone() {
    XColorDialog* dialog = new XColorDialog;
    dialog->show();
}

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    //launchDialog();
    launchStandalone();
    
    return a.exec();
}
