#include <QTime>
#include <QString>
#include "calcmainwindow.h"
#include "ui_calcmainwindow.h"

#define VALIDATE_MACRO(Operator, Show) { (lhsOperand Operator rhsOperand == solution ? "Correct: " : "Incorrect: ") + QString::number(this->lhsOperand) + Show + QString::number(this->rhsOperand) + " = " + QString::number(solution) + "\n" }
//Validates if correct or not, and Build the QString for the output.

CalcMainWindow::CalcMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CalcMainWindow)
{
    qsrand(QTime::currentTime().msec());
    ui->setupUi(this);
    ui->lhsOperand_spinBox->setEnabled(false);
    ui->rhsOperand_spinBox->setEnabled(false);
    ui->solution_spinBox->setEnabled(false);
    connect(ui->addition_radioButton, SIGNAL(clicked()), this, SLOT(manageOperator()));
    connect(ui->subtraction_radioButton, SIGNAL(clicked()), this, SLOT(manageOperator()));
    connect(ui->multiplication_radioButton, SIGNAL(clicked()), this, SLOT(manageOperator()));
    connect(ui->division_radioButton, SIGNAL(clicked()), this, SLOT(manageOperator()));
}

CalcMainWindow::~CalcMainWindow()
{
    delete ui;
}

void CalcMainWindow::manageOperator()
{
    if(ui->addition_radioButton->isChecked())
    {
        this->_operator = Operator::addition;
        ui->operator_label->setText("+");
    }
    else if(ui->subtraction_radioButton->isChecked())
    {
        this->_operator = Operator::subtraction;
        ui->operator_label->setText("-");
    }
    else if(ui->multiplication_radioButton->isChecked())
    {
        this->_operator = Operator::multiplication;
        ui->operator_label->setText("*");
    }
    else if(ui->division_radioButton->isChecked())
    {
        this->_operator = Operator::division;
        ui->operator_label->setText("/");
    }
}

void CalcMainWindow::manageUiGeneratedChange()
{
    if(isGenerated)
    {
        ui->generateOrSolv_PushButton->setText("Solv");
    }
    else
    {
        ui->generateOrSolv_PushButton->setText("Generate");
    }
    ui->addition_radioButton->setEnabled(!isGenerated);
    ui->subtraction_radioButton->setEnabled(!isGenerated);
    ui->multiplication_radioButton->setEnabled(!isGenerated);
    ui->division_radioButton->setEnabled(!isGenerated);
    ui->lhsOperand_spinBox->setEnabled(isGenerated);
    ui->rhsOperand_spinBox->setEnabled(isGenerated);
    ui->solution_spinBox->setEnabled(isGenerated);
}

void CalcMainWindow::generateOperands(Operator o)
{
    switch (o)
    {
    case addition:
        this->lhsOperand = qrand() % 100 + 1;
        this->rhsOperand = qrand() % (100 - this->lhsOperand) + 1;
        break;
    case subtraction:
        this->lhsOperand = qrand() % 100 + 1;
        this->rhsOperand = qrand() % this->lhsOperand + 1;
        break;
    case multiplication:
        this->lhsOperand = qrand() % 10 + 1;
        this->rhsOperand = qrand() % 10 + 1;
        break;
    case division:
        this->lhsOperand = qrand() % 10 + 1;
        this->rhsOperand = qrand() % 10 + 1;
        this->lhsOperand *= this->rhsOperand;
        break;
    }
    ui->lhsOperand_spinBox->setValue(this->lhsOperand);
    ui->rhsOperand_spinBox->setValue(this->rhsOperand);
}

QString CalcMainWindow::solv(Operator o)
{
    QString result = "";
    int solution = ui->solution_spinBox->value();
    switch (o)
    {
    case addition:
        result += VALIDATE_MACRO(+, " + ");
        break;
    case subtraction:
        result += VALIDATE_MACRO(-, " - ");
        break;
    case multiplication:
        result += VALIDATE_MACRO(*, " * ");
        break;
    case division:
        result += VALIDATE_MACRO(/, " / ");
        break;
    }
    QString currentText = ui->textEdit->toPlainText();
    ui->textEdit->setText(currentText + result);
    return result;
}

void CalcMainWindow::on_generateOrSolv_PushButton_clicked()
{
    isGenerated = !isGenerated;
    if(isGenerated)
    {
        ui->solution_spinBox->setMaximum(this->_operator == division ? 10 : 100);
        generateOperands(this->_operator);
    }
    else
    {
        solv(this->_operator);
    }
    manageUiGeneratedChange();
}
