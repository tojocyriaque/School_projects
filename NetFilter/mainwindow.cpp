#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTableView *view = new QTableView;

    setupChainFrame();
    setupPolicyFrame();
    setupProtocolFrame();
    setupInterfacesFrame();

    showRules();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupChainFrame(){
    ui->chainComboBox->addItem("INPUT");
    ui->chainComboBox->addItem("OUTPUT");
    ui->chainComboBox->addItem("FORWARD");
}

void MainWindow::setupPolicyFrame(){
    ui->policyComboBox->addItem("ACCEPT");
    ui->policyComboBox->addItem("DROP");
    ui->policyComboBox->addItem("REJECT");
}

void MainWindow::setupProtocolFrame(){
    ui->protocolComboBox->addItem("tcp");
    ui->protocolComboBox->addItem("udp");
    ui->protocolComboBox->addItem("icmp");
    ui->protocolComboBox->addItem("all");
}

void MainWindow::setupInterfacesFrame(){
    QProcess *findInterfaces = new QProcess;
    findInterfaces->start(QString("/bin/sh"), QStringList() << "-c" << "ifconfig");
    findInterfaces->waitForFinished();
    QByteArray byte_results = findInterfaces->readAllStandardOutput();
    QStringList results = QString::fromUtf8(byte_results).trimmed().split("\n\n");
    for(QString result: results){
        QString interface = result.split(": ")[0];
        if(interface!="lo"){
            ui->sourceInterfaceComboBox->addItem(interface);
            ui->destinationInterfaceComboBox->addItem(interface);
        }
    }
}

QFrame* MainWindow::ruleFrame(QString rule, int num){
    QWidget* widget = new QWidget;
    QHBoxLayout *hl = new QHBoxLayout(widget);
    QFrame *rule_Frame = new QFrame;
    rule_Frame->setLayout(hl);

    QLineEdit *ruleLineEdit = new QLineEdit;
    ruleLineEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    ruleLineEdit->setText(rule);

    QPushButton *detailsBtn = new QPushButton;
    detailsBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    detailsBtn->setStyleSheet("background-color: rgb(98, 160, 234);");
    detailsBtn->setText("details");
    connect(detailsBtn, &QPushButton::clicked,[=]{showRuleDetails(rule);});

    QPushButton *removeBtn = new QPushButton;
    removeBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    removeBtn->setStyleSheet("background-color: rgb(237, 51, 59);");
    removeBtn->setText("remove");
    connect(removeBtn, &QPushButton::clicked,[=]{removeRule(rule, num);});

    hl->addWidget(ruleLineEdit);
    hl->addWidget(detailsBtn);
    hl->addWidget(removeBtn);

    return rule_Frame;
}

void MainWindow::showRules(){
    int ruleNum = 0;
    QProcess *rules_process = new QProcess;
    rules_process->start(QString("/bin/sh"), QStringList() << "-c" << "sudo iptables -L");
    rules_process->waitForFinished();
    QByteArray bt = rules_process->readAllStandardOutput();
    QStringList rules = QString::fromUtf8(bt).trimmed().split("\n");
    std::string chain = "";
    std::vector<std::string> chains = {"INPUT", "FORWARD", "OUTPUT"};
    std::vector<QString> policies = {"ACCEPT", "DROP", "REJECT"};
    int chain_index = -1;

    QWidget *w = new QWidget;
    QVBoxLayout *vl = new QVBoxLayout(w);
    ui->rulesScrollArea->setWidget(w);
    for(QString s: rules){
        if(s.contains(QRegularExpression("^Chain"))){
            ruleNum = 0;
            chain_index = chain_index+1;
            chain = chains.at(chain_index);
            for(QString policy: policies){
                if(s.contains(QRegularExpression(policy))){
                    defaultPolicies[chain_index] = policy;
                    break;
                }
            }
        }
        else if(!s.contains(QRegularExpression("^target")) && s.size()>1){
            ruleNum++;
            vl->addWidget(ruleFrame(QString::fromStdString(chain+" ")+s, ruleNum));
        }
    }
}

void MainWindow::showRuleDetails(QString rule){
    QStringList rules = rule.split(" ");
    QMainWindow *detailsWindow = new QMainWindow();
    detailsWindow->setWindowModality(Qt::WindowModal);
    detailsWindow->show();
}

void MainWindow::addNewRule(){
    QProcess *add = new QProcess;
    QString chain = ui->chainComboBox->currentText();
    QString protocol = ui->protocolComboBox->currentText();
    QStringList destPorts = ui->destinationPortsLineEdit->text().split(";");
    QStringList srcPorts = ui->sourcePortsLineEdit->text().split(";");
    QString policy = ui->policyComboBox->currentIndex();
    QString mac = ui->macAddrLineEdit->text();
    QString srcAddr = ui->sourceAddrLineEdit->tex();
    QString destAddr = ui->destinationAddrLineEdit->text();
    QString srcIface = ui->sourceInterfaceComboBox->currentText();
    QString destIface = ui->destinationInterfaceComboBox->currentText();
}

