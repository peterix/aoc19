#include "log.h"

#include <QDateTime>

namespace {
qint64 timeSinceStart()
{
    static QDateTime startTime = QDateTime::currentDateTime();
    return startTime.msecsTo(QDateTime::currentDateTime());
}

void appDebugOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const char *levels = "DWCFIS";
    const QString format("%1 %2 %3\n");

    qint64 msecstotal = timeSinceStart();
    qint64 seconds = msecstotal / 1000;
    qint64 msecs = msecstotal % 1000;
    QString foo;
    char buf[1025] = {0};
    ::snprintf(buf, 1024, "%5lld.%03lld", seconds, msecs);

    QString out = format.arg(buf).arg(levels[type]).arg(msg);
    QTextStream(stderr) << out.toLocal8Bit();
    fflush(stderr);
}
}

void initLog() {
    qInstallMessageHandler(appDebugOutput);
    qDebug() << "<> Log initialized.";
}
