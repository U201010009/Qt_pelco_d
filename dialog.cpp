#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setBtnEnable(false);

    this->setFixedSize(this->size());

    if(ui->addr_spin_box_)
    {
        ui->addr_spin_box_->setRange(1, 255);
    }

    if(ui->presetpoint_spin_box_)
    {
        ui->presetpoint_spin_box_->setRange(1, 64);
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setBtnEnable(bool status)
{
    if(ui->call_presetpoint_btn_)
        ui->call_presetpoint_btn_->setEnabled(status);
    if(ui->set_presetpoint_btn_)
        ui->set_presetpoint_btn_->setEnabled(status);
    if(ui->delete_presetpoint_btn_)
        ui->delete_presetpoint_btn_->setEnabled(status);
    if(ui->up_btn_)
        ui->up_btn_->setEnabled(status);
    if(ui->down_btn_)
        ui->down_btn_->setEnabled(status);
    if(ui->left_btn_)
        ui->left_btn_->setEnabled(status);
    if(ui->right_btn_)
        ui->right_btn_->setEnabled(status);
    if(ui->aperture_down_btn_)
        ui->aperture_down_btn_->setEnabled(status);
    if(ui->aperture_up_btn_)
        ui->aperture_up_btn_->setEnabled(status);
    if(ui->focus_down_btn_)
        ui->focus_down_btn_->setEnabled(status);
    if(ui->focus_up_btn_)
        ui->focus_up_btn_->setEnabled(status);
}

void Dialog::onCheckBoxStateChanged(int state)
{
    if(state)
    {
        setBtnEnable(true);

        int i = ui->servial_combo_->currentIndex();

        QString data = ui->bit_combo_->currentText();
        DWORD dwBaudRate = data.toInt();
        BYTE addr = ui->addr_spin_box_->value();

        if(mPelcoD.Init(i + 1, addr, dwBaudRate))
        {}
        else
        {
            QMessageBox msgBox(QMessageBox::Warning, "failed", "Serial Inif failed!", QMessageBox::Ok);
            msgBox.exec();
        }

    }
    else
    {
        mPelcoD.UnInit();
        setBtnEnable(false);
    }
}

void Dialog::onUpPressed()
{
    if(mPelcoD.Available())
    {
        mPelcoD.Up();
    }
}

void Dialog::onDownPressed()
{
    if(mPelcoD.Available())
    {
        mPelcoD.Down();
    }
}

void Dialog::onLeftPressed()
{
    if(mPelcoD.Available())
    {
        mPelcoD.Left();
    }
}

void Dialog::onRightPressed()
{
    if(mPelcoD.Available())
    {
        mPelcoD.Right();
    }
}

void Dialog::onFocusUpPressed()
{
    if(mPelcoD.Available())
    {
        mPelcoD.FocusFar();
    }
}

void Dialog::onFocusDownPressed()
{
    if(mPelcoD.Available())
    {
        mPelcoD.FocusNear();
    }
}

void Dialog::onApertureUpPressed()
{
    if(mPelcoD.Available())
    {
        mPelcoD.ApertureLarge();
    }
}

void Dialog::onApertureDownPressed()
{
    if(mPelcoD.Available())
    {
        mPelcoD.ApertureSmall();
    }
}

void Dialog::onCallPresetPointClicked()
{
    if(mPelcoD.Available())
    {
        if(ui->presetpoint_spin_box_)
        {
            BYTE num = ui->presetpoint_spin_box_->value();
            mPelcoD.CallPresetPoint(num);
        }
    }
}

void Dialog::onSetPresetPointClicked()
{
    if(mPelcoD.Available())
    {
        if(ui->presetpoint_spin_box_)
        {
            BYTE num = ui->presetpoint_spin_box_->value();
            mPelcoD.SetPresetPoint(num);
        }
    }
}

void Dialog::onDeletePresetPointClicked()
{
    if(mPelcoD.Available())
    {
        if(ui->presetpoint_spin_box_)
        {
            BYTE num = ui->presetpoint_spin_box_->value();
            mPelcoD.DeletePresetPoint(num);
        }
    }
}

void Dialog::onReleased()
{
    if(mPelcoD.Available())
    {
        mPelcoD.Stop();
    }
}
