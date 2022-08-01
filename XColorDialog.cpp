#include "XColorDialog.h"
#include <QDebug>

XColorDialog::XColorDialog(QWidget *parent) :
    QDialog(parent){

    pal = new QPalette();
    pal->setColor(QPalette::AlternateBase, BG_COLOR);
    pal->setColor(QPalette::Window, BG_COLOR);
    pal->setColor(QPalette::Button, BG_COLOR);
    pal->setColor(QPalette::Base, BG_COLOR);
    pal->setColor(QPalette::Text, Qt::white);
    pal->setColor(QPalette::WindowText, Qt::white);
    pal->setColor(QPalette::ToolTipText, Qt::white);
    pal->setColor(QPalette::ButtonText, Qt::white);
    pal->setColor(QPalette::BrightText, Qt::red);
    pal->setColor(QPalette::ToolTipBase, Qt::black);
    pal->setColor(QPalette::HighlightedText, Qt::black);
    pal->setColor(QPalette::Link, QColor(42, 130, 218));
    pal->setColor(QPalette::Highlight, QColor(42, 130, 218));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    setFixedSize(663,276);
    SetupUI();

    setAcceptDrops(true);
}

void XColorDialog::SetupUI(){
    hLayoutAll = new QHBoxLayout(this);

    setupPicker();
    setupPeviews();
    setupSliders();

    /*vLayoutButtons = new QVBoxLayout;
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    vLayoutButtons->addWidget(okButton);
    vLayoutButtons->addWidget(cancelButton);
    vLayoutButtons->addStretch();
    vLayoutButtons->setContentsMargins(0,5,5,0);

    hLayoutPreviewButton = new QHBoxLayout;

    hLayoutPreviewButton->addLayout(vLayoutPreview);
    hLayoutPreviewButton->addStretch();
    hLayoutPreviewButton->addLayout(vLayoutButtons);
    hLayoutPreviewButton->setContentsMargins(25,0,0,0)*/ 

    //paint event overides stylesheets for XGradientSlider
    /*sliderBlue->setStyleSheet("QSlider::groove:horizontal { "
        "border: 1px solid #999999; "
        "height: 20px; "
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4); "
        "margin: 2px 0; "
        "} "
        "QSlider::handle:horizontal { "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f); "
        "border: 1px solid #5c5c5c; "
        "width: 30px; "
        "margin: -2px 0px; "
        "} ");

    sliderBlue->setStyleSheet("QSlider::groove:horizontal {background-color:yellow;}"
        "QSlider::handle:horizontal {background-color:blue; height:16px; width: 16px;}");*/

    hLayoutAll->addWidget(colorSquare);
    hLayoutAll->addWidget(verticalSlider);
    hLayoutAll->addLayout(vLayoutPreview);
    hLayoutAll->addLayout(gLayoutSlider);

    this->setLayout(hLayoutAll);

    setConnect();
    setVerticalSlider();
    setPreviewColors(color());
}
void XColorDialog::setupPicker() {

    colorSquare = new XColorSquare(this);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    colorSquare->setSizePolicy(sizePolicy);
    verticalSlider = new XGradientSlider(this);
    verticalSlider->setOrientation(Qt::Vertical);
}
void XColorDialog::setupPeviews() {

    vLayoutPreview = new QVBoxLayout;
    vLayoutPreview->setSpacing(1);
    checkBoxCurr = new QCheckBox("Current");
    checkBoxComp = new QCheckBox("Complementary");
    checkBoxOpp = new QCheckBox("Opposite");
    checkBoxRev = new QCheckBox("Reverse");
    colorPreviewCurr = new XColorPreview(this);
    colorPreviewComp = new XColorPreview(this);
    colorPreviewOpp = new XColorPreview(this);
    colorPreviewRev = new XColorPreview(this);

    checkBoxCurr->setChecked(true);

    vLayoutPreview->addWidget(checkBoxCurr);
    vLayoutPreview->addWidget(colorPreviewCurr);

    vLayoutPreview->addWidget(checkBoxComp);
    vLayoutPreview->addWidget(colorPreviewComp);

    vLayoutPreview->addWidget(checkBoxOpp);
    vLayoutPreview->addWidget(colorPreviewOpp);

    vLayoutPreview->addWidget(checkBoxRev);
    vLayoutPreview->addWidget(colorPreviewRev);

    vLayoutPreview->setAlignment(checkBoxCurr, Qt::AlignLeft);
    vLayoutPreview->setAlignment(checkBoxComp, Qt::AlignLeft);
    vLayoutPreview->setAlignment(checkBoxOpp, Qt::AlignLeft);
    vLayoutPreview->setAlignment(checkBoxRev, Qt::AlignLeft);
}
void XColorDialog::setupSliders(){

    gLayoutSlider = new QGridLayout;
    labelAlpha = new QLabel("alpha:");
    spinAlpha = new QSpinBox(this);
    spinAlpha->setPalette(*pal);
    spinAlpha->setMaximum(100);
    spinAlpha->setValue(100);
    labelAlphaSuffix = new QLabel("%");
    sliderAlpha = new XGradientSlider(this);
    sliderAlpha->setMaximum(100);
    sliderAlpha->setValue(100);
    sliderAlpha->setOrientation(Qt::Horizontal);
    gLayoutSlider->addWidget(labelAlpha, 0, 0, 1, 1);
    gLayoutSlider->addWidget(spinAlpha, 0, 1, 1, 1);
    gLayoutSlider->addWidget(labelAlphaSuffix, 0, 2, 1, 1);
    gLayoutSlider->addWidget(sliderAlpha, 0, 3, 1, 1);

    radioHue = new QRadioButton("H:");
    radioHue->setChecked(true);
    spinHue = new QSpinBox(this);
    spinHue->setPalette(*pal);
    spinHue->setMaximum(359);
    labelHueSuffix = new QLabel("°");
    sliderHue = new XGradientSlider(this);
    QVector<QColor> rainbow;
    for (int i = 0; i < 360; i += 360 / 6)
        rainbow.push_back(QColor::fromHsv(i, 255, 255));
    rainbow.push_back(Qt::red);
    sliderHue->setColors(rainbow);
    sliderHue->setMaximum(359);
    sliderHue->setOrientation(Qt::Horizontal);
    gLayoutSlider->addWidget(radioHue, 1, 0, 1, 1);
    gLayoutSlider->addWidget(spinHue, 1, 1, 1, 1);
    gLayoutSlider->addWidget(labelHueSuffix, 1, 2, 1, 1);
    gLayoutSlider->addWidget(sliderHue, 1, 3, 1, 1);

    radioSat = new QRadioButton("S:");
    radioSat->setChecked(false);
    spinSat = new QSpinBox(this);
    spinSat->setPalette(*pal);
    spinSat->setMaximum(100);
    labelSatSuffix = new QLabel("%");
    sliderSat = new XGradientSlider(this);
    sliderSat->setMaximum(100);
    sliderSat->setOrientation(Qt::Horizontal);
    gLayoutSlider->addWidget(radioSat, 2, 0, 1, 1);
    gLayoutSlider->addWidget(spinSat, 2, 1, 1, 1);
    gLayoutSlider->addWidget(labelSatSuffix, 2, 2, 1, 1);
    gLayoutSlider->addWidget(sliderSat, 2, 3, 1, 1);

    radioVal = new QRadioButton("V:");
    radioVal->setChecked(false);
    spinVal = new QSpinBox(this);
    spinVal->setPalette(*pal);
    spinVal->setMaximum(100);
    labelValSuffix = new QLabel("%");
    sliderVal = new XGradientSlider(this);
    sliderVal->setMaximum(100);
    sliderVal->setOrientation(Qt::Horizontal);
    gLayoutSlider->addWidget(radioVal, 3, 0, 1, 1);
    gLayoutSlider->addWidget(spinVal, 3, 1, 1, 1);
    gLayoutSlider->addWidget(labelValSuffix, 3, 2, 1, 1);
    gLayoutSlider->addWidget(sliderVal, 3, 3, 1, 1);

    radioRed = new QRadioButton("R:");
    radioRed->setChecked(false);
    spinRed = new QSpinBox(this);
    spinRed->setPalette(*pal);
    spinRed->setMaximum(255);
    sliderRed = new XGradientSlider(this);
    sliderRed->setMaximum(255);
    sliderRed->setOrientation(Qt::Horizontal);
    gLayoutSlider->addWidget(radioRed, 4, 0, 1, 1);
    gLayoutSlider->addWidget(spinRed, 4, 1, 1, 1);
    gLayoutSlider->addWidget(sliderRed, 4, 3, 1, 1);

    radioGreen = new QRadioButton("G:");
    radioGreen->setChecked(false);
    spinGreen = new QSpinBox(this);
    spinGreen->setPalette(*pal);
    spinGreen->setMaximum(255);
    sliderGreen = new XGradientSlider(this);
    sliderGreen->setMaximum(255);
    sliderGreen->setOrientation(Qt::Horizontal);
    gLayoutSlider->addWidget(radioGreen, 5, 0, 1, 1);
    gLayoutSlider->addWidget(spinGreen, 5, 1, 1, 1);
    gLayoutSlider->addWidget(sliderGreen, 5, 3, 1, 1);

    radioBlue = new QRadioButton("B:");
    radioBlue->setChecked(false);
    spinBlue = new QSpinBox(this);
    spinBlue->setPalette(*pal);
    spinBlue->setMaximum(255);
    sliderBlue = new XGradientSlider(this);
    sliderBlue->setMaximum(255);
    sliderBlue->setOrientation(Qt::Horizontal);
    gLayoutSlider->addWidget(radioBlue, 6, 0, 1, 1);
    gLayoutSlider->addWidget(spinBlue, 6, 1, 1, 1);
    gLayoutSlider->addWidget(sliderBlue, 6, 3, 1, 1);
    gLayoutSlider->setContentsMargins(5, 0, 0, 0);
}

