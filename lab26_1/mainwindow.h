#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConfirmClicked();
    void onLoadTxtClicked();

private:
    QLineEdit *nameEdit;
    QTextEdit *descriptionEdit;
    QLineEdit *complexityEdit;
    QLineEdit *coordXEdit;
    QLineEdit *coordYEdit;
    QPushButton *confirmButton;
    QPushButton *loadTxtButton;
};

#endif
