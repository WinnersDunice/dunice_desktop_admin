#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
private:
    Ui::MainWindow *ui;
    QString _firstName = nullptr, _secondName = nullptr, _lastName = nullptr;
    QString _login = nullptr;
    QString _password = nullptr;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_FCS_FIELD_textChanged(const QString &arg1);

    void on_LOGIN_FIELD_textChanged(const QString &arg1);

    void on_PASSWORD_FIELD_textChanged(const QString &arg1);

    void on_PUSH_BUTTON_clicked();


    void on_PUSH_BUTTON_pressed();
};
#endif // MAINWINDOW_H
