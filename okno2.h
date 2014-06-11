#ifndef OKNO2_H
#define OKNO2_H

#include <QMainWindow>
#include <vector>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
namespace Ui {
class okno2;
}

class okno2 : public QMainWindow
{
    Q_OBJECT
    QPushButton* przycisk;
    QPushButton* przycisk_q;
    std::vector<QLabel*> fabryki;
    std::vector<QLabel*> centra;
    int il_fabr;
    int il_centr;
    std::vector<int> dane;
    std::vector<std::vector<QLineEdit*> > formularz;
    std::vector<std::vector<QLineEdit*> > formularz2;
    std::vector<QLabel*> fabryki2;
    std::vector<QLabel*> centra2;
    QLabel* koszt_l;
    QLineEdit* koszt_w;
public:
    explicit okno2(QWidget *parent = 0);
    ~okno2();
public slots:
    void ustaw_f(QString wart);
    void ustaw_c(QString wart);
    void conf();
    void zbierz_dane();

private:
    Ui::okno2 *ui;
};

#endif // OKNO2_H
