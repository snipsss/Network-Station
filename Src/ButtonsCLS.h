#pragma once
#include <QFile>


class TableWidget;
class QHBoxLayout;

class Buttons : public QObject
{
    Q_OBJECT
public:
    explicit Buttons(TableWidget* pTableWidget);
    QHBoxLayout* getLayout() {return m_pLayout;}
    ~Buttons();
private:
    QHBoxLayout* m_pLayout;
};
