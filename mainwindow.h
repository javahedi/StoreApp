#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QList>
#include <QMap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <sstream> // Add this line


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


////////////////
// Struct to store item information
struct itemprice {
    QString Name; // Use QString for better Qt integration
    double Price;

    itemprice() : Name(""), Price(0.0) {}
    itemprice(const QString& name, double price) : Name(name), Price(price) {}
};

// Struct to store receipt information
struct receiptInfo {
    int receiptNumber;
    QString customerName;
    QString cardNumber;

    receiptInfo() : receiptNumber(0), customerName(""), cardNumber("") {}
    receiptInfo(int number, const QString& name, const QString& card)
        : receiptNumber(number), customerName(name), cardNumber(card) {}

    QString toString() const {
        return QString("Receipt Number: %1\nCustomer Name: %2\nCard Number: %3")
        .arg(receiptNumber)
            .arg(customerName)
            .arg(cardNumber);
    }

    bool saveToFile(const QString& filePath) const {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for writing:" << file.errorString();
            return false;
        }

        QTextStream out(&file);
        out << toString();
        file.close();
        return true;
    }
};





//////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonViewCart_clicked();
    void on_pushButtonBackShopPage_clicked();
    void on_pushButtonPay_clicked();
    void on_pushButtonConfirm_clicked();
    void on_pushButtonNewShop_clicked();
    void on_pushButtonCock_clicked();
    void on_pushButtonPepsi_clicked();
    void on_pushButtonSprit_clicked();
    void on_pushButtonFanta_clicked();

private:
    Ui::MainWindow *ui;

    // Member variables
    double total = 0.0;
    int cock = 0;
    int sprit = 0;
    int fanta = 0;
    int pepsi = 0;
    int receiptCounter = 0;

    std::vector<itemprice> vList; // List of items in the cart
    QMap<QString, double> itemMap; // Map of item names to prices

    // Helper functions
    QString formatTotal(double total) const;
    void addItem(const QString& name, double price, int& counter, QLabel* label);

};
#endif // MAINWINDOW_H
