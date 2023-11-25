#include "ServerWidget.h"
#include "ButtonsServerCLS.h"
#include "TableCLS.h"
#include "ButtonsCLS.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTextStream>
#include <QScrollBar>
#include <QScrollArea>
#include "threadserver.h"
#include "ServerRunnerCLS.h"

int LineCounter(QFile* file)
{
    QTextStream in(file);
    int lineCount = 0;
    while (!in.atEnd())
    {
        in.readLine();
        lineCount++;
    }
    file->close();
    return lineCount;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget* pQWdidget = new QWidget;
    pQWdidget->setWindowTitle("Network station");
    TableWidget*  pTableWidget = new TableWidget;
    //pQWdidget->setStyleSheet("/home/valeriikupriianov/Downloads/USGOV.jpg");
    QGridLayout* pGridLayout = new QGridLayout;
    //QGridLayout* pServerLayout = new QGridLayout;
    QFile* m_file = new QFile("/home/valeriikupriianov/IWantToDie/Src/iplist.txt");
    m_file->open(QIODevice::ReadOnly | QIODevice::Text);
    //uploadData(pTableWidget,m_file);
    QHBoxLayout* phboxLayout = new QHBoxLayout;
    QVector<QString> vecData;
    pTableWidget->setVectorIpData(vecData);
    pTableWidget->setQFile(m_file);
    pTableWidget->SetQHboxLayout(phboxLayout);

    QScrollArea* pScrollBar = new QScrollArea(pQWdidget);
    pScrollBar->setWidget(pTableWidget);
    pScrollBar->setWidgetResizable(true);
    //pScrollBar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    pScrollBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    pGridLayout->addWidget(pScrollBar,0,Qt::AlignLeft);

    //int  rowCount = static_cast<int>(LineCounter(m_file));
    pTableWidget->setRowCount(92);
    pTableWidget->setColumnCount(2);
    pTableWidget->setColumnWidth(0,200);
    pTableWidget->setColumnWidth(1,200);
    pTableWidget->setHorizontalHeaderLabels({"Address","Status"});


    //ThreadServer* thread = new ThreadServer;
    //thread->start(QThread::HighPriority);
    QTextEdit* ptextEdit = new QTextEdit;





    //pServerInitOject->quitServerSession(prunnerObject);
    //pServerInitOject->start();
    //ThreadServer thread;
    //thread.start();
    QThread* pServerThread = new QThread;
    Socket* p_socketObject = new Socket;
    RunnerSRV* prunnerObject = new RunnerSRV(p_socketObject,pServerThread);
    prunnerObject->setQTextEdit(ptextEdit);
    prunnerObject->getTextEdt()->setFixedSize(420,420);
    prunnerObject->show();
    pGridLayout->addWidget(prunnerObject->getTextEdt(),0,1);
    ServerInit* pServerInitOject = new ServerInit(prunnerObject);
    ServerButtons* pServerButtons = new ServerButtons(pServerInitOject);
    pServerInitOject->moveToThread(pServerThread);
    Buttons* pButtons = new Buttons(pTableWidget);
    pServerThread->start();
    //pServerThread->quit();

    pGridLayout->addLayout(pServerButtons->getLayout(),2,1);
    pGridLayout->addLayout(pButtons->getLayout(), 1, 0);
    //rRunnerSRV* pServerRunner = new RunnerSRV;
    //pServerRunner->setMainWidget(pQWdidget);
   // pQWdidget->setLayout(pServerRunner->getQHboxLayout());
   // pGridLayout->addWidget(pScrollBar);
    pGridLayout->addWidget(pTableWidget,0,0);
    pQWdidget->setLayout(pGridLayout);
   // pQWdidget->setLayout(pServerRunner->getQHboxLayout());
   // pQWdidget->setLayout(pServerLayout);
    //RunServer();

    pQWdidget->setFixedSize(1000,500);
    pQWdidget->show();


    return a.exec();
}
