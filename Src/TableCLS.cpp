#include "ButtonsCLS.h"
#include "TableCLS.h"
#include <boost/asio.hpp>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QDialog>
#include "ValidatorCLS.h"
#include <QLayout>
#include <iostream>
#include <ios>

TableWidget::TableWidget()
{
}

TableWidget::~TableWidget()
{
}



void TableWidget::uploadData()
{
    int rowCount = 0;
        QTextStream in(getQFile());
        while (!in.atEnd())
        {
            QString line = in.readLine();
            m_vectrData.push_back(line);
            //line.erase(std::remove(std::begin(line), std::end(line), '\r'), line.end());
            QStringList columns = line.split(" ");
            //insertRow(rowCount + 1);
            QTableWidgetItem* item1 = new QTableWidgetItem;
            item1->setText(line);
            setItem(rowCount, 0, item1);

            ++rowCount;
        }
        m_pFile->close();
}



void TableWidget::ValidateTheData()
{
    for (int i = 0; i < this->rowCount(); i++)
    {
       // QStringList columns = line.split(" ");
        QTableWidgetItem *item = new QTableWidgetItem; // Create a new item
        if (ValidatorIPAddresses::isValidIp(m_vectrData[i]))
        {
            item->setText(" --> Valid Ip");
            item->setBackground(QColor(Qt::green));
        }
        else
        {
            item->setText(" --> Invalid Ip");
            item->setBackground(QColor(Qt::red));
        }

        setItem(i, 3, item);
    }
}



void TableWidget::getCurrrentIpInfo()
{

    QDialog* psubDialog = new QDialog;
    using boost::asio::ip::tcp;
            boost::asio::io_service io_service;
            tcp::resolver resolver(io_service);
            tcp::resolver::query query(boost::asio::ip::host_name(), "");
            tcp::resolver::iterator iter = resolver.resolve(query);
            tcp::resolver::iterator end; // End marker.
            while (iter != end)
            {
                tcp::endpoint ep = *iter++;
                QLabel* addressLabel = new QLabel("Address: " + QString::fromStdString(ep.address().to_string()));
                QLabel* portLabel = new QLabel("Port: " + QString::number(ep.port()));
                QLabel* Capacity = new QLabel("Capacity: " + QString::number(ep.capacity()));
                m_pAddressLayout->addWidget(addressLabel);
                m_pAddressLayout->addWidget(portLabel);
                m_pAddressLayout->addWidget(Capacity);
                psubDialog->setLayout(m_pAddressLayout);
            }

            psubDialog->show();
}



void TableWidget::highlightRows()
{
       int rowCount = 0;
       QTextStream in(getQFile());
      //QTextStream in(m_file);
       while (!in.atEnd())
       {
           QString line = in.readLine();
           //line.erase(std::remove(std::begin(line), std::end(line), '\r'), line.end());
           QStringList columns = line.split(" ");
           QTableWidgetItem *item2 = new QTableWidgetItem(" --> Invalid Ip");
           QTableWidgetItem *item3 = new QTableWidgetItem(" --> Valid Ip");
           QTableWidgetItem* item1 = new QTableWidgetItem;
           item1->setText(line);
           setItem(rowCount, 0, item1);
           if(ValidatorIPAddresses::isValidIp(line))
           {
               item(rowCount,0)->setBackground(QColor(Qt::green));
               setItem(rowCount,1,item3);
           }
           else
           {
               item(rowCount,0)->setBackground(QColor(Qt::red));
               setItem(rowCount,1,item2);
           }
           //показывается что возможно утечка памяти но я не буду писать delete item2,item3
           ++rowCount;
       }
}


void TableWidget::addNewRow()
{
    setRowCount(rowCount() + 1);
}

void TableWidget::flushAllFromTable()
{
     clearContents();
}