void XColorDialog::setPreviewColors(QColor col){

    QColor colComp = QColor(255 - col.red(), 255 - col.green(), 255 - col.blue(), col.alpha());
    QColor colOpp = QColor(255 - col.green(), 255 - col.red(), 255 - col.blue(), col.alpha());
    QColor colRev = QColor(255 - col.blue(), 255 - col.green(), 255 - col.red(), col.alpha());

    colorPreviewCurr->setColor(col);
    colorPreviewOpp->setColor(colOpp);
    colorPreviewComp->setColor(colComp);
    colorPreviewRev->setColor(colRev);
}
void XColorDialog::setConnect(){

    QObject::connect(radioHue, SIGNAL(clicked(bool)),this, SLOT(setVerticalSlider()));
    QObject::connect(radioSat, SIGNAL(clicked(bool)),this, SLOT(setVerticalSlider()));
    QObject::connect(radioVal, SIGNAL(clicked(bool)),this, SLOT(setVerticalSlider()));
    QObject::connect(radioRed, SIGNAL(clicked(bool)),this, SLOT(setVerticalSlider()));
    QObject::connect(radioGreen, SIGNAL(clicked(bool)),this, SLOT(setVerticalSlider()));
    QObject::connect(radioBlue, SIGNAL(clicked(bool)),this, SLOT(setVerticalSlider()));
    QObject::connect(sliderAlpha, SIGNAL(valueChanged(int)), spinAlpha, SLOT(setValue(int)));
    QObject::connect(spinAlpha, SIGNAL(valueChanged(int)), sliderAlpha, SLOT(setValue(int)));
    QObject::connect(sliderHue, SIGNAL(valueChanged(int)), spinHue, SLOT(setValue(int)));
    QObject::connect(spinHue, SIGNAL(valueChanged(int)), sliderHue, SLOT(setValue(int)));
    QObject::connect(sliderSat, SIGNAL(valueChanged(int)), spinSat, SLOT(setValue(int)));
    QObject::connect(spinSat, SIGNAL(valueChanged(int)), sliderSat, SLOT(setValue(int)));
    QObject::connect(sliderVal, SIGNAL(valueChanged(int)), spinVal, SLOT(setValue(int)));
    QObject::connect(spinVal, SIGNAL(valueChanged(int)), sliderVal, SLOT(setValue(int)));
    QObject::connect(sliderRed, SIGNAL(valueChanged(int)), spinRed, SLOT(setValue(int)));
    QObject::connect(spinRed, SIGNAL(valueChanged(int)), sliderRed, SLOT(setValue(int)));
    QObject::connect(sliderGreen, SIGNAL(valueChanged(int)), spinGreen, SLOT(setValue(int)));
    QObject::connect(spinGreen, SIGNAL(valueChanged(int)), sliderGreen, SLOT(setValue(int)));
    QObject::connect(sliderBlue, SIGNAL(valueChanged(int)), spinBlue, SLOT(setValue(int)));
    QObject::connect(spinBlue, SIGNAL(valueChanged(int)), sliderBlue, SLOT(setValue(int)));
    QObject::connect(sliderHue, SIGNAL(valueChanged(int)), this, SLOT(setHSV()));
    QObject::connect(sliderSat, SIGNAL(valueChanged(int)), this, SLOT(setHSV()));
    QObject::connect(sliderVal, SIGNAL(valueChanged(int)), this, SLOT(setHSV()));
    QObject::connect(sliderRed, SIGNAL(valueChanged(int)), this, SLOT(setRGB()));
    QObject::connect(sliderGreen, SIGNAL(valueChanged(int)), this, SLOT(setRGB()));
    QObject::connect(sliderBlue, SIGNAL(valueChanged(int)), this, SLOT(setRGB()));
    QObject::connect(sliderAlpha, SIGNAL(valueChanged(int)), this, SLOT(updateWidgets()));
    QObject::connect(colorSquare, SIGNAL(colorSelected(QColor)), this, SLOT(updateWidgets()));
    QObject::connect(this, SIGNAL(checkedChanged(char)), colorSquare, SLOT(setCheckedColor(char)));
    //QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    //QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(ClickedOkButton()));

}

