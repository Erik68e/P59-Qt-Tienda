#include "factura.h"
#include "ui_factura.h"

#include <set>

Factura::Factura(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Factura)
{
    ui->setupUi(this);
}

Factura::~Factura()
{
    delete ui;
}

const QString &Factura::cedula() const
{
    return m_cedula;
}

void Factura::setCedula(const QString &newCedula)
{
    m_cedula = newCedula;
}

const QString &Factura::nombre() const
{
    return m_nombre;
}

void Factura::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

const QString &Factura::telefono() const
{
    return m_telefono;
}

void Factura::setTelefono(const QString &newTelefono)
{
    m_telefono = newTelefono;
}

const QString &Factura::email() const
{
    return m_email;
}

void Factura::setEmail(const QString &newEmail)
{
    m_email = newEmail;
}

const QString &Factura::direccion() const
{
    return m_direccion;
}

void Factura::setDireccion(const QString &newDireccion)
{
    m_direccion = newDireccion;
}

const QString &Factura::subtotal() const
{
    return m_subtotal;
}

void Factura::setSubtotal(const QString &newSubtotal)
{
    m_subtotal = newSubtotal;
}

const QString &Factura::iva() const
{
    return m_iva;
}

void Factura::setIva(const QString &newIva)
{
    m_iva = newIva;
}

const QString &Factura::total() const
{
    return m_total;
}

void Factura::setTotal(const QString &newTotal)
{
    m_total = newTotal;
}

QString Factura::currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80]; tstruct = *localtime(&now);

    strftime(buf, sizeof (buf), "%Y-%m-%d | %X", &tstruct);

    return buf;
}


void Factura::datos(QString nombre, QString cedula, QString telefono, QString email, QString direccion)
{
    setNombre(nombre);
    setCedula(cedula);
    setTelefono(telefono);
    setEmail(email);
    setDireccion(direccion);
}

void Factura::tota(QString subtotal, QString iva, QString total)
{
    setSubtotal(subtotal);
    setIva(iva);
    setTotal(total);
}

QString Factura::infoCliente()
{
    datos(m_nombre,m_cedula,telefono(),email(),direccion());
    QString str = "";
    str.append("      -  -  Informacion del Cliente  -  -\n");
    str.append("----------------------------------------------\n");
    str.append("* Cedula:    " + m_cedula);
    str.append("\n* Nombre:    " + m_nombre);
    str.append("\n* Telefono:  " + m_telefono);
    str.append("\n* E-mail:     " + m_email);
    str.append("\n* Direccion:  " + m_direccion);
    return str;
}

void Factura::fecha()
{
    ui->outFecha->setText(currentDateTime());
    ui->outSubTotal->setText(subtotal());
    ui->outIva->setText(m_iva);
    ui->outTotal->setText(m_total);
    Tienda objTienda;
    ui->outCliente->appendPlainText(infoCliente());
    ui->outResumenCompra->appendPlainText(objTienda.resumenCompra());

}

void Factura::guardar()
{
    // Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar datos",
                                                         QDir::home().absolutePath(),
                                                         "Archivo de salarios (*.slr)");
    qDebug() << nombreArchivo;
    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un stream de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << " Fecha: ";
        salida << ui->outFecha->text();
        salida << "\n" << endl;
        salida << ui->outCliente->toPlainText();
        salida << "\n" << endl;
        salida << ui->outResumenCompra->toPlainText();
        salida << "\n - - Totales - - " << endl;
        salida << " * SubTotal: ";
        salida << ui->outSubTotal->text();
        salida << "\n * Iva(12%): ";
        salida << ui->outIva->text();
        salida << "\n * Total: ";
        salida << ui->outTotal->text();

    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar los datos");
    }
    //Cerrar archivo
    archivo.close();
}

void Factura::on_Imprimir_clicked()
{
    guardar();
}

void Factura::on_Cerrar_clicked()
{
    close();
}
