
#include "QLogger.h"

FILE* QLogger::s_logFile = nullptr;
QtMsgType QLogger::s_logLevel;

void QLogger::stopLogging() {
    qInstallMessageHandler(0);
    if (s_logFile) {
        fflush(s_logFile);
        fclose(s_logFile);
        s_logFile = nullptr;
    }
}


void QLogger::setLogLevel(int index) {
    switch (index) {
    case 0:
        stopLogging();
        break;
    case 1:
        setLogLevel(QtDebugMsg);
        break;
    default:
        setLogLevel(QtSystemMsg);
        break;
    }
}

void QLogger::setLogLevel(QtMsgType type) {
    s_logLevel = type;
    if (s_logFile == nullptr) {
        QString tempPath = QDir::tempPath() + QString("/Launchy");
        QDir tempDir(tempPath);
        if (!tempDir.exists()) {
            tempDir.mkpath(".");
        }
        QString logFileName = tempPath + QString("/launchy.log");
        s_logFile = fopen(logFileName.toUtf8(), "a");
        if (s_logFile) {
            qInstallMessageHandler(QLogger::messageHandler);
        }
    }
}

void QLogger::messageHandler(QtMsgType type,
                            const QMessageLogContext& context,
                            const QString& msg) {
    if (type <= s_logLevel || s_logFile == nullptr) {
        return;
    }
    QDateTime time = QDateTime::currentDateTime();
    QByteArray timeStr = time.toString("yyyy-MM-dd hh:mm:ss.zzz").toLocal8Bit();
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(s_logFile, "%s DEBUG: %s (%s:%u, %s)\n", timeStr.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(s_logFile, "%s WARNING: %s (%s:%u, %s)\n", timeStr.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(s_logFile, "%s CRITICAL: %s (%s:%u, %s)\n", timeStr.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(s_logFile, "%s FATAL: %s (%s:%u, %s)\n", timeStr.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(s_logFile, "%s INFO: %s (%s:%u, %s)\n", timeStr.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    }
    fflush(s_logFile);
}