#include "readbytesserialportworker.h"

readBytesSerialPortWorker::readBytesSerialPortWorker(SerialPortWorkerBasis *parentBasis, QState *parent) :
    QState(parent),
    basisptr(parentBasis)
{
    setObjectName(QStringLiteral("readBytesSerialPortWorker"));
    anIf(SerialPortWorkerBasisDbgEn, anAck("readBytesSerialPortWorker Constructed"));
}

void readBytesSerialPortWorker::onEntry(QEvent *)
{
    anIf(SerialPortWorkerBasisDbgEn, anTrk("readBytesSerialPortWorker Entered"));
    basisptr->currentStateName = objectName();
    qApp->processEvents();
    if (basisptr->SerialPort.waitForReadyRead(2700))
    {
        QByteArray tmpRead(basisptr->SerialPort.readAll());
        while (basisptr->SerialPort.waitForReadyRead(300))
        {
            tmpRead += basisptr->SerialPort.readAll();
        }
        anIf(SerialPortWorkerBasisDbgEn, anAck("Bytes Read !"));
        basisptr->currentGlobalSignal.Type = QVariant::fromValue(SerialPortWorkerBasis::replyBytesWithTimeStamp);
        basisptr->currentGlobalSignal.Data = QVariant::fromValue(tmpRead);
        basisptr->currentGlobalSignal.TimeStamp = NOW2String;
    }
    else
    {
        anIf(SerialPortWorkerBasisDbgEn, anWarn("Ready Read Timed Out !"));
        basisptr->currentGlobalSignal.Type = QVariant::fromValue(SerialPortWorkerBasis::ReadyReadTimedOut);
    }
    basisptr->addAGlobalSignal(basisptr->currentGlobalSignal);
    emit basisptr->requestDirectTransition(QStringLiteral("runningSerialPortWorker"));
}

void readBytesSerialPortWorker::onExit(QEvent *)
{
    anIf(SerialPortWorkerBasisDbgEn, anTrk("Leave readBytesSerialPortWorker"));
    basisptr->previousStateName = objectName();
}
