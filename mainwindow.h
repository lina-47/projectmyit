#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void encodeText();
    void decodeText();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_inputRejected();

    void on_lineEdit_selectionChanged();

    void on_lineEdit_windowIconTextChanged(const QString &iconText);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif
