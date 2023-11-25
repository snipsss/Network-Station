#pragma once
#include <QTableWidget>
#include <QFile>
#include <QHBoxLayout>

class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableWidget();
    ~TableWidget();
    void setQFile(QFile* file) {m_pFile = file;}
    QFile* getQFile(){return m_pFile;}
    void setVectorIpData(QVector<QString> vecData){m_vectrData = vecData;}

    void SetQHboxLayout(QHBoxLayout* layout){m_pAddressLayout = layout;}
    QHBoxLayout* getHboxLayout() {return m_pAddressLayout;}
    int getCountRow();
private:
    QFile* m_pFile;
    QVector<QString> m_vectrData;
    QHBoxLayout* m_pAddressLayout;

private slots:
    void ValidateTheData();
    void getCurrrentIpInfo();   
    void uploadData();
   // void saveFileChanging();
    void addNewRow();
    void highlightRows();
    void flushAllFromTable();

   //rrrrr void ableUnAbleHighlightRows();
};
