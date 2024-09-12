#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "worktaskmodel.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->descriptionEdit->setFocus();

    // Rellenar tabla con datos
    workTaskModel = new WorkTaskModel(this);
    workTaskModel->populateData(m_workTasks);

    // Conectamos el modelo con la tabla
    ui->taskTable->setModel(workTaskModel);

    // Mostramos los títulos de las columnas y la info
    ui->taskTable->horizontalHeader()->setVisible(true);
    ui->taskTable->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addTimeButton_clicked()
{
    if (ui->initTimeEdit->time() >= ui->finalTimeEdit->time()) {
        qDebug() << "Initial time later than final time\n";
        ui->statusBar->showMessage("Initial time later than final time");
    } else if (ui->descriptionEdit->text().trimmed() == "") {
        qDebug() << "Description is empty!\n";
        ui->statusBar->showMessage("Description is empty!");
    } else if (isOverlappingTask(ui->initTimeEdit->time())) {
        ui->statusBar->showMessage("Task overlaps with previous task!");
    } else {
        WorkTask wt(ui->descriptionEdit->text(), ui->initTimeEdit->time(), ui->finalTimeEdit->time());
        this->m_workTasks.append(wt);
        qDebug() << "Added!\n";
        ui->statusBar->showMessage("Added!", 5000);

        // Limpiar campos
        ui->descriptionEdit->clear();
        ui->initTimeEdit->setTime(QTime(0, 0));
        ui->finalTimeEdit->setTime(QTime(0, 0));

        // Refrescar modelo
        workTaskModel = new WorkTaskModel(this);
        workTaskModel->populateData(this->m_workTasks);
        ui->taskTable->setModel(workTaskModel);
        ui->taskTable->horizontalHeader()->setVisible(true);
        ui->taskTable->show();
    }
}


void MainWindow::on_deleteTimeButton_clicked()
{
    int index = ui->taskTable->selectionModel()->currentIndex().row();

        if(index < 0)
        {
            QMessageBox msgBox;
            msgBox.setText("Seleccione una tarea");
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText(QString("Desea borrar la tarea con ID: %1 ?").arg(workTaskModel->index(index, 0).data().toInt()));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            int ret = msgBox.exec();

            switch(ret) {
                case QMessageBox::Yes:
                    int idDelete = workTaskModel->index(index, 0).data().toInt();
                    qDebug() << "ID: " << idDelete << "\n";

                    // Borrar tarea de la lista
                    for(int index = 0; index < m_workTasks.size(); index++) {
                        if (m_workTasks.at(index).getId() == idDelete){
                            m_workTasks.removeAt(index);
                            break;
                        }
                    }

                    QMessageBox confirmacionPopup;
                    confirmacionPopup.setText("Tarea borrada!");
                    confirmacionPopup.exec();

                    // Refresh
                    workTaskModel = new WorkTaskModel(this);
                    workTaskModel->populateData(this->m_workTasks);
                    ui->taskTable->setModel(workTaskModel);
                    ui->taskTable->horizontalHeader()->setVisible(true);
                    ui->taskTable->show();

                    break;
            }
        }
}

bool MainWindow::isOverlappingTask(QTime currentInitialTime)
{
    if (m_workTasks.length() == 0)
    {
        return false;
    } else if (currentInitialTime < m_workTasks.at(m_workTasks.length() - 1).getFinalTime()) {
        return true;
    } else {
        return false;
    }
}

