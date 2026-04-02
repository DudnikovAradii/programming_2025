#include "mainwindow.h"
#include "passform.h"
#include "russianperson.h"
#include "americanperson.h"
#include <QHeaderView>
#include <QDebug>

// Функция для показа ошибок
static void showFormatError(QWidget* parent, const QString& fieldName, const QString& expectedFormat, int lineNumber) {
    QMessageBox::warning(parent, "Ошибка формата",
                         QString("Строка %1: Неверный формат %2\n\n"
                                 "Ожидаемый формат: %3")
                             .arg(lineNumber)
                             .arg(fieldName)
                             .arg(expectedFormat));
}

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

    loadButton_ = new QPushButton("Загрузить");
    connect(loadButton_, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    mainLayout_->addWidget(loadButton_);

    table_ = new QTableWidget();
    // 4 столбца: Фамилия, Имя, Отчество/Middle name, Дата рождения
    table_->setColumnCount(4);
    table_->setHorizontalHeaderLabels(QStringList() << "Фамилия" << "Имя" << "Отчество/Middle name" << "Дата рождения");
    table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table_->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);  // Фамилия
    table_->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);  // Имя
    table_->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);  // Отчество/Middle name
    table_->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);  // Дата рождения

    table_->setColumnWidth(0, 200);  // Фамилия
    table_->setColumnWidth(1, 200);  // Имя
    table_->setColumnWidth(2, 220);  // Отчество/Middle name
    table_->setColumnWidth(3, 120);  // Дата рождения

    connect(table_, &QTableWidget::doubleClicked, this, &MainWindow::onTableDoubleClicked);
    mainLayout_->addWidget(table_);

    setWindowTitle("Список сотрудников");
    resize(800, 450);
}

QString MainWindow::getLastNameFromPerson(Person* person_) const {
    RussianPerson* russian = dynamic_cast<RussianPerson*>(person_);
    if (russian) {
        QStringList parts = russian->getFullName().split(" ");
        return parts.size() > 0 ? parts.value(0) : "";
    }

    AmericanPerson* american = dynamic_cast<AmericanPerson*>(person_);
    if (american) {
        QStringList parts = american->getFullName().split(" ");
        return parts.size() > 2 ? parts.value(2) : "";
    }

    return "";
}

QString MainWindow::getFirstNameFromPerson(Person* person_) const {
    RussianPerson* russian = dynamic_cast<RussianPerson*>(person_);
    if (russian) {
        QStringList parts = russian->getFullName().split(" ");
        return parts.size() > 1 ? parts.value(1) : "";
    }

    AmericanPerson* american = dynamic_cast<AmericanPerson*>(person_);
    if (american) {
        QStringList parts = american->getFullName().split(" ");
        return parts.size() > 0 ? parts.value(0) : "";
    }

    return "";
}

