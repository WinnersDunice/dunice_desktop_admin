#include "mainwindow.h"
#include "CheckProcessor.h"
#include "DataSender.h"
#include "ui_mainwindow.h"


#include <string.h>
#include <sstream>
#include <QThread>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Запрещаем кракозябры в поле ФИО
    QRegularExpression FCS("^[a-zA-Zа-яА-ЯёЁ ]+$");
    QRegularExpressionValidator *validatorFCS = new QRegularExpressionValidator(FCS, ui->FCS_FIELD);
    ui->FCS_FIELD->setValidator(validatorFCS);

    //Запрещаем кракозябры в поле id
    QRegularExpression IDF("^[0-9]+$");
    QRegularExpressionValidator *validatorIDF = new QRegularExpressionValidator(IDF, ui->ID_FIELD);
    ui->ID_FIELD->setValidator(validatorIDF);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PUSH_BUTTON_pressed()
{
    _password = ui->PASSWORD_FIELD->text();
    _login = ui->LOGIN_FIELD->text();
    _officeID = ui->ID_FIELD->text();

    QString _name = ui->FCS_FIELD->text();
    std::wistringstream iss(_name.toStdWString());
    std::wstring input;
    iss >> input;
    _firstName = QString::fromStdWString(input);
    iss >> input;
    _secondName = QString::fromStdWString(input);
    iss >> input;
    _lastName = QString::fromStdWString(input);


    if(_firstName != nullptr && _secondName != nullptr && _lastName != nullptr \
        && _login != nullptr && _password != nullptr)
    {
        CheckProcessor procCheck;
        QString ID = procCheck.BiosValue(2, 8, 8);

        std::vector<QString> data;

        data.push_back(_firstName);
        data.push_back(_secondName);
        data.push_back(_lastName);
        data.push_back(_login);
        data.push_back(_password);
        data.push_back(_officeID);
        data.push_back(ID);

        try
        {
            DataSender sender("https://api.dunicewinners.ru/register");
            sender.sendData(data);

            ui->MESSEGE_LABEL->setText("Регистрация успешна");
            ui->LOGIN_FIELD->setText("");
            ui->PASSWORD_FIELD->setText("");
            ui->FCS_FIELD->setText("");
            ui->ID_FIELD->setText("");

        }
        catch(QString& err)
        {
            if(err == "Server send not OK")
                ui->MESSEGE_LABEL->setText("Что-то не так с интернетом");
        }
    }
    else
    {
        if(_firstName == nullptr && _secondName == nullptr && _lastName == nullptr && _password == nullptr && _login == nullptr)
            ui->MESSEGE_LABEL->setText("Вы точно заполнили все поля?");
        else if((_firstName == nullptr || _secondName == nullptr || _lastName == nullptr))
            ui->MESSEGE_LABEL->setText("Что-то не так с ФИО");
        else if(_password == nullptr)
            ui->MESSEGE_LABEL->setText("Поставьте пароль, пожалуйста");
        else if(_login == nullptr)
            ui->MESSEGE_LABEL->setText("Логин обязателен");
        else
            ui->MESSEGE_LABEL->setText("Вы точно заполнили все поля?");
    }
}

void MainWindow::on_PUSH_BUTTON_clicked(){}
void MainWindow::on_FCS_FIELD_textChanged(const QString &arg1){}
void MainWindow::on_LOGIN_FIELD_textChanged(const QString &arg1){}
void MainWindow::on_PASSWORD_FIELD_textChanged(const QString &arg1){}
