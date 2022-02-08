#include "tienda.h"
#include "ui_tienda.h"

#include <qdebug.h>

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    // Lista de productos
    cargarProductos();
    // Mostrar los productos en el combo
    foreach (Producto *p, m_productos){
        ui->inProducto->addItem(p->nombre());
    }
    // Configurar cabecera de la tabla
    QStringList cabecera = {tr("Cantidad"),tr("Producto"),tr("P. Unitario"),tr("Subtotal")};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Inicializar las variables
    m_subtotal = 0;
}

Tienda::~Tienda()
{
    delete ui;
}

/**
 * @brief Tienda::cargarProductos Cargar la lista de productos de la tienda
 */

void Tienda::cargarProductos()
{
    // Crear productos "quemados" en el codigo
    m_productos.append(new Producto(1,tr("Leche"),0.80));
    m_productos.append(new Producto(2,tr("Pan"),0.15));
    m_productos.append(new Producto(3,tr("Queso"),2.50));
    // Podria leerse de una base de datos, de un archivo o incluso de internet
}

void Tienda::calcular(float stProducto)
{
    // Calcular valores
    m_subtotal += stProducto;
    float iva = m_subtotal * IVA/100;
    float total= m_subtotal + iva;
    // Mostrar valores en GUI
    ui->outSubtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->outIVA->setText("$ " + QString::number(iva, 'f', 2));
    ui->outTotal->setText("$ " + QString::number(total, 'f', 2));
}

void Tienda::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto actual seleccionado
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio del producto en la etiqueta
    ui->outPrecio->setText("$ " + QString::number(precio, 'f',2));
    // Resetear el spin box de cantidad
    ui->inCantidad->setValue(0);
}

void Tienda::on_btnAgregar_released()
{
    // Validar que no se agregen con 0 cantidad
    int cantidad = ui -> inCantidad->value();
    if(cantidad == 0){
        return;
    }
    // Obtener los datos de la GUI
    int i = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(i);

    // Calcular el subtotal del producto
    float subTotal = p->precio() * cantidad;
    qDebug() << p->nombre() << cantidad << p->precio() << subTotal;

    // Agregar datos a la tabla
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila, 0, new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(), 'f',2)));
    ui->outDetalle->setItem(fila, 3, new QTableWidgetItem(QString::number(subTotal, 'f',2)));

    // Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    // Actualizar subtotales
    calcular(subTotal);
}

QString Tienda::resumenCompra()
{
    // Validar que no se agregen con 0 cantidad
    int cantidad = ui -> inCantidad->value();
    if(cantidad == 0){
        ;
    }
    // Obtener los datos de la GUI
    int i = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(i);

    // Calcular el subtotal del producto
    float subTotal = p->precio() * cantidad;

    QString str = "";
        str.append(tr("\t\t-  -  Detalle de la Compra  -  -\n"));
        str.append("-----------------------------------------------------------------------------------------------\n");
        str.append(tr("             |  - Cantidad -  |  - Producto -  |  - P. Unitarios -  |  - Subtotal -  |\n"));
        str.append("                      " + QString::number(cantidad) + "                   " + (p->nombre()) + "                " + QString::number(p->precio(), 'f',2) + "                   " + QString::number(subTotal, 'f',2));
        return str;
}

void Tienda::on_facturar_released()
{
    QString nombre = ui -> inNombre -> text();
    QString cedula = ui -> inCedula -> text();
    QString telefono = ui -> inTelefono -> text();
    QString email = ui -> inEmail -> text();
    if(nombre == "" || cedula == "" || email == "" || telefono == ""){
        QMessageBox::warning(this,"Advertencia", "No hay detalles de compra, ni informacion del cliente");
        return;
    }
    qDebug()<< nombre;
    // Crear un objeto de la ventana que queremos invocar
    Factura *dialogo = new Factura(this);
    dialogo->datos(ui->inCedula->text(),
                   ui->inNombre->text(),
                   ui->inTelefono->text(),
                   ui->inEmail->text(),
                   ui->inDireccion->toPlainText());
    dialogo->tota(ui->outSubtotal->text(),
                  ui->outIVA->text(),
                  ui->outTotal->text());

    dialogo->fecha();
    dialogo->exec();
}
