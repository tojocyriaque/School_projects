#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupChainFrame();
    void setupPolicyFrame();
    void setupProtocolFrame();
    void setupInterfacesFrame();

    QFrame *ruleFrame(QString rule, int num);
    void showRules();
    void showRuleDetails(QString rule);
    void removeRule(QString rule, int num);

    void showDefaultPolicy();
    void changeDefaultPolicy(QComboBox* input, QComboBox *forward, QComboBox *output);

    void addNewRule();

private slots:
    void on_addButton_clicked();

    void on_defaultButton_clicked();

    void on_clearButton_clicked();

    void on_updateButton_clicked();

private:
    QString defaultPolicies[3];
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
