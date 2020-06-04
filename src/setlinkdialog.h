#ifndef SETLINKDIALOG_H
#define SETLINKDIALOG_H

#include <QDialog>

namespace Ui {
class SetLinkDialog;
}

class SetLinkDialog : public QDialog {
    Q_OBJECT

public:
    explicit SetLinkDialog(QWidget* parent = nullptr);
    ~SetLinkDialog();
    QString getName();
    QString getValue();

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::SetLinkDialog* ui;
};

#endif // SETLINKDIALOG_H
