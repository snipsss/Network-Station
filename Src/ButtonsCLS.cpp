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

Buttons::Buttons(TableWidget* pTableWidget) : m_pLayout(new QHBoxLayout)
{
    QPushButton* pButtonAddNewRow = new QPushButton("Add new row");
    QPushButton* pButtonhightLigh = new QPushButton("Validate Data");
    QPushButton* pButtonFlush = new QPushButton("Flush all from Table");
    QPushButton* pButtonGetInfo = new QPushButton("Get Ip Info");
    QPushButton* pButtonUploadData = new QPushButton("Upload Data");
   // QPushButton* pButton = new QPushButton("");
    //QPushButton* pButton = new QPushButton("this dont't work");
    m_pLayout->addWidget(pButtonUploadData);

    m_pLayout->addWidget(pButtonAddNewRow);
    m_pLayout->addWidget(pButtonhightLigh);
    m_pLayout->addWidget(pButtonFlush);
    m_pLayout->addWidget(pButtonGetInfo);

    connect(pButtonUploadData, SIGNAL(clicked()), pTableWidget, SLOT(uploadData()));
    connect(pButtonAddNewRow, SIGNAL(clicked()), pTableWidget, SLOT(addNewRow()));
     connect(pButtonhightLigh, SIGNAL(clicked()), pTableWidget, SLOT(ValidateTheData()));
      connect(pButtonGetInfo, SIGNAL(clicked()), pTableWidget, SLOT(getCurrrentIpInfo()));
       connect(pButtonFlush, SIGNAL(clicked()), pTableWidget, SLOT(flushAllFromTable()));

}





Buttons::~Buttons()
{
    delete m_pLayout;
}
