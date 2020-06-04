#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_knowledgeGraphWidget = new KnowledgeGraphWidget(ui->wgtClient);
    QHBoxLayout* lay = new QHBoxLayout();
    ui->wgtClient->setLayout(lay);
    lay->setMargin(0);
    lay->addWidget(m_knowledgeGraphWidget);
    m_model = new QStandardItemModel(this);
    ui->lvData->setModel(m_model);
    m_searchModel = new QStandardItemModel(this);
    loadSubjects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSubjects()
{

    QSqlQuery qry;
    QString sql;
    sql = "select id,name from subject order by id";
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    m_model->removeRows(0, m_model->rowCount());
    while (qry.next()) {
        QStandardItem* item = new QStandardItem();
        item->setText(qry.value("name").toString());
        item->setData(qry.value("id").toInt());
        m_model->appendRow(item);
    }
}

void MainWindow::searchData(QString keyword, KnowledgeGraphWidgetItem* parentItem)
{

    if (parentItem == nullptr) {
        parentItem = m_knowledgeGraphWidget->addRootItem(keyword);
    }
    QSqlQuery qry;
    QString sql;
    sql = "select id,name,value from link where name='" + keyword + "' and pid=" + QString("%1").arg(m_pid);
    qDebug() << sql;
    sqliteDao()->sqliteWrapper()->select(sql, qry);

    while (qry.next()) {
        QString linkName = qry.value(1).toString() + "_" + qry.value(2).toString();
        if (!m_knowledgeGraphWidget->linkNames.contains(linkName)) {
            KnowledgeGraphWidgetItem* item = m_knowledgeGraphWidget->addItem(qry.value(0).toInt(),
                qry.value(1).toString(), qry.value(2).toString());
            if (item->parentItem() == nullptr) {
                item->setParentItem(parentItem);
            }
            m_knowledgeGraphWidget->linkNames << linkName;
            m_knowledgeGraphWidget->AddLink(qry.value(1).toString(), qry.value(2).toString());
            searchData(item->value(), item);
        } else {
            qDebug() << linkName;
        }
    }
}

void MainWindow::on_btnAddNewSubject_clicked()
{
    QString name;
    bool ret = setValue("新建主题", "主题", name);
    if (ret == false) {
        return;
    }
    sqliteDao()->sqliteWrapper()->execute(QString("insert into subject(name) values ('%1')").arg(name));
}

void MainWindow::on_lvData_clicked(const QModelIndex& index)
{
    QStandardItem* item = m_model->itemFromIndex(index);
    m_pid = item->data().toInt();
}

void MainWindow::on_btnAddLink_clicked()
{
    SetLinkDialog* dlg = new SetLinkDialog();
    int ret = dlg->exec();
    if (ret == QDialog::Accepted) {
        QString sql = QString("insert into link(pid,name,value) "
                              " values(%1,'%2','%3')")
                          .arg(m_pid)
                          .arg(dlg->getName())
                          .arg(dlg->getValue());
        sqliteDao()->sqliteWrapper()->execute(sql);
    }
    delete dlg;
}

void MainWindow::on_edtSearch_returnPressed()
{
    QSqlQuery qry;
    QString sql = "select distinct name from link where name like '%" + ui->edtSearch->text() + "%' and pid=" + QString("%1").arg(m_pid);
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    m_searchModel->removeRows(0, m_searchModel->rowCount());
    int n = 0;
    while (qry.next()) {
        QStandardItem* item = new QStandardItem();
        item->setText(qry.value(0).toString());
        m_searchModel->appendRow(item);
        n++;
    }
    if (n == 0) {

    } else if (n == 1) {

        searchData(m_searchModel->item(0)->text());
        m_knowledgeGraphWidget->update();
    } else {
        searchData(m_searchModel->item(0)->text());
        m_knowledgeGraphWidget->update();
    }
}
