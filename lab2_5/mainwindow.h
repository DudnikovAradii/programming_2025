#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QMessageBox>
#include <QDebug>

#include "person.h"
#include "russianperson.h"
#include "americanperson.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QTableWidget* table_;
    QPushButton* loadButton_;
    QVector<Person*> persons_;

public:
    MainWindow(QWidget* parent_ = nullptr);
    ~MainWindow();

private slots:
    void onLoadButtonClicked();
    void onTableDoubleClicked(const QModelIndex& index_);
    void onPersonDeleted(Person* person_);

private:
    void setupUI();
    void loadFromFile(const QString& filename_);
    void updateTable();
    void clearData();
};

#endif // MAINWINDOW_H
