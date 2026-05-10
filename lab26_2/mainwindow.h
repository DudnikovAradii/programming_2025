#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadClicked();

private:
    void validateAndSplitData();

    QTableWidget *correctTable;
    QTableWidget *incorrectTable;
    QPushButton *loadButton;
    QLabel *correctLabel;
    QLabel *incorrectLabel;
    QLabel *statusLabel;
};

#endif
