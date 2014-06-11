#ifndef OKNO1_H
#define OKNO1_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
namespace Ui {
class okno1;
}

class okno1 : public QMainWindow
{
    Q_OBJECT
    QLabel* lab1;
    QLabel* lab2;
    QPushButton* button;
    QLineEdit* lin1;
    QLineEdit* lin2;
public:
    explicit okno1(QWidget *parent = 0);
    ~okno1();
    void conf();

public slots:
    void ustaw_fabryki();
    void ustaw_centra();
    void zakoncz();

signals:
    void fabryki(QString wart);
    void centra(QString wart);
    void koniec();

private:
    Ui::okno1 *ui;
};

#endif // OKNO1_H
