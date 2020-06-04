#include "setlinkdialog.h"
#include "ui_setlinkdialog.h"

SetLinkDialog::SetLinkDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SetLinkDialog)
{
    ui->setupUi(this);
}

SetLinkDialog::~SetLinkDialog()
{
    delete ui;
}

QString SetLinkDialog::getName()
{
    return ui->cbbName->currentText();
}

QString SetLinkDialog::getValue()
{
    return ui->edtValue->text();
}

void SetLinkDialog::on_btnOk_clicked()
{
    accept();
}

void SetLinkDialog::on_btnCancel_clicked()
{
    reject();
}
