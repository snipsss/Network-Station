#include <QHBoxLayout>
#include "MainServerRun.h"
#include <QObject>
#include <QPushButton>
#include "ServerWidget.h"

class ServerInit;
class QHBoxLayout;
class ThreadServer;

class ServerButtons: public QObject
{
    Q_OBJECT
  public:
    explicit ServerButtons(ServerInit* parent);
    ~ServerButtons();
    QHBoxLayout* getLayout() {return m_pServerLayout;}

public slots:
    void isActivePressedServerConditionButton();

private:
    QPushButton* pQButtonrunServer;
    QHBoxLayout* m_pServerLayout;
};

