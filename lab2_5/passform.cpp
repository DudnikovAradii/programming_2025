#include "passform.h"
#include "person.h"
#include <QDir>
#include <QRandomGenerator>

PassForm::PassForm(Person* person_, QWidget* parent_)
    : QDialog(parent_), person_(person_) {
    setupUI();
    setupImage();

    setWindowTitle("Пропуск");
    setMinimumSize(400, 500);
    setModal(true);
}

PassForm::~PassForm() {}

void PassForm::setupUI() {
    QVBoxLayout* mainLayout_ = new QVBoxLayout(this);

    // Заголовок
    QLabel* titleLabel_ = new QLabel("ПРОПУСК");
    titleLabel_->setAlignment(Qt::AlignCenter);
    QFont titleFont_ = titleLabel_->font();
    titleFont_.setPointSize(16);
    titleFont_.setBold(true);
    titleLabel_->setFont(titleFont_);
    mainLayout_->addWidget(titleLabel_);

    mainLayout_->addWidget(new QLabel("----------------------------------------"));

    // Информация о человеке
    nameLabel_ = new QLabel("ФИО: " + person_->getFullName());
    nameLabel_->setAlignment(Qt::AlignCenter);
    QFont nameFont_ = nameLabel_->font();
    nameFont_.setPointSize(12);
    nameLabel_->setFont(nameFont_);
    mainLayout_->addWidget(nameLabel_);

    birthLabel_ = new QLabel("Дата рождения: " + person_->getFormattedBirthDate());
    birthLabel_->setAlignment(Qt::AlignCenter);
    birthLabel_->setFont(nameFont_);
    mainLayout_->addWidget(birthLabel_);

    mainLayout_->addWidget(new QLabel("----------------------------------------"));

    // Изображение
    imageLabel_ = new QLabel();
    imageLabel_->setAlignment(Qt::AlignCenter);
    imageLabel_->setMinimumSize(200, 200);
    imageLabel_->setStyleSheet("border: 1px solid gray; background-color: white;");
    mainLayout_->addWidget(imageLabel_);

    mainLayout_->addStretch();

    // Кнопки
    QHBoxLayout* buttonLayout_ = new QHBoxLayout();
    cancelButton_ = new QPushButton("Отмена");
    printButton_ = new QPushButton("Печать");

    connect(cancelButton_, &QPushButton::clicked, this, &PassForm::onCancel);
    connect(printButton_, &QPushButton::clicked, this, &PassForm::onPrint);

    buttonLayout_->addStretch();
    buttonLayout_->addWidget(cancelButton_);
    buttonLayout_->addWidget(printButton_);
    buttonLayout_->addStretch();

    mainLayout_->addLayout(buttonLayout_);
}

void PassForm::setupImage() {
    QPixmap pixmap_;

    switch(IMAGE_MODE_) {
    case 1: // Статичная картинка
        pixmap_.load(":/images/default.jpg");
        if (pixmap_.isNull()) {
            pixmap_ = QPixmap(200, 200);
            pixmap_.fill(Qt::lightGray);
            QPainter painter_(&pixmap_);
            painter_.drawText(pixmap_.rect(), Qt::AlignCenter, "No Image");
        }
        break;

    case 2: // Рандомная из папки img_res
    {
        QDir dir_("img_res");
        if (!dir_.exists()) {
            // Создаем папку если её нет
            dir_.mkpath(".");
        }

        QStringList filters_;
        filters_ << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
        QStringList files_ = dir_.entryList(filters_);

        if (!files_.isEmpty()) {
            int randomIndex_ = QRandomGenerator::global()->bounded(files_.size());
            QString imagePath_ = dir_.filePath(files_[randomIndex_]);
            pixmap_.load(imagePath_);
            qDebug() << "Загружено изображение:" << imagePath_;
        }

        if (pixmap_.isNull()) {
            pixmap_ = QPixmap(200, 200);
            pixmap_.fill(Qt::lightGray);
            QPainter painter_(&pixmap_);
            painter_.drawText(pixmap_.rect(), Qt::AlignCenter, "No Images in img_res");
        }
        break;
    }

    case 3: // Уникальная для каждого
    {
        QString imageName_ = person_->getFullName().simplified();
        imageName_.replace(" ", "_");
        imageName_.replace(QRegularExpression("[^a-zA-Z0-9_а-яА-Я]"), "");
        imageName_ = imageName_.toLower();

        QFile file_("img_res/" + imageName_ + ".jpg");
        if (file_.exists()) {
            pixmap_.load("img_res/" + imageName_ + ".jpg");
        } else {
            // Пробуем другие расширения
            QStringList extensions = {".png", ".jpeg", ".bmp"};
            bool found = false;
            for (const QString& ext : extensions) {
                if (QFile::exists("img_res/" + imageName_ + ext)) {
                    pixmap_.load("img_res/" + imageName_ + ext);
                    found = true;
                    break;
                }
            }

            if (!found) {
                pixmap_ = QPixmap(200, 200);
                pixmap_.fill(Qt::lightGray);
                QPainter painter_(&pixmap_);
                painter_.drawText(pixmap_.rect(), Qt::AlignCenter, "No unique image");
            }
        }
        break;
    }
    }

    if (!pixmap_.isNull()) {
        imageLabel_->setPixmap(pixmap_.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void PassForm::onCancel() {
    close();
}

void PassForm::onPrint() {
    emit personDeleted(person_);
    close();
}
