#include "mainwindow.h"
#include "passform.h"
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent_) : QMainWindow(parent_) {
    setupUI();
}

MainWindow::~MainWindow() {
    clearData();
}

void MainWindow::setupUI() {
    QWidget* centralWidget_ = new QWidget(this);
    setCentralWidget(centralWidget_);

    QVBoxLayout* mainLayout_ = new QVBoxLayout(centralWidget_);

    // Кнопка загрузки
    loadButton_ = new QPushButton("Загрузить");
    connect(loadButton_, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    mainLayout_->addWidget(loadButton_);

    // Таблица
    table_ = new QTableWidget();
    table_->setColumnCount(2);
    table_->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Дата рождения");
    table_->horizontalHeader()->setStretchLastSection(true);
    table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(table_, &QTableWidget::doubleClicked, this, &MainWindow::onTableDoubleClicked);
    mainLayout_->addWidget(table_);

    setWindowTitle("Список сотрудников");
    resize(600, 400);
}

void MainWindow::onLoadButtonClicked() {
    QString filename_ = QFileDialog::getOpenFileName(this, "Выберите файл с данными", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (!filename_.isEmpty()) {
        loadFromFile(filename_);
    }
}

void MainWindow::loadFromFile(const QString& filename_) {
    QFile file_(filename_);
    if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    clearData();

    QTextStream in_(&file_);
    int lineNumber_ = 0;

    while (!in_.atEnd()) {
        QString line_ = in_.readLine().trimmed();
        lineNumber_++;
        if (line_.isEmpty()) continue;

        QStringList parts_ = line_.split(",");
        if (parts_.size() < 7) {
            qDebug() << "Ошибка в строке" << lineNumber_ << ": неверный формат";
            continue;
        }

        int code_ = parts_[0].toInt();

        if (code_ == 1) { // RuP: код, Фамилия, Имя, Отчество, день, месяц, год
            QString lastName_ = parts_[1].trimmed();
            QString firstName_ = parts_[2].trimmed();
            QString patronymic_ = parts_[3].trimmed();
            if (patronymic_ == "-" || patronymic_ == "—") patronymic_ = "";

            int day_ = parts_[4].toInt();
            int month_ = parts_[5].toInt();
            int year_ = parts_[6].toInt();
            Date birthDate_(day_, month_, year_);

            if (!birthDate_.isValid()) {
                qDebug() << "Ошибка в строке" << lineNumber_ << ": неверная дата";
                continue;
            }

            // Проверка имени и фамилии
            RussianPerson tempPerson;
            if (!tempPerson.setFirstName(firstName_)) {
                qDebug() << "Ошибка в строке" << lineNumber_ << ": неверное имя";
                continue;
            }
            if (!tempPerson.setLastName(lastName_)) {
                qDebug() << "Ошибка в строке" << lineNumber_ << ": неверная фамилия";
                continue;
            }
            if (!tempPerson.setPatronymic(patronymic_)) {
                qDebug() << "Ошибка в строке" << lineNumber_ << ": неверное отчество";
                continue;
            }

            RussianPerson* person_ = new RussianPerson(lastName_, firstName_, patronymic_, birthDate_);
            persons_.append(person_);
        }
        else if (code_ == 2) { // AmP: код, Имя, ВтороеИмя, Фамилия, месяц, день, год
            QString firstName_ = parts_[1].trimmed();
            QString middleName_ = parts_[2].trimmed();
            QString lastName_ = parts_[3].trimmed();

            int month_ = parts_[4].toInt();
            int day_ = parts_[5].toInt();
            int year_ = parts_[6].toInt();
            Date birthDate_(day_, month_, year_);

            if (!birthDate_.isValid()) {
                qDebug() << "Ошибка в строке" << lineNumber_ << ": неверная дата";
                continue;
            }

            // Проверка имени, фамилии и middle name
            AmericanPerson tempPerson;
            if (!tempPerson.setFirstName(firstName_)) {
                qDebug() << "Ошибка в строке" << lineNumber_ << ": неверное имя";
                continue;
            }
            if (!tempPerson.setLastName(lastName_)) {
                qDebug() << "Ошибка в строке" << lineNumber_ << ": неверная фамилия";
                continue;
            }
            if (!tempPerson.setMiddleName(middleName_)) {
                qDebug() << "Ошибка в строке" << lineNumber_ << ": неверное middle name";
                continue;
            }

            AmericanPerson* person_ = new AmericanPerson(firstName_, middleName_, lastName_, birthDate_);
            persons_.append(person_);
        }
        else {
            qDebug() << "Ошибка в строке" << lineNumber_ << ": неизвестный код" << code_;
        }
    }

    file_.close();
    updateTable();
    QMessageBox::information(this, "Успех", QString("Загружено %1 записей").arg(persons_.size()));
}

void MainWindow::updateTable() {
    table_->setRowCount(persons_.size());
    for (int i_ = 0; i_ < persons_.size(); ++i_) {
        Person* person_ = persons_[i_];
        QTableWidgetItem* nameItem_ = new QTableWidgetItem(person_->getFullName());
        QTableWidgetItem* dateItem_ = new QTableWidgetItem(person_->getBirthDate().toString());
        table_->setItem(i_, 0, nameItem_);
        table_->setItem(i_, 1, dateItem_);
    }
}

void MainWindow::onTableDoubleClicked(const QModelIndex& index_) {
    if (!index_.isValid()) return;

    int row_ = index_.row();
    if (row_ >= 0 && row_ < persons_.size()) {
        PassForm* form_ = new PassForm(persons_[row_], this);
        connect(form_, &PassForm::personDeleted, this, &MainWindow::onPersonDeleted);
        form_->show();
    }
}

void MainWindow::onPersonDeleted(Person* person_) {
    int index_ = persons_.indexOf(person_);
    if (index_ != -1) {
        delete persons_[index_];
        persons_.remove(index_);
        updateTable();
        QMessageBox::information(this, "Успех", "Сотрудник удален из списка");
    }
}

void MainWindow::clearData() {
    qDeleteAll(persons_);
    persons_.clear();
    if (table_) {
        table_->setRowCount(0);
    }
}
