#ifndef FACTURA_H
#define FACTURA_H

#include <QDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

#include <tienda.h>

namespace Ui {
class Factura;
}

class Factura : public QDialog
{
    Q_OBJECT

public:
    explicit Factura(QWidget *parent = nullptr);
    ~Factura();

    QString currentDateTime();
    void fecha();
    void guardar();

    void datos(QString nombre, QString cedula, QString telefono, QString email, QString direccion);
    void tota(QString subtotal, QString iva, QString total);
    QString infoCliente();
    QString resumenCompra();

    const QString &cedula() const;
    void setCedula(const QString &newCedula);
    const QString &nombre() const;
    void setNombre(const QString &newNombre);
    const QString &telefono() const;
    void setTelefono(const QString &newTelefono);
    const QString &email() const;
    void setEmail(const QString &newEmail);
    const QString &direccion() const;
    void setDireccion(const QString &newDireccion);

    const QString &iva() const;
    void setIva(const QString &newIva);
    const QString &total() const;
    void setTotal(const QString &newTotal);

    const QString &subtotal() const;
    void setSubtotal(const QString &newSubtotal);

private slots:
    void on_Imprimir_clicked();

    void on_Cerrar_clicked();

private:
    Ui::Factura *ui;

    QString m_cedula;
    QString m_nombre;
    QString m_telefono;
    QString m_email;
    QString m_direccion;

    QString m_subtotal, m_iva, m_total;
};

#endif // FACTURA_H
