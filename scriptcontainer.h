#ifndef SCRIPTCONTAINER_H
#define SCRIPTCONTAINER_H

#include "can_structs.h"
#include "canfilter.h"

#include <QJSEngine>
#include <QTimer>
#include <qlistwidget.h>

class ScriptContainer : public QObject
{
    Q_OBJECT

public:
    ScriptContainer();
    void gotFrame(const CANFrame &frame);

    QString fileName;
    QString filePath;
    QString scriptText;

public slots:
    void compileScript();
    void setErrorWidget(QListWidget *list);
    void setFilter(QJSValue id, QJSValue mask, QJSValue bus);
    void setTickInterval(QJSValue interval);
    void clearFilters();
    void sendFrame(QJSValue bus, QJSValue id, QJSValue length, QJSValue data);

private slots:
    void tick();

signals:
    void sendCANFrame(const CANFrame *, int);

private:
    QJSEngine scriptEngine;
    QJSValue compiledScript;
    QJSValue setupFunction;
    QJSValue gotFrameFunction;
    QJSValue tickFunction;
    QTimer timer;
    QListWidget *errorWidget;
    QList<CANFilter> filters;
};

#endif // SCRIPTCONTAINER_H
