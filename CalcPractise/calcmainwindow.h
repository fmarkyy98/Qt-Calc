#ifndef CALCMAINWINDOW_H
#define CALCMAINWINDOW_H

#include <QMainWindow>
#include "operator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CalcMainWindow; }
QT_END_NAMESPACE

class CalcMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalcMainWindow(QWidget *parent = nullptr);
    ~CalcMainWindow();

private slots:
    void manageOperator();
    void on_generateOrSolv_PushButton_clicked();

private:
    Ui::CalcMainWindow *ui;
    int lhsOperand = 0;
    int rhsOperand = 0;
    Operator _operator = Operator::addition;
    bool isGenerated = false;

    void manageUiGeneratedChange();
    void generateOperands(Operator o);
    QString solv(Operator o);

};
#endif // CALCMAINWINDOW_H