void MainWindow::removeRule(QString rule, int num){
    QString command = QString("sudo iptables -D ") + rule.split(" ")[0] + QString::fromStdString(" "+std::to_string(num));
    QProcess *remove_process = new QProcess;
    remove_process->execute(QString("/bin/sh"), QStringList() << "-c" << command);
    remove_process->close();
    showRules();
}

void MainWindow::showDefaultPolicy(){
    QMainWindow *defaultPolicyWindow = new QMainWindow;
    QFrame *policiesFrame = new QFrame;
    QVBoxLayout *defaultPoliciesLayout = new QVBoxLayout;
    policiesFrame->setLayout(defaultPoliciesLayout);

    QLabel *inputLabel = new QLabel;
    inputLabel->setText("INPUT");
    QComboBox *inputComboBox = new QComboBox;
    for(auto policy: std::vector<QString>{"ACCEPT","DROP","REJECT"}){
        inputComboBox->addItem(policy);
    }
    inputComboBox->setCurrentText(defaultPolicies[0]);
    defaultPoliciesLayout->addWidget(inputLabel);
    defaultPoliciesLayout->addWidget(inputComboBox);

    QLabel *forwardLabel = new QLabel;
    forwardLabel->setText("FORWARD");
    QComboBox *forwardComboBox = new QComboBox;
    for(auto policy: std::vector<QString>{"ACCEPT","DROP","REJECT"}){
        forwardComboBox->addItem(policy);
    }
    forwardComboBox->setCurrentText(defaultPolicies[1]);
    defaultPoliciesLayout->addWidget(forwardLabel);
    defaultPoliciesLayout->addWidget(forwardComboBox);

    QLabel *outputLabel = new QLabel;
    outputLabel->setText("OUTPUT");
    QComboBox * outputComboBox = new QComboBox;
    for(auto policy: std::vector<QString>{"ACCEPT","DROP","REJECT"}){
        outputComboBox->addItem(policy);
    }
    outputComboBox->setCurrentText(defaultPolicies[0]);
    defaultPoliciesLayout->addWidget(outputLabel);
    defaultPoliciesLayout->addWidget(outputComboBox);

    QPushButton *changeButton = new QPushButton;
    changeButton->setText("change");
    connect(changeButton, &QPushButton::clicked, [=]{MainWindow::changeDefaultPolicy(inputComboBox, forwardComboBox, outputComboBox);});
    defaultPoliciesLayout->addWidget(changeButton);

    defaultPolicyWindow->setWindowModality(Qt::WindowModal);
    defaultPolicyWindow->setCentralWidget(policiesFrame);
    defaultPolicyWindow->show();
}

void MainWindow::changeDefaultPolicy(QComboBox *input, QComboBox *forward, QComboBox *output){
    defaultPolicies[0] = input->currentText();
    defaultPolicies[1] = forward->currentText();
    defaultPolicies[2] = output->currentText();
    QProcess *change_process = new QProcess;
    change_process->start(QString("/bin/sh"), QStringList() << "-c" << "sudo iptables -P INPUT " + defaultPolicies[0]);
    change_process->waitForFinished();
    change_process->execute(QString("/bin/sh"), QStringList() << "-c" << "sudo iptables -P INPUT " + defaultPolicies[0]);
    change_process->waitForFinished();

    change_process->start(QString("/bin/sh"), QStringList() << "-c" << "sudo iptables -P FORWARD " + defaultPolicies[1]);
    change_process->waitForFinished();
    change_process->execute(QString("/bin/sh"), QStringList() << "-c" << "sudo iptables -P FORWARD " + defaultPolicies[1]);
    change_process->waitForFinished();

    change_process->start(QString("/bin/sh"), QStringList() << "-c" << "sudo iptables -P OUTPUT " + defaultPolicies[2]);
    change_process->waitForFinished();
    change_process->execute(QString("/bin/sh"), QStringList() << "-c" << "sudo iptables -P OUTPUT " + defaultPolicies[2]);
    change_process->waitForFinished();
}

void MainWindow::on_addButton_clicked()
{
    addNewRule();
}

void MainWindow::on_defaultButton_clicked()
{
    showDefaultPolicy();
}

void MainWindow::on_clearButton_clicked()
{
    QProcess *clear_process = new QProcess;
    clear_process->start(QString("/bin/sh"), QStringList() << "-c" << "sudo iptables -F");
    clear_process->waitForFinished();
    showRules();
}

void MainWindow::on_updateButton_clicked()
{
    showRules();
}
