#include "dialog.h"
#include "XColorDialog.h"
#include "XColorSquare.h"
#include <QApplication>
#include <QStyleFactory>
#include <iostream>

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
    //a.setStyle(QStyleFactory::create("Fusion"));


    //launchDialog();
    launchStandalone();
    
    return a.exec();
}
