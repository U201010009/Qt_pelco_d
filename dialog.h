#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "pelco_d.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    void setBtnEnable(bool status);

private slots:
    void onCheckBoxStateChanged(int state);
    void onUpPressed();
    void onDownPressed();
    void onLeftPressed();
    void onRightPressed();

    void onFocusUpPressed();
    void onFocusDownPressed();
    void onApertureUpPressed();
    void onApertureDownPressed();

    void onCallPresetPointClicked();
    void onSetPresetPointClicked();
    void onDeletePresetPointClicked();

    void onReleased();


    void onSpeedValueChanged(int num);
private:
    Ui::Dialog *ui;

    PELCO_D mPelcoD;
};

#endif // DIALOG_H
