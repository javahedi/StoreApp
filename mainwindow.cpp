#include "mainwindow.h"
#include "./ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



/////////////////////
// Helper Functions
////////////////////

QString MainWindow::formatTotal(double total) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << total;
    return QString::fromStdString(oss.str() + "$");
}


void MainWindow::addItem(const QString& name, double price, int& counter, QLabel* label){
    vList.push_back(itemprice(name, price));
    counter++;
    label->setText(QString::number(counter));
}
//////////////////////
///  Navigate buttons
//////////////////////

void MainWindow::on_pushButtonViewCart_clicked()
{
    // Set the current index of the stacked widget to the cart view page
    ui->stackedWidget->setCurrentIndex(1);

    // Clear the list widget before adding new items
    ui->listWidgetofItem->clear();

    total = 0.0; // Reset total before calculating
    for (const auto &v : vList) {
        QString itemText = QString("%1\t%2 $").arg(v.Name).arg(v.Price, 0, 'f', 2);
        ui->listWidgetofItem->addItem(itemText);
        total +=v.Price;
    }

    ui->labelTotalPriceInCard->setText(formatTotal(total));

}


void MainWindow::on_pushButtonBackShopPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButtonPay_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->labelTotalPrice->setText(formatTotal(total));
}


void MainWindow::on_pushButtonConfirm_clicked()
{
    //Get the text from QTextEdit
    QString name = ui->textEditName->toPlainText().trimmed();
    QString card = ui->textEditCarNum->toPlainText().trimmed();

    if(name.isEmpty() || card.isEmpty()){
        QMessageBox::warning(this, "Invalid Input", "Please enter your name.");
        return;
    }

    //Create a receiptInfo object and
    receiptInfo receipt(receiptCounter++, name, card);
    ui->textEditShow->setPlainText(receipt.toString());

    qDebug() << "Receipt Info:" << receipt.toString();


    // Optionally, save the receipt to a file
    if (receipt.saveToFile("receipt.txt")) {
        QMessageBox::information(this, "Success", "Receipt saved to file.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save receipt to file.");
    }

    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButtonNewShop_clicked()
{
    // Reset all member variables
    total = 0.0;
    cock = 0;
    sprit = 0;
    fanta = 0;
    pepsi = 0;

    // Clear the item list
    vList.clear();

    // Update the UI to reflect the reset state
    ui->labelNumCock->setText("0");
    ui->labelNumPepsi->setText("0");
    ui->labelNumSprit->setText("0");
    ui->labelNumFanta->setText("0");
    ui->labelTotalPriceInCard->setText("0.00$");
    ui->labelTotalPrice->setText("0.00$");
    ui->listWidgetofItem->clear();
    ui->textEditName->clear();
    ui->textEditCarNum->clear();

    // Navigate back to the shop page
    ui->stackedWidget->setCurrentIndex(0);
}


//////////////////////
///  Add buttons
//////////////////////
void MainWindow::on_pushButtonCock_clicked()
{
    //itemprice ip;
    //ip.Name = "Cock";
    //ip.Price = 2.2;
    //vList.push_back(ip);
    //cock+=1;
    //ui->labelNumCock->setText(QString::number(cock));
    addItem("Cock",2.2,cock,ui->labelNumCock);
}


void MainWindow::on_pushButtonPepsi_clicked()
{
    //itemprice ip;
    //ip.Name = "Pepsi";
    //ip.Price = 2.15;
    //vList.push_back(ip);
    //pepsi+=1;
    //ui->labelNumPepsi->setText(QString::number(pepsi));

    addItem("Pepsi",2.15,pepsi,ui->labelNumPepsi);
}


void MainWindow::on_pushButtonSprit_clicked()
{
    //itemprice ip;
    //ip.Name = "Sprit";
    //ip.Price = 2.1;
    //vList.push_back(ip);
    //sprit+=1;
    //ui->labelNumSprit->setText(QString::number(sprit));
    addItem("Sprit",2.1,sprit,ui->labelNumSprit);
}




void MainWindow::on_pushButtonFanta_clicked()
{
    //itemprice ip;
    //ip.Name = "Fanta";
    //ip.Price = 2.12;
    //vList.push_back(ip);
    //fanta+=1;
    //ui->labelNumFanta->setText(QString::number(fanta));
    addItem("Fanta",2.12,fanta,ui->labelNumFanta);
}