QString MainWindow::getMiddleOrPatronymicFromPerson(Person* person_) const {
    RussianPerson* russian = dynamic_cast<RussianPerson*>(person_);
    if (russian) {
        QStringList parts = russian->getFullName().split(" ");
        return parts.size() > 2 ? parts.value(2) : "-";
    }

    AmericanPerson* american = dynamic_cast<AmericanPerson*>(person_);
    if (american) {
        QStringList parts = american->getFullName().split(" ");
        return parts.size() > 1 ? parts.value(1) : "";
    }

    return "";
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
    int errorCount_ = 0;

    while (!in_.atEnd()) {
        QString line_ = in_.readLine().trimmed();
        lineNumber_++;
        if (line_.isEmpty()) continue;

        QStringList parts_ = line_.split(",");
        if (parts_.size() < 7) {
            QMessageBox::warning(this, "Ошибка формата",
                                 QString("Строка %1: Неверный формат строки\n\n"
                                         "Ожидаемый формат: код,фамилия,имя,отчество/мидлнейм,день,месяц,год\n"
                                         "Для русских (код=1): 1,Иванов,Иван,Иванович,22,01,2001\n"
                                         "Для американцев (код=2): 2,John,Michael,Doe,10,23,1990")
                                     .arg(lineNumber_));
            errorCount_++;
            continue;
        }

        int code_ = parts_[0].toInt();
//Русский
        if (code_ == 1) {
            QString lastName_ = parts_[1].trimmed();
            QString firstName_ = parts_[2].trimmed();
            QString patronymic_ = parts_[3].trimmed();
            if (patronymic_ == "-" || patronymic_ == "—") patronymic_ = "";

            int day_ = parts_[4].toInt();
            int month_ = parts_[5].toInt();
            int year_ = parts_[6].toInt();

            // Проверка даты
            if (!Date::isValidDateStatic(day_, month_, year_)) {
                QMessageBox::warning(this, "Ошибка формата",
                                     QString("Строка %1: Неверный формат даты (Русский)\n\n"
                                             "Ожидаемый формат: дд.мм.гггг\n"
                                             "Пример: 22.01.2001\n"
                                             "День: 1-31, Месяц: 1-12, Год: 1900-2026")
                                         .arg(lineNumber_));
                errorCount_++;
                continue;
            }

            Date birthDate_(day_, month_, year_);

            // Проверка ФИО
            RussianPerson tempPerson;
            bool nameError = false;

            if (!tempPerson.setLastName(lastName_)) {
                showFormatError(this, "фамилии (Русский)", "Заглавная буква + строчные (А-Я, а-я), не пусто", lineNumber_);
                nameError = true;
            }
            else if (!tempPerson.setFirstName(firstName_)) {
                showFormatError(this, "имени (Русский)", "Заглавная буква + строчные (А-Я, а-я), не пусто", lineNumber_);
                nameError = true;
            }
            else if (patronymic_ != "" && !tempPerson.setPatronymic(patronymic_)) {
                showFormatError(this, "отчества (Русский)", "Заглавная буква + строчные (А-Я, а-я), может быть пустым или '-'", lineNumber_);
                nameError = true;
            }

            if (nameError) {
                errorCount_++;
                continue;
            }

            RussianPerson* person_ = new RussianPerson(lastName_, firstName_, patronymic_, birthDate_);
            persons_.append(person_);

            qDebug() << "Загружен русский:" << person_->getFullName()
                     << birthDate_.toString(DateFormat::Russian);
        }
//Амереканец
        else if (code_ == 2) {
            QString firstName_ = parts_[1].trimmed();
            QString middleName_ = parts_[2].trimmed();
            QString lastName_ = parts_[3].trimmed();

            int month_ = parts_[4].toInt();  // сначала месяц
            int day_ = parts_[5].toInt();    // потом день
            int year_ = parts_[6].toInt();

            // Проверка даты
            if (!Date::isValidDateStatic(day_, month_, year_)) {
                QMessageBox::warning(this, "Ошибка формата",
                                     QString("Строка %1: Неверный формат даты (Американский)\n\n"
                                             "Ожидаемый формат: мм-дд-гггг\n"
                                             "Пример: 10-23-1990 (месяц-день-год)\n"
                                             "День: 1-31, Месяц: 1-12, Год: 1900-2026")
                                         .arg(lineNumber_));
                errorCount_++;
                continue;
            }

            Date birthDate_(day_, month_, year_);

            // Проверка ФИО
            AmericanPerson tempPerson;
            bool nameError = false;

            if (!tempPerson.setFirstName(firstName_)) {
                showFormatError(this, "имени (Американский)", "Заглавная буква + строчные (A-Z, a-z), не пусто", lineNumber_);
                nameError = true;
            }
            else if (!tempPerson.setLastName(lastName_)) {
                showFormatError(this, "фамилии (Американский)", "Заглавная буква + строчные (A-Z, a-z), не пусто", lineNumber_);
                nameError = true;
            }
            else if (!tempPerson.setMiddleName(middleName_)) {
                showFormatError(this, "мидл нейм (Американский)", "Заглавная буква + строчные (A-Z, a-z), не пусто", lineNumber_);
                nameError = true;
            }

            if (nameError) {
                errorCount_++;
                continue;
            }

            AmericanPerson* person_ = new AmericanPerson(firstName_, middleName_, lastName_, birthDate_);
            persons_.append(person_);

            qDebug() << "Загружен американец:" << person_->getFullName()
                     << birthDate_.toString(DateFormat::American);
        }

        else {
            QMessageBox::warning(this, "Ошибка формата",
                                 QString("Строка %1: Неизвестный код человека\n\n"
                                         "Допустимые значения:\n"
                                         "  1 - Русский\n"
                                         "  2 - Американец\n\n"
                                         "Пример: 1,Иванов,Иван,Иванович,22,01,2001")
                                     .arg(lineNumber_));
            errorCount_++;
        }
    }

    file_.close();
    updateTable();

    QString resultMsg;
    if (errorCount_ > 0) {
        resultMsg = QString("Загружено %1 записей\nПропущено (ошибки): %2")
                        .arg(persons_.size())
                        .arg(errorCount_);
        QMessageBox::warning(this, "Загрузка завершена", resultMsg);
    } else {
        resultMsg = QString("Успешно загружено %1 записей").arg(persons_.size());
        QMessageBox::information(this, "Успех", resultMsg);
    }
}

void MainWindow::updateTable() {
    table_->setRowCount(persons_.size());

    for (int i_ = 0; i_ < persons_.size(); ++i_) {
        Person* person_ = persons_[i_];

        // Столбец 0: Фамилия
        QTableWidgetItem* lastNameItem_ = new QTableWidgetItem(getLastNameFromPerson(person_));

        // Столбец 1: Имя
        QTableWidgetItem* firstNameItem_ = new QTableWidgetItem(getFirstNameFromPerson(person_));

        // Столбец 2: Отчество/Middle name
        QTableWidgetItem* middleItem_ = new QTableWidgetItem(getMiddleOrPatronymicFromPerson(person_));

        // Столбец 3: Дата рождения
        QTableWidgetItem* dateItem_ = new QTableWidgetItem(person_->getFormattedBirthDate());

        table_->setItem(i_, 0, lastNameItem_);
        table_->setItem(i_, 1, firstNameItem_);
        table_->setItem(i_, 2, middleItem_);
        table_->setItem(i_, 3, dateItem_);
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
        QMessageBox::information(this, "Успех", "Пропуск распечатан");
    }
}

void MainWindow::clearData() {
    qDeleteAll(persons_);
    persons_.clear();

    if (table_) {
        table_->setRowCount(0);
    }
}
