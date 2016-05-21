#include "mainform.h"
#include "ui_mainform.h"
#include "matrix_method.h"
#include "lup_method.h"
#include "rev_method.h"
#include <QMessageBox>
#include <QTime>
#include <QFile>
#include <QTextStream>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    updateTable(ui->spinBox->value());

}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_spinBox_valueChanged(int v)
{
   updateTable(v);
}

void MainForm::updateTable(int v)
{
    QStringList labels;
    for (int i = 0;i < v;i++)
        labels << QString("A%1").arg(i + 1);
    labels << "B";
    ui->STable->setRowCount(v);
    ui->STable->setColumnCount(v + 1);
    ui->STable->setHorizontalHeaderLabels(labels);
}

void MainForm::on_slvBtn_clicked()
{
    int n = ui->spinBox->value();
    if (ui->STable->columnCount() > n + 1)
        updateTable(n);
    if (ui->radioM->isChecked())
        SolveMatrix(n);
    else if (ui->radioR->isChecked())
        SolveRev(n);
    else if (ui->radioLUP->isChecked())
        SolveLUP(n);
    else
        Info("Оберіть метод зі списку праворуч");
}

void MainForm::SolveMatrix(int n)
{
    QTime timer;
    timer.start();
    float **A = new float * [n];
    float **B = new float * [n];
    for (int i = 0;i < n;i++)
    {
        A[i] = new float [n];
        B[i] = new float [1];
    }
    bool ok = true;
    //A
    for (int i = 0;i < n;i++)
        for (int j = 0; j < n;j++)
        {
            A[i][j] = ui->STable->item(i,j)->text().toFloat(&ok);
            if (!ok)
            {
             Error("Некорректні дані у таблиці");
             delete[] A;
             delete[] B;
             return;
            }
        }
    //B
    for (int i = 0;i < n;i++)
        B[i][0] = ui->STable->item(i,n)->text().toFloat(&ok);
    if (det(A,n) != 0)
    {
    float **Ar = inverse(A,n);
    float *X = new float[n];
    matrix_solve(Ar,B,X,n);
    ui->STable->setColumnCount(n + 2);
    ui->STable->setHorizontalHeaderItem(n + 1,new QTableWidgetItem("X"));
    FillRoots(X,n);
    WriteResult(X,n);
    delete[] A;
    delete[] Ar;
    delete[] B;
    delete[] X;

    Info(QString("Час виконання %1 мс").arg(timer.elapsed()));
    }
    else Error("Немає розв'язку: Визначник дорівнює 0");


}

void MainForm::SolveLUP(int n)
{
    QTime timer;
    timer.start();
    float **A = new float * [n];
    float *B = new float [n];
    int *P = new int [n];
    float *X = new float[n];

    for (int i = 0;i < n;i++)
    {
        A[i] = new float [n];
    }

    bool ok = true;
    //A
    for (int i = 0;i < n;i++)
        for (int j = 0; j < n;j++)
        {
            A[i][j] = ui->STable->item(i,j)->text().toFloat(&ok);
            if (!ok)
            {
             Error("Некорректні дані у таблиці");
             delete[] A;
             delete[] B;
             delete[] P;
             delete[] X;
             return;
            }
        }
    //B
    for (int i = 0;i < n;i++)
        B[i] = ui->STable->item(i,n)->text().toFloat(&ok);

    if (lup_decompose(n,A,P) != -1)
    {
        lup_solve(n,P,A,B,X);
        ui->STable->setColumnCount(n + 2);
        ui->STable->setHorizontalHeaderItem(n + 1,new QTableWidgetItem("X"));
        FillRoots(X,n);
        Info(QString("Час виконання %1 мс").arg(timer.elapsed()));
    } else Error("Немає розв'язку: Визначник дорівнює 0");

    delete[] A;
    delete[] P;
    delete[] B;
    delete[] X;
}

void MainForm::SolveRev(int n)
{
    QTime timer;
    timer.start();
    float **A = new float * [n];
    float *X = new float[n];

    for (int i = 0;i < n;i++)
    {
        A[i] = new float [n + 1];
    }

    bool ok = true;
    //A
    for (int i = 0;i < n;i++)
        for (int j = 0; j < n;j++)
        {
            A[i][j] = ui->STable->item(i,j)->text().toFloat(&ok);
            if (!ok)
            {
             Error("Некорректні дані у таблиці");
             delete[] A;
             delete[] X;
             return;
            }
        }

    for (int i = 0;i < n;i++)
        A[i][n] = ui->STable->item(i,n)->text().toFloat(&ok);

    if (det(A,n) != 0)
    {
        rev_solve(A,X,n);
        ui->STable->setColumnCount(n + 2);
        ui->STable->setHorizontalHeaderItem(n + 1,new QTableWidgetItem("X"));
        FillRoots(X,n);
        Info(QString("Час виконання %1 мс").arg(timer.elapsed()));
    } else Error("Немає розв'язку: Визначник дорівнює 0");

    delete[] A;
    delete[] X;

}

void MainForm::Error(QString e)
{
    QMessageBox msg;
    msg.setText(e);
    msg.setIcon(QMessageBox::Critical);
    msg.exec();
}

void MainForm::Info(QString i)
{
    QMessageBox msg;
    msg.setText(i);
    msg.setIcon(QMessageBox::Information);
    msg.exec();
}

void MainForm::FillRoots(float *X,int n)
{
    for (int i = 0;i < n;i++)
        ui->STable->setItem(i,n + 1,new QTableWidgetItem(QString::number(X[i])));
}

void MainForm::WriteResult(float *X, int n)
{
    QFile out("output.txt");
    if (out.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream write(&out);
        for (int i = 0;i < n;i++)
            write << X[i] << " ";
    }
    out.close();
}
