#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_slvBtn_clicked();

private:
    Ui::MainForm *ui;
    void updateTable(int);
    void SolveMatrix(int);
    void SolveLUP(int);
    void SolveRev(int);
    void Error(QString);
    void FillRoots(float*,int);
    void Info(QString);
    void WriteResult(float*,int);
};

#endif // MAINFORM_H
