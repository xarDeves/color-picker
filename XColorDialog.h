#ifndef XCOLORDIALOG_H
#define XCOLORDIALOG_H

#include <QDialog>
#include "XColorPreview.hpp"
#include "XColorSquare.h"
#include "XGradientSlider.hpp"
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QGraphicsBlurEffect>

#define BG_COLOR "#353535"

class XColorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit XColorDialog(QWidget *parent = 0);

    QColor  color() const;

private:
    enum CheckedColor
    {
        H,S,V,R,G,B
    }checkedColor;

    QPalette*           pal;

    QHBoxLayout*        hLayoutAll;
    XColorSquare*       colorSquare;
    XGradientSlider*    verticalSlider;

    QVBoxLayout*        vLayoutPreview;
    QCheckBox*             checkBoxCurr;
    QCheckBox*             checkBoxOpp;
    QCheckBox*             checkBoxComp;
    QCheckBox*             checkBoxRev;
    XColorPreview*      colorPreviewCurr;
    XColorPreview*      colorPreviewOpp;
    XColorPreview*      colorPreviewComp;
    XColorPreview*      colorPreviewRev;

    QVBoxLayout*        vLayoutButtons;
    QPushButton*        okButton;
    QPushButton*        cancelButton;

    QHBoxLayout*        hLayoutPreviewButton;

    QGridLayout*        gLayoutSlider;
    QLabel*             labelAlpha;
    QSpinBox*           spinAlpha;
    QLabel*             labelAlphaSuffix;
    XGradientSlider*    sliderAlpha;

    QRadioButton*       radioHue;
    QSpinBox*           spinHue;
    QLabel*             labelHueSuffix;
    XGradientSlider*    sliderHue;

    QRadioButton*       radioSat;
    QSpinBox*           spinSat;
    QLabel*             labelSatSuffix;
    XGradientSlider*    sliderSat;

    QRadioButton*       radioVal;
    QSpinBox*           spinVal;
    QLabel*             labelValSuffix;
    XGradientSlider*    sliderVal;

    QRadioButton*       radioRed;
    QSpinBox*           spinRed;
    XGradientSlider*    sliderRed;
    QRadioButton*       radioGreen;
    QSpinBox*           spinGreen;
    XGradientSlider*    sliderGreen;
    QRadioButton*       radioBlue;
    QSpinBox*           spinBlue;
    XGradientSlider*    sliderBlue;

private:
    void    SetupUI();
    void    setConnect();
    void    setPreviewColors(QColor col);
    void    setupPicker();
    void    setupPeviews();
    void    setupSliders();

signals:
    void    colorChanged(QColor);
    void    checkedChanged(char);
    void    colorSelected(QColor);

public slots:
    void    updateWidgets();
    void    setHSV();
    void    setRGB();

    void    setColor(QColor color);
    void    setVerticalSlider();

    void    clickedOkButton();
};

#endif // XCOLORDIALOG_H
