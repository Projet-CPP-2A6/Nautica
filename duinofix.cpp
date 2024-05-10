#include "duinofix.h"

Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
    arduino_uno_vendor_id = 9025;
    arduino_uno_producy_id = 67;
}

Arduino::Arduino(quint16 vendorId, quint16 productId)
    : Arduino()
{
    arduino_uno_vendor_id = vendorId;
    arduino_uno_producy_id = productId;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 115200 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

Arduino::~Arduino(){
    if(serial->isOpen()){
            serial->close();
            qDebug() << "arduino is closed";
    }
}

QByteArray Arduino::stream_from_arduino()
{
    QByteArray receivedData;
    // Keep reading until there's no more data available
    while (serial->isReadable()) { // Wait for data to be available for up to 100 milliseconds
        serial->waitForReadyRead(100);
        receivedData.append(serial->readAll());
    }
    return receivedData;
}

QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
         serial->waitForReadyRead(200);
         data=serial->readAll(); //récupérer les données reçues
    }
   return data;
}

int Arduino::write_to_arduino(QByteArray data)
{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}
