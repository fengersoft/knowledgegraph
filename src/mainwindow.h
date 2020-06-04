#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "api/controls/knowledgegraphwidget.h"
#include "api/controls/setvaluedialog.h"
#include "api/sql/sqlitedao.h"
#include "setlinkdialog.h"
#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void loadSubjects();
    void searchData(QString keyword, KnowledgeGraphWidgetItem* parentItem = nullptr);

private slots:
    void on_btnAddNewSubject_clicked();

    void on_lvData_clicked(const QModelIndex& index);

    void on_btnAddLink_clicked();

    void on_edtSearch_returnPressed();

private:
    Ui::MainWindow* ui;
    QStandardItemModel* m_model;
    KnowledgeGraphWidget* m_knowledgeGraphWidget;
    int m_pid;
    QStandardItemModel* m_searchModel;
};
#endif // MAINWINDOW_H
