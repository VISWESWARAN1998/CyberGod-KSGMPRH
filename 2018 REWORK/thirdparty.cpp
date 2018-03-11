#include "thirdparty.hpp"
#include "ui_thirdparty.h"
#include <QFile>
#include <QTextStream>

ThirdParty::ThirdParty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdParty)
{
    ui->setupUi(this);
    QFile file("licenses.txt");
    if(file.open(QFile::ReadOnly))
    {
        QTextStream stream(&file);
        ui->thirdParty_LiceneDisplayBrowser->setText(stream.readAll());
        file.close();
    }
}

ThirdParty::~ThirdParty()
{
    delete ui;
}
