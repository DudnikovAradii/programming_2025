#ifndef PASSFORM_H
#define PASSFORM_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QRandomGenerator>
#include <QPixmap>
#include <QPainter>
#include <QRegularExpression>
#include <QCoreApplication>
#include <QEvent>
#include <QDebug>

class Person;

class PassForm : public QDialog {
    Q_OBJECT

private:
    Person* person_;
    QLabel* nameLabel_;
    QLabel* birthLabel_;
    QLabel* imageLabel_;
    QPushButton* cancelButton_;
    QPushButton* printButton_;

    static const int IMAGE_MODE_ = 2; // 1 - статичная, 2 - рандомная, 3 - уникальная

public:
    explicit PassForm(Person* person_, QWidget* parent_ = nullptr);
    ~PassForm();

signals:
    void personDeleted(Person* person_);  // Сигнал для удаления

private slots:
    void onCancel();
    void onPrint();

private:
    void setupUI();
    void setupImage();
};

#endif // PASSFORM_H