QColor XColorDialog::color() const{

    QColor color = colorSquare->color();
    color.setAlpha(qRound(sliderAlpha->value() * 2.55));
    return color;
}

void XColorDialog::setColor(QColor color){

    colorSquare->setColor(color);
    sliderAlpha->setValue(color.alpha() / 2.55);
    updateWidgets();
}

void XColorDialog::setVerticalSlider(){

    disconnect(verticalSlider, SIGNAL(valueChanged(int)), sliderHue, SLOT(setValue(int)));
    disconnect(verticalSlider, SIGNAL(valueChanged(int)), sliderSat, SLOT(setValue(int)));
    disconnect(verticalSlider, SIGNAL(valueChanged(int)), sliderVal, SLOT(setValue(int)));
    disconnect(verticalSlider, SIGNAL(valueChanged(int)), sliderRed, SLOT(setValue(int)));
    disconnect(verticalSlider, SIGNAL(valueChanged(int)), sliderGreen, SLOT(setValue(int)));
    disconnect(verticalSlider, SIGNAL(valueChanged(int)), sliderBlue, SLOT(setValue(int)));

    if(radioHue->isChecked())
    {
        QVector<QColor> rainbow;
        for ( int i = 0; i < 360; i+= 360/6 )
            rainbow.push_front(QColor::fromHsv(i,255,255));
        rainbow.push_front(Qt::red);
        verticalSlider->setMaximum(sliderHue->maximum());
        verticalSlider->setColors(rainbow);
        verticalSlider->setValue(sliderHue->value());
        connect(verticalSlider, SIGNAL(valueChanged(int)), sliderHue, SLOT(setValue(int)));
        emit checkedChanged('H');
    }
    if(radioSat->isChecked())
    {
        verticalSlider->setMaximum(sliderSat->maximum());
        verticalSlider->setValue(sliderSat->value());
        verticalSlider->setFirstColor(sliderSat->lastColor());
        verticalSlider->setLastColor(sliderSat->firstColor());
        connect(verticalSlider, SIGNAL(valueChanged(int)), sliderSat, SLOT(setValue(int)));
        emit checkedChanged('S');
    }
    if(radioVal->isChecked())
    {
        verticalSlider->setMaximum(sliderVal->maximum());
        verticalSlider->setValue(sliderVal->value());
        verticalSlider->setFirstColor(sliderVal->lastColor());
        verticalSlider->setLastColor(sliderVal->firstColor());
        connect(verticalSlider, SIGNAL(valueChanged(int)), sliderVal, SLOT(setValue(int)));
        emit checkedChanged('V');
    }
    if(radioRed->isChecked())
    {
        verticalSlider->setMaximum(sliderRed->maximum());
        verticalSlider->setValue(sliderRed->value());
        verticalSlider->setFirstColor(sliderRed->lastColor());
        verticalSlider->setLastColor(sliderRed->firstColor());
        connect(verticalSlider, SIGNAL(valueChanged(int)), sliderRed, SLOT(setValue(int)));
        emit checkedChanged('R');
    }
    if(radioGreen->isChecked())
    {
        verticalSlider->setMaximum(sliderGreen->maximum());
        verticalSlider->setValue(sliderGreen->value());
        verticalSlider->setFirstColor(sliderGreen->lastColor());
        verticalSlider->setLastColor(sliderGreen->firstColor());
        connect(verticalSlider, SIGNAL(valueChanged(int)), sliderGreen, SLOT(setValue(int)));
        emit checkedChanged('G');
    }
    if(radioBlue->isChecked())
    {
        verticalSlider->setMaximum(sliderBlue->maximum());
        verticalSlider->setValue(sliderBlue->value());
        verticalSlider->setFirstColor(sliderBlue->lastColor());
        verticalSlider->setLastColor(sliderBlue->firstColor());
        connect(verticalSlider, SIGNAL(valueChanged(int)), sliderBlue, SLOT(setValue(int)));
        emit checkedChanged('B');
    }

}

