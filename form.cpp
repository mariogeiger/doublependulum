#include "form.h"
#include "ui_form.h"
#include <QSettings>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    loadSettings();

    connect(ui->l1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->l2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->m1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->m2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->theta1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));
    connect(ui->theta2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(giveGuiDataToDoublePendulum()));

    connect(ui->pushButton, SIGNAL(clicked()), ui->doublePendulum, SLOT(reset()));

    giveGuiDataToDoublePendulum();
    ui->doublePendulum->reset();
}

Form::~Form()
{
    saveSettings();
    delete ui;
}

void Form::saveSettings()
{
    QSettings set;
    set.setValue("l1", ui->l1DoubleSpinBox->value());
    set.setValue("l2", ui->l2DoubleSpinBox->value());
    set.setValue("m1", ui->m1DoubleSpinBox->value());
    set.setValue("m2", ui->m2DoubleSpinBox->value());
    set.setValue("theta1", ui->theta1DoubleSpinBox->value());
    set.setValue("theta2", ui->theta2DoubleSpinBox->value());
}

void Form::loadSettings()
{
    QSettings set;
    ui->l1DoubleSpinBox->setValue(set.value("l1", ui->l1DoubleSpinBox->value()).toDouble());
    ui->l2DoubleSpinBox->setValue(set.value("l2", ui->l2DoubleSpinBox->value()).toDouble());
    ui->m1DoubleSpinBox->setValue(set.value("m1", ui->m1DoubleSpinBox->value()).toDouble());
    ui->m2DoubleSpinBox->setValue(set.value("m2", ui->m2DoubleSpinBox->value()).toDouble());
    ui->theta1DoubleSpinBox->setValue(set.value("theta1", ui->theta1DoubleSpinBox->value()).toDouble());
    ui->theta2DoubleSpinBox->setValue(set.value("theta2", ui->theta2DoubleSpinBox->value()).toDouble());
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
