#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    connect(ui->l1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->l2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->m1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->m2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->theta1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->theta2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));

    connect(ui->pushButton, SIGNAL(clicked()), ui->doublePendulum, SLOT(reset()));

    giveGuiDataToDoublePendulum();
}

Form::~Form()
{
    delete ui;
}

void Form::giveGuiDataToDoublePendulum()
{
    ui->doublePendulum->setParameters(ui->m1DoubleSpinBox->value(),
                                      ui->m2DoubleSpinBox->value(),
                                      ui->l1DoubleSpinBox->value(),
                                      ui->l2DoubleSpinBox->value(),
                                      ui->theta1DoubleSpinBox->value(),
                                      ui->theta2DoubleSpinBox->value());
}
