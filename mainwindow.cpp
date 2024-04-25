#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_encryptPushButton_clicked() //havent testedc****
{

    QString rsa_public = ui->rsaPublicKeyLineEdit->text();
    QString rsa_private = ui->rsaPrivateKeyLineEdit->text();
    QString aes_key_enc = ui->aesKeyLineEdit->text();
    QString plain_text = ui->plainTextEdit->toPlainText();

    setStyleSheet("QMessageBox{font-family: Source Code Pro; font-size: 12pt;}");

    // handle empty required field
    if (rsa_public.isEmpty() || rsa_private.isEmpty() || aes_key_enc.isEmpty()) {
        QMessageBox::information(this, "Error", "Keys are required for encryption", QMessageBox::Ok);
        return;
    }

    if (plain_text.isEmpty()) {
        QMessageBox::information(this, "Error", "Plain text field is empty", QMessageBox::Ok);
        return;
    }

    this->setEnabled(false); //disable user interaction

    //display a message indicating that the decryption process is ongoing
    QSplashScreen* decrypting = new QSplashScreen;
    QRect mainWindowGeometry = geometry();
    decrypting->setEnabled(false);

    QFont font = decrypting->font();
    font.setPointSize(24);
    font.setFamily("Source Code Pro");
    decrypting->setFont(font);

    decrypting->setGeometry(mainWindowGeometry); //set geometry to cover the whole screen
    decrypting->setWindowOpacity(0.4);
    decrypting->showMessage("Decrypting AES Key. This might take a while...", Qt::AlignCenter, Qt::black); //set message centered and white text

    decrypting->show();

    QCoreApplication::processEvents();


    //decrpyt aes key with rsa
    std::string aes_key_dec_hex;

    try { //try to decrypt hex
        bigint rsa_public_int(rsa_public.toStdString());
        // bigint rsa_public_int("4095509893188208770005594148806912901940254590834413582211574248986413173696675736731560807225744215275640986373996205331286759337101744549032093988305779");

        bigint rsa_private_int(rsa_private.toStdString());
        // bigint rsa_private_int("579435979162619761190367120345111303949825465176877687963471681484228319408082774616630434770887313002355665524535712929045856226063476796034002666882897");

        bigint aes_key_enc_int(aes_key_enc.toStdString());
        // bigint aes_key_enc_int("739289943379635636540771952241727919975144525839681379295854115420598172133733414608529748314222871583576855701623042812510825816063760883116243861920851");

        aes_key_dec_hex = binToHex<128>(intToBin<128>(rsaDec(aes_key_enc_int, rsa_private_int, rsa_public_int)));
        // aes_key_dec_hex = "5468617473206D79204B756E67204675";

    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return;
    } catch (...) {
        QMessageBox::information(this, "Error", "RSA Keys must be integers", QMessageBox::Ok);
        return;
    }

    //encrypt plain text with aes key
    std::string plain_text_hex = textToHex(plain_text.toLocal8Bit().toStdString());
    std::string cipher_text = encECB128(plain_text_hex, aes_key_dec_hex);

    //set cipher text to encypted plain text
    QString asciiText = QString::fromLocal8Bit(hexToText(cipher_text).c_str());
    // ui->cipherTextEdit->setPlainText(asciiText);
    ui->cipherTextEdit->setPlainText(QString::fromStdString(cipher_text));
    ui->plainTextEdit->clear();
    std::cout << textToHex(asciiText.toLocal8Bit().toStdString());

    decrypting->close();
    this->setEnabled(true);
}

void MainWindow::on_decryptPushButton_clicked()
{

    QString rsa_public = ui->rsaPublicKeyLineEdit->text();
    QString rsa_private = ui->rsaPrivateKeyLineEdit->text();
    QString aes_key_enc = ui->aesKeyLineEdit->text();
    QString cipher_text = ui->cipherTextEdit->toPlainText();

    setStyleSheet("QMessageBox{font-family: Source Code Pro; font-size: 12pt;}");

    // handle empty required field
    if (rsa_public.isEmpty() || rsa_private.isEmpty() || aes_key_enc.isEmpty()) {
        QMessageBox::information(this, "Error", "Keys are required for decryption", QMessageBox::Ok);
        return;
    }

    if (cipher_text.isEmpty()) {
        QMessageBox::information(this, "Error", "Cipher text field is empty", QMessageBox::Ok);
        return;
    }

    this->setEnabled(false); //disable user interaction

    //display a message indicating that the decryption process is ongoing
    QSplashScreen* decrypting = new QSplashScreen;
    QRect mainWindowGeometry = geometry();
    decrypting->setEnabled(false);

    QFont font = decrypting->font();
    font.setPointSize(24);
    font.setFamily("Source Code Pro");
    decrypting->setFont(font);

    decrypting->setGeometry(mainWindowGeometry); //set geometry to cover the whole screen
    decrypting->setWindowOpacity(0.4);
    decrypting->showMessage("Decrypting AES Key. This might take a while...", Qt::AlignCenter, Qt::black); //set message centered and white text

    decrypting->show();

    QCoreApplication::processEvents();


    //decrpyt aes key with rsa
    std::string aes_key_dec_hex;

    try { //try to decrypt hex
        bigint rsa_public_int(rsa_public.toStdString());
        // bigint rsa_public_int("4095509893188208770005594148806912901940254590834413582211574248986413173696675736731560807225744215275640986373996205331286759337101744549032093988305779");

        bigint rsa_private_int(rsa_private.toStdString());
        // bigint rsa_private_int("579435979162619761190367120345111303949825465176877687963471681484228319408082774616630434770887313002355665524535712929045856226063476796034002666882897");

        bigint aes_key_enc_int(aes_key_enc.toStdString());
        // bigint aes_key_enc_int("739289943379635636540771952241727919975144525839681379295854115420598172133733414608529748314222871583576855701623042812510825816063760883116243861920851");

        aes_key_dec_hex = binToHex<128>(intToBin<128>(rsaDec(aes_key_enc_int, rsa_private_int, rsa_public_int)));
        // aes_key_dec_hex = "5468617473206D79204B756E67204675";

    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return;
    } catch (...) {
        QMessageBox::information(this, "Error", "RSA Keys must be integers", QMessageBox::Ok);
        return;
    }

    //decrypt cipher text with aes key
    std::string cipher_text_hex = textToHex(cipher_text.toLocal8Bit().toStdString());
    std::string plain_text = decECB128(cipher_text.toStdString(), aes_key_dec_hex);

    std::cout << plain_text << std::endl;
    //set cipher text to encypted plain text
    QString asciiText = QString::fromLocal8Bit(hexToText(plain_text).c_str());
    std::cout << textToHex(asciiText.toLocal8Bit().toStdString()) << std::endl;

    ui->plainTextEdit->setPlainText(QString::fromStdString(hexToText(plain_text)));
    ui->cipherTextEdit->clear();
    decrypting->close();
    this->setEnabled(true);
}
