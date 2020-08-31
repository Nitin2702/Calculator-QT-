#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cctype>
#include <cmath>
double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_plusminus,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    connect(ui->pushButton_sin,SIGNAL(released()),this,SLOT(trigo_operation_pressed()));
    connect(ui->pushButton_isin,SIGNAL(released()),this,SLOT(trigo_operation_pressed()));
    connect(ui->pushButton_cos,SIGNAL(released()),this,SLOT(trigo_operation_pressed()));
    connect(ui->pushButton_icos,SIGNAL(released()),this,SLOT(trigo_operation_pressed()));
    connect(ui->pushButton_tan,SIGNAL(released()),this,SLOT(trigo_operation_pressed()));
    connect(ui->pushButton_itan,SIGNAL(released()),this,SLOT(trigo_operation_pressed()));


    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);

    ui->pushButton_sin->setCheckable(true);
    ui->pushButton_cos->setCheckable(true);
    ui->pushButton_tan->setCheckable(true);
    ui->pushButton_isin->setCheckable(true);
    ui->pushButton_icos->setCheckable(true);
    ui->pushButton_itan->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;

   }


void MainWindow::digit_pressed()
{
    QPushButton * button=(QPushButton*)sender();

    double labelNumber;
    QString newLabel;


    if ((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() || ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber))

    {
      labelNumber =button->text().toDouble();
      userIsTypingSecondNumber = true;
      newLabel = QString::number(labelNumber,'g',15);
    }

    else
    {
            if (ui->label->text().contains('.') && button->text() == "0")
            {
                newLabel= ui->label->text() + button->text();
            }
            else
            {
                labelNumber= (ui->label->text() + button->text()).toDouble();
                newLabel=QString::number(labelNumber,'g',15);
            }
    }

    ui->label->setText(newLabel);

}



void MainWindow::on_pushButton_decimal_released()
{
    {
        if(!ui->label->text().count(QLatin1Char('.'))) {
            ui->label->setText(ui->label->text() + ".");
        }

    }
}


void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    if(button->text()=="+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    if(button->text()=="%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * .01;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }
}

void MainWindow::on_pushButton_clear_released()
{

    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_sin->setChecked(false);
    ui->pushButton_cos->setChecked(false);
    ui->pushButton_tan->setChecked(false);
    ui->pushButton_isin->setChecked(false);
    ui->pushButton_icos->setChecked(false);
    ui->pushButton_itan->setChecked(false);

    userIsTypingSecondNumber = false;

    ui->label->setText("0");

}

void MainWindow::on_pushButton_equal_released()
{

    double labelNumber,secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if (ui->pushButton_add->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_add->setChecked(false);
    }
    else if (ui->pushButton_subtract->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_subtract->setChecked(false);

    }
    else if (ui->pushButton_multiply->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_multiply->setChecked(false);

    }
    else if (ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_divide->setChecked(false);

    }
            userIsTypingSecondNumber = false;

}


void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);
}


void MainWindow::trigo_operation_pressed()
{

    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    if(button->text()=="sin")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * (3.14159265358979323846/180);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        labelNumber = std::sin(labelNumber);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    else if(button->text()=="cos")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * (3.14159265358979323846/180);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        labelNumber = std::cos(labelNumber);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    else if(button->text()=="tan")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * (3.14159265358979323846/180);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        labelNumber = std::tan(labelNumber);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    else if(button->text()=="asin")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = std::asin(labelNumber);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        labelNumber = labelNumber * (180/3.14159265358979323846);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    else if(button->text()=="acos")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = std::acos(labelNumber);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        labelNumber = labelNumber * (180/3.14159265358979323846);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    else if(button->text()=="atan")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = std::atan(labelNumber);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        labelNumber = labelNumber * (180/3.14159265358979323846);
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }
}
