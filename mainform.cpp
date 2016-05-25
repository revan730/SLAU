#include "mainform.h"
#include "ui_mainform.h"
#include "matrix_method.h"
#include "lup_method.h"
#include "rev_method.h"
#include "qcustomplot.h"
#include <QMessageBox>
#include <QElapsedTimer>
#include <QFile>
#include <QTextStream>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);//Инициализация интерфейса
    updateTable(ui->spinBox->value());//Построение таблицы

}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_spinBox_valueChanged(int v)//Вызывается при изменении порядка системы
{
   updateTable(v);//Обновление таблицы
}

void MainForm::updateTable(int v)
{
    QStringList labels;
    for (int i = 0;i < v;i++)
        labels << QString("A%1").arg(i + 1);//Вставка подписей столбиков таблицы
    labels << "B";
    ui->STable->setRowCount(v);//Установка количества строк
    ui->STable->setColumnCount(v + 1);//...количества столбиков
    ui->STable->setHorizontalHeaderLabels(labels);//Установка подписей таблицы
}

void MainForm::on_slvBtn_clicked()//Вызывается при нажатии на кнопку "Розв'язати"
{
    int n = ui->spinBox->value();
    //В зависимости от нажатой кнопки, вызываем соответсвующий метод
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

void MainForm::SolveMatrix(int n)//Матричный метод
{
    QElapsedTimer timer;//Таймер для измерения время работы
    double **A = new double * [n];//Основная матрица
    double **B = new double * [n];//Вектор свободных членов
    int ic = 0,oc = 0;//Счетчики итераций и операций

    for (int i = 0;i < n;i++)
    {
        A[i] = new double [n];
        B[i] = new double [1];
    }
    bool ok = true;
    //Ввод данных в матрицу А
    for (int i = 0;i < n;i++)
        for (int j = 0; j < n;j++)
        {
            A[i][j] = ui->STable->item(i,j)->text().toDouble(&ok);
            if (!ok)
            {
             Error("Некорректні дані у таблиці");
             delete[] A;
             delete[] B;
             return;
            }
        }
    //Ввод данных в матрицу В
    for (int i = 0;i < n;i++)
        B[i][0] = ui->STable->item(i,n)->text().toDouble(&ok);
    if (det(A,n) != 0)
    {
        //Само решение
        timer.start();
        double **Ar = inverse(A,n,ic,oc);//Обратная матрица А
        double *X = new double[n];//Вектор Х
        matrix_solve(Ar,B,X,n,ic,oc);
        Info(QString("Час виконання %1 мс,ітерацій - %2 ,операцій - %3").arg(timer.elapsed()).arg(ic).arg(oc));
        ui->STable->setColumnCount(n + 2);
        ui->STable->setHorizontalHeaderItem(n + 1,new QTableWidgetItem("X"));
        //Вывод результата в таблицу
        FillRoots(X,n);
        WriteResult(X,n);
        if (n == 2)
            //Построение графика,если порядок равен 2
            DrawPlot();
        //Освобождение памяти
        delete[] A;
        delete[] Ar;
        delete[] B;
        delete[] X;

    }
    else Error("Немає розв'язку: Визначник дорівнює 0");


}

void MainForm::SolveLUP(int n)//LUP метод
{
    QElapsedTimer timer;
    double **A = new double * [n];
    double *B = new double [n];
    int *P = new int [n];//Матрица перестановок Р
    double *X = new double[n];
    int ic = 0, oc = 0;

    for (int i = 0;i < n;i++)
    {
        A[i] = new double [n];
    }

    bool ok = true;
    //Ввод данных для матрицы А
    for (int i = 0;i < n;i++)
        for (int j = 0; j < n;j++)
        {
            A[i][j] = ui->STable->item(i,j)->text().toDouble(&ok);
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
    //Ввод данных для матрицы В
    for (int i = 0;i < n;i++)
        B[i] = ui->STable->item(i,n)->text().toDouble(&ok);
    timer.start();
    if (lup_decompose(n,A,P,ic,oc) != -1)
    {
        //Само решение
        lup_solve(n,P,A,B,X,ic,oc);
        Info(QString("Час виконання %1 мс,ітерацій - %2 ,операцій - %3").arg(timer.elapsed()).arg(ic).arg(oc));
        ui->STable->setColumnCount(n + 2);
        ui->STable->setHorizontalHeaderItem(n + 1,new QTableWidgetItem("X"));
        FillRoots(X,n);
        WriteResult(X,n);
        if (n == 2)
            DrawPlot();
    } else Error("Немає розв'язку: Визначник дорівнює 0");

    delete[] A;
    delete[] P;
    delete[] B;
    delete[] X;
}

void MainForm::SolveRev(int n)
{
    QElapsedTimer timer;
    double **A = new double * [n];
    double *X = new double[n];
    int ic,oc;

    for (int i = 0;i < n;i++)
    {
        A[i] = new double [n + 1];
    }

    bool ok = true;
    //Ввод данных для матрицы А
    for (int i = 0;i < n;i++)
        for (int j = 0; j < n;j++)
        {
            A[i][j] = ui->STable->item(i,j)->text().toDouble(&ok);
            if (!ok)
            {
             Error("Некорректні дані у таблиці");
             delete[] A;
             delete[] X;
             return;
            }
        }
    //Ввод данных для матрицы В
    for (int i = 0;i < n;i++)
        A[i][n] = ui->STable->item(i,n)->text().toDouble(&ok);

    if (det(A,n) != 0)
    {
        timer.start();
        int time = rev_solve(A,X,n,ic,oc);
        Info(QString("Час виконання %1 мс,ітерацій - %2 ,операцій - %3").arg(time).arg(ic).arg(oc));
        ui->STable->setColumnCount(n + 2);
        ui->STable->setHorizontalHeaderItem(n + 1,new QTableWidgetItem("X"));
        FillRoots(X,n);
        WriteResult(X,n);
        if (n == 2)
            DrawPlot();
    } else Error("Немає розв'язку: Визначник дорівнює 0");

    delete[] A;
    delete[] X;

}

void MainForm::Error(QString e)//Вывод окна с сообщением про ошибку
{
    QMessageBox msg;
    msg.setText(e);
    msg.setIcon(QMessageBox::Critical);
    msg.exec();
}

void MainForm::Info(QString i)//Вывод окна с информационным сообщением
{
    QMessageBox msg;
    msg.setText(i);
    msg.setIcon(QMessageBox::Information);
    msg.exec();
}

void MainForm::FillRoots(double *X,int n)//Заполнение таблицы корнями системы
{
    for (int i = 0;i < n;i++)
        ui->STable->setItem(i,n + 1,new QTableWidgetItem(QString::number(X[i])));
}

void MainForm::WriteResult(double *X, int n)//Вывод результатов в файл
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

void MainForm::DrawPlot()//Постройка графика
{
    //Создание окна
    QCustomPlot *plot = new QCustomPlot;
    plot->setFixedSize(QSize(200,200));
    plot->setWindowTitle("Графік");
    plot->show();
    //Получение коефициентов из таблицы
    double A11 = ui->STable->item(0,0)->text().toDouble();
    double A21 = ui->STable->item(0,1)->text().toDouble();
    double B1 = ui->STable->item(0,2)->text().toDouble();
    double A12 = ui->STable->item(1,0)->text().toDouble();
    double A22 = ui->STable->item(1,1)->text().toDouble();
    double B2 = ui->STable->item(1,2)->text().toDouble();
    QVector<double> X(200),Y1(200),Y2(200);
    //Генерация точек для отрисовки
    for (int i = 0;i < 100;i++)
    {
        X[i] = i;
        Y1[i] = (B1 - A11 * X[i]) / A21;
        Y2[i] = (B2 - A12 * X[i]) / A22;
    }

    for (int i = 99;i < 200;i++)
    {
        X[i] = - i;
        Y1[i] = (B1 - A11 * X[i]) / A21;
        Y2[i] = (B2 - A12 * X[i]) / A22;
    }
    //Инициализация холста
        plot->addGraph();
        plot->addGraph();
        plot->graph(0)->setData(X,Y1);
        plot->graph(1)->setData(X,Y2);
        plot->graph(1)->setPen(QPen(Qt::red));
        connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
        connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));
        plot->graph(0)->rescaleAxes();
        plot->graph(1)->rescaleAxes(true);
        plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//Даем возможность взаимодействия с графиком
        plot->replot();//Построение графика
}