void XColorDialog::setHSV(){

    if(!signalsBlocked())
    {
        colorSquare->setColor(QColor::fromHsv(sliderHue->value(),
                                              qRound(sliderSat->value()*2.55),
                                              qRound(sliderVal->value()*2.55)));
        updateWidgets();
    }
}

void XColorDialog::setRGB(){

    if(!signalsBlocked())
    {
        QColor color(sliderRed->value(), sliderGreen->value(), sliderBlue->value());
        if(color.saturation() == 0)
        {
            color = QColor::fromHsv(sliderHue->value(), 0, color.value());
        }
        colorSquare->setColor(color);
        updateWidgets();
    }
}

void XColorDialog::updateWidgets(){

    blockSignals(true);
    foreach(QWidget* w, findChildren<QWidget*>())
        w->blockSignals(true);

    QColor col = color();
    

    sliderRed->setValue(col.red());
    spinRed->setValue(sliderRed->value());
    sliderRed->setFirstColor(QColor(0,col.green(),col.blue()));
    sliderRed->setLastColor(QColor(255,col.green(),col.blue()));

    sliderGreen->setValue(col.green());
    spinGreen->setValue(sliderGreen->value());
    sliderGreen->setFirstColor(QColor(col.red(),0,col.blue()));
    sliderGreen->setLastColor(QColor(col.red(),255,col.blue()));

    sliderBlue->setValue(col.blue());
    spinBlue->setValue(sliderBlue->value());
    sliderBlue->setFirstColor(QColor(col.red(),col.green(),0));
    sliderBlue->setLastColor(QColor(col.red(),col.green(),255));

    sliderHue->setValue(qRound(colorSquare->hue()*360.0));
    spinHue->setValue(sliderHue->value());

    sliderSat->setValue(qRound(colorSquare->saturation()*100.0));
    spinSat->setValue(sliderSat->value());
    sliderSat->setFirstColor(QColor::fromHsvF(colorSquare->hue(),0,colorSquare->value()));
    sliderSat->setLastColor(QColor::fromHsvF(colorSquare->hue(),1,colorSquare->value()));

    sliderVal->setValue(qRound(colorSquare->value()*100.0));
    spinVal->setValue(sliderVal->value());
    sliderVal->setFirstColor(QColor::fromHsvF(colorSquare->hue(),colorSquare->saturation(),0));
    sliderVal->setLastColor(QColor::fromHsvF(colorSquare->hue(),colorSquare->saturation(),1));

    setVerticalSlider();
    setPreviewColors(col);

    blockSignals(false);
    foreach(QWidget* w, findChildren<QWidget*>())
        w->blockSignals(false);

    emit colorChanged(col);
}

void XColorDialog::clickedOkButton(){

    QColor color = this->color();
    emit colorSelected(color);
    this->close();
}
