#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::encodeText);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::decodeText);

    // Заполняем comboBox, если он пустой
    if (ui->comboBox->count() == 0) {
        ui->comboBox->addItems(QStringList() << "Shift +1" << "Shift by N" << "Invert" << "Custom Shift");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::encodeText() {
    QByteArray input = ui->textEdit->toPlainText().toLatin1();
    QByteArray result;
    QString key = ui->lineEdit->text();
    int n = key.toInt();
    int index = ui->comboBox->currentIndex();

    switch (index) {
    case 0: // Shift +1
        for (char c : input)
            result.append((static_cast<unsigned char>(c) + 1) % 256);
        break;

    case 1: // Shift by N
        for (char c : input)
            result.append((static_cast<unsigned char>(c) + n) % 256);
        break;

    case 2: // Invert
        for (char c : input)
            result.append(static_cast<char>(26 - static_cast<unsigned char>(c) + 193));
        break;

    case 3: { // Custom Shift
        QString repeated = key.repeated(6);
        for (int i = 0; i < input.size(); ++i) {
            int zz = repeated[i].digitValue();
            result.append((static_cast<unsigned char>(input[i]) + zz) % 256);
        }
        break;
    }
    }

    ui->textEdit_2->setPlainText(QString::fromLatin1(result));
}

void MainWindow::decodeText() {
    QByteArray input = ui->textEdit_2->toPlainText().toLatin1();
    QByteArray result;
    QString key = ui->lineEdit->text();
    int n = key.toInt();
    int index = ui->comboBox->currentIndex();

    switch (index) {
    case 0:
        for (char c : input)
            result.append((static_cast<unsigned char>(c) - 1 + 256) % 256);
        break;

    case 1:
        for (char c : input)
            result.append((static_cast<unsigned char>(c) - n + 256) % 256);
        break;

    case 2:
        for (char c : input)
            result.append(static_cast<char>(26 - static_cast<unsigned char>(c) + 193));
        break;

    case 3: {
        QString repeated = key.repeated(6);
        for (int i = 0; i < input.size(); ++i) {
            int zz = repeated[i].digitValue();
            result.append((static_cast<unsigned char>(input[i]) - zz + 256) % 256);
        }
        break;
    }
    }

    ui->textEdit->setPlainText(QString::fromLatin1(result));
}
