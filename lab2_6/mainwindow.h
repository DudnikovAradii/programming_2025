#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTableWidget>

#include "pointofinterest.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QList<PointOfInterest> list;

    QLineEdit *nameEdit;
    QLineEdit *descriptionEdit;
    QSpinBox *difficultySpin;
    QDoubleSpinBox *xSpin;
    QDoubleSpinBox *ySpin;

    QPushButton *addButton;
    QPushButton *loadTxtButton;
    QPushButton *loadJsonButton;

    QTableWidget *validTable;
    QTableWidget *invalidTable;

    void setupUI();

    QList<PointOfInterest> loadFromTxt(QString path);
    void saveToJson(QString path, QList<PointOfInterest> list);
    void loadAndSplit(QString path,
                      QList<PointOfInterest> &valid,
                      QList<PointOfInterest> &invalid);
    void fillTable(QTableWidget *table, QList<PointOfInterest> list);
    void clearTables();
};

#endif
