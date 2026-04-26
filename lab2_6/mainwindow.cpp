#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QInputDialog>
#include <cmath>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QHBoxLayout *topLayout = new QHBoxLayout();

    QVBoxLayout *formLayout = new QVBoxLayout();

    nameEdit = new QLineEdit();
    descriptionEdit = new QLineEdit();

    difficultySpin = new QSpinBox();
    difficultySpin->setRange(-1000, 1000);
    difficultySpin->setValue(5);
    difficultySpin->setToolTip("Сложность должна быть от 1 до 10");

    xSpin = new QDoubleSpinBox();
    ySpin = new QDoubleSpinBox();

    xSpin->setRange(-1000.0, 1000.0);
    ySpin->setRange(-1000.0, 1000.0);
    xSpin->setDecimals(2);
    ySpin->setDecimals(2);

    formLayout->addWidget(new QLabel("Название:"));
    formLayout->addWidget(nameEdit);

    formLayout->addWidget(new QLabel("Описание:"));
    formLayout->addWidget(descriptionEdit);

    formLayout->addWidget(new QLabel("Сложность (1-10):"));
    formLayout->addWidget(difficultySpin);

    formLayout->addWidget(new QLabel("Координата X:"));
    formLayout->addWidget(xSpin);

    formLayout->addWidget(new QLabel("Координата Y:"));
    formLayout->addWidget(ySpin);

    QVBoxLayout *buttonLayout = new QVBoxLayout();

    addButton = new QPushButton("Добавить");
    loadTxtButton = new QPushButton("Загрузить TXT");
    loadJsonButton = new QPushButton("Загрузить JSON");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(loadTxtButton);
    buttonLayout->addWidget(loadJsonButton);
    buttonLayout->addStretch();

    topLayout->addLayout(formLayout, 3);
    topLayout->addLayout(buttonLayout, 1);

    QHBoxLayout *tablesLayout = new QHBoxLayout();

    validTable = new QTableWidget();
    invalidTable = new QTableWidget();

    QVBoxLayout *validLayout = new QVBoxLayout();
    validLayout->addWidget(new QLabel("Корректные"));
    validLayout->addWidget(validTable);

    QVBoxLayout *invalidLayout = new QVBoxLayout();
    invalidLayout->addWidget(new QLabel("Ошибки"));
    invalidLayout->addWidget(invalidTable);

    tablesLayout->addLayout(validLayout);
    tablesLayout->addLayout(invalidLayout);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(tablesLayout);

    connect(addButton, &QPushButton::clicked, [=]() {
        PointOfInterest p;
        p.name = nameEdit->text();
        p.description = descriptionEdit->text();
        p.difficulty = difficultySpin->value();
        p.x = xSpin->value();
        p.y = ySpin->value();

        list.append(p);

        saveToJson("data.json", list);

        if (p.isValid()) {
            QMessageBox::information(this, "Успешно",
                                     QString("Объект \"%1\" добавлен в JSON файл").arg(p.name));
        } else {
            QString errors;
            if (p.name.isEmpty()) errors += "- Название пустое\n";
            if (p.description.isEmpty()) errors += "- Описание пустое\n";

            QRegularExpression regex("\\d");
            if (p.name.contains(regex) || p.description.contains(regex))
                errors += "- Название или описание содержат цифры\n";

            if (p.difficulty < 1 || p.difficulty > 10)
                errors += "- Сложность должна быть от 1 до 10 (текущее: " + QString::number(p.difficulty) + ")\n";
            if (std::isnan(p.x) || std::isinf(p.x))
                errors += "- Координата X некорректна\n";
            if (std::isnan(p.y) || std::isinf(p.y))
                errors += "- Координата Y некорректна\n";

            QMessageBox::warning(this, "Объект с ошибками",
                                 QString("Объект \"%1\" добавлен в JSON, но содержит ошибки:\n%2")
                                     .arg(p.name.isEmpty() ? "без имени" : p.name)
                                     .arg(errors));
        }

        nameEdit->clear();
        descriptionEdit->clear();
        difficultySpin->setValue(5);
        xSpin->setValue(0);
        ySpin->setValue(0);
    });

    connect(loadTxtButton, &QPushButton::clicked, [=]() {
        QString path = QFileDialog::getOpenFileName(this, "Выберите TXT файл", "", "*.txt");
        if (path.isEmpty()) return;

        auto loaded = loadFromTxt(path);
        list.append(loaded);

        saveToJson("data.json", list);

        QMessageBox::information(this, "Загрузка TXT",
                                 QString("Загружено %1 объектов из TXT и добавлено в JSON файл").arg(loaded.size()));
    });

    connect(loadJsonButton, &QPushButton::clicked, [=]() {
        QString path = QFileDialog::getOpenFileName(this, "Выберите JSON файл", "", "*.json");
        if (path.isEmpty()) return;

        if (path.isEmpty()) {
            path = "data.json";
        }

        QStringList options = {"Только корректные", "Только с ошибками", "Все объекты"};
        bool ok;
        QString choice = QInputDialog::getItem(this, "Выбор таблицы",
                                               "Какие данные загрузить?",
                                               options, 0, false, &ok);

        if (!ok) return;

        QList<PointOfInterest> valid, invalid;
        loadAndSplit(path, valid, invalid);

        clearTables();

        if (choice == "Только корректные") {
            fillTable(validTable, valid);
            fillTable(invalidTable, QList<PointOfInterest>());
            QMessageBox::information(this, "Загрузка JSON",
                                     QString("Загружено %1 корректных объектов").arg(valid.size()));
        }
        else if (choice == "Только с ошибками") {
            fillTable(validTable, QList<PointOfInterest>());
            fillTable(invalidTable, invalid);
            QMessageBox::information(this, "Загрузка JSON",
                                     QString("Загружено %1 объектов с ошибками").arg(invalid.size()));
        }
        else if (choice == "Все объекты") {
            fillTable(validTable, valid);
            fillTable(invalidTable, invalid);
            QMessageBox::information(this, "Загрузка JSON",
                                     QString("Загружено всего %1 объектов (корректных: %2, с ошибками: %3)")
                                         .arg(valid.size() + invalid.size())
                                         .arg(valid.size())
                                         .arg(invalid.size()));
        }
    });
}

