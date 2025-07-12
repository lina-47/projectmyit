#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::encodeText);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::decodeText);


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

    switch (index-1) {
    case 0:
        for (char c : input)
            result.append((static_cast<unsigned char>(c) + 1) % 256);
        break;

    case 1:
        for (char c : input)
            result.append((static_cast<unsigned char>(c) + n) % 256);
        break;

    case 2:
        for (char c : input)
            result.append(static_cast<char>(26 - static_cast<unsigned char>(c) + 193));
        break;

    case 3: {
        QString repeated = key.repeated(6);
        for (int i = 0; i < input.size(); ++i) {
            int zz = repeated[i].digitValue();
            result.append((static_cast<unsigned char>(input[i]) + zz) % 256);
        }
        break;
    }
    case 4: {
        QByteArray keyBytes = ui->lineEdit->text().toLatin1();
        if (keyBytes.isEmpty()) break;

        for (int i = 0; i < input.size(); ++i) {
            unsigned char textByte = static_cast<unsigned char>(input[i]);
            unsigned char keyByte = static_cast<unsigned char>(keyBytes[i % keyBytes.size()]);
            result.append(static_cast<char>((textByte + keyByte) % 256));
        }

        ui->textEdit_2->setPlainText(QString::fromLatin1(result));
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

    switch (index - 1) {
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
    case 4: {
        QByteArray keyBytes = ui->lineEdit->text().toLatin1();
        if (keyBytes.isEmpty()) break;

        for (int i = 0; i < input.size(); ++i) {
            unsigned char textByte = static_cast<unsigned char>(input[i]);
            unsigned char keyByte = static_cast<unsigned char>(keyBytes[i % keyBytes.size()]);
            result.append(static_cast<char>((textByte - keyByte + 256) % 256));
        }

        ui->textEdit->setPlainText(QString::fromLatin1(result));
        break;
    }
    }

    ui->textEdit->setPlainText(QString::fromLatin1(result));
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 1 || index == 3) {
        ui->label_2->hide();
        ui->lineEdit->hide();
    }
    else {
        ui->label_2->show();
        ui->lineEdit->show();
    }
}

