#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QPlainTextEdit>
#include "HopsanCore.h"


class MainWindow;

class MessageWidget : public QTextEdit
{
    Q_OBJECT
private:
    void setMessageColor(int type);

public:
    MessageWidget(MainWindow *pParent=0);
    void printCoreMessages();
    void printGUIMessage(QString message);
    void printGUIErrorMessage(QString message);
    void printGUIWarningMessage(QString message);
    void printGUIInfoMessage(QString message);
    QSize sizeHint() const;

public slots:
    void checkMessages();
};

#endif // MESSAGEWIDGET_H