void MainWindow::clearTables()
{
    validTable->clear();
    validTable->setRowCount(0);
    validTable->setColumnCount(0);

    invalidTable->clear();
    invalidTable->setRowCount(0);
    invalidTable->setColumnCount(0);
}

QList<PointOfInterest> MainWindow::loadFromTxt(QString path)
{
    QList<PointOfInterest> loadedList;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
        return loadedList;

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split("/");

        if (parts.size() != 5)
            continue;

        PointOfInterest p;
        p.name = parts[0];
        p.description = parts[1];
        p.difficulty = parts[2].toInt();
        p.x = parts[3].toDouble();
        p.y = parts[4].toDouble();

        loadedList.append(p);
    }

    file.close();
    return loadedList;
}

void MainWindow::saveToJson(QString path, QList<PointOfInterest> list)
{
    QJsonArray arr;

    for (auto p : list)
        arr.append(p.toJson());

    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(arr).toJson());
        file.close();
    }
}

void MainWindow::loadAndSplit(QString path,
                              QList<PointOfInterest> &valid,
                              QList<PointOfInterest> &invalid)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonArray arr = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    for (auto val : arr)
    {
        auto p = PointOfInterest::fromJson(val.toObject());

        if (p.isValid())
            valid.append(p);
        else
            invalid.append(p);
    }
}

void MainWindow::fillTable(QTableWidget *table, QList<PointOfInterest> list)
{
    table->setRowCount(list.size());
    table->setColumnCount(5);

    QStringList headers = {"Название", "Описание", "Сложность", "X", "Y"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);

    auto hasDigits = [](const QString& str) -> bool {
        for (QChar ch : str) {
            if (ch.isDigit()) return true;
        }
        return false;
    };

    for (int i = 0; i < list.size(); i++)
    {
        auto p = list[i];

        QTableWidgetItem *nameItem = new QTableWidgetItem(p.name);
        if (p.name.isEmpty() || hasDigits(p.name)) {
            nameItem->setBackground(Qt::red);
            nameItem->setForeground(Qt::white);
        }
        table->setItem(i, 0, nameItem);

        QTableWidgetItem *descItem = new QTableWidgetItem(p.description);
        if (p.description.isEmpty() || hasDigits(p.description)) {
            descItem->setBackground(Qt::red);
            descItem->setForeground(Qt::white);
        }
        table->setItem(i, 1, descItem);

        QTableWidgetItem *difficultyItem = new QTableWidgetItem(QString::number(p.difficulty));
        if (p.difficulty < 1 || p.difficulty > 10) {
            difficultyItem->setBackground(Qt::red);
            difficultyItem->setForeground(Qt::white);
        }
        table->setItem(i, 2, difficultyItem);

        QTableWidgetItem *xItem = new QTableWidgetItem(QString::number(p.x, 'f', 2));
        if (std::isnan(p.x) || std::isinf(p.x)) {
            xItem->setBackground(Qt::red);
            xItem->setForeground(Qt::white);
        }
        table->setItem(i, 3, xItem);

        QTableWidgetItem *yItem = new QTableWidgetItem(QString::number(p.y, 'f', 2));
        if (std::isnan(p.y) || std::isinf(p.y)) {
            yItem->setBackground(Qt::red);
            yItem->setForeground(Qt::white);
        }
        table->setItem(i, 4, yItem);
    }

    table->resizeColumnsToContents();
}
