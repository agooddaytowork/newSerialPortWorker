#include "idleserialportworker.h"

idleSerialPortWorker::idleSerialPortWorker(SerialPortWorkerBasis *parentBasis, QState *parent) :
    QState(parent),
    basisptr(parentBasis)
{
    setObjectName(QStringLiteral("idleSerialPortWorker"));
    anIf(SerialPortWorkerBasisDbgEn, anAck("idleSerialPortWorker Constructed"));
}

void idleSerialPortWorker::onEntry(QEvent *)
{
    anIf(SerialPortWorkerBasisDbgEn, anTrk("idleSerialPortWorker Entered"));
    basisptr->currentStateName = objectName();
    qApp->processEvents();
    if (basisptr->previousStateName == QStringLiteral("uninitiatedSerialPortWorker"))
    {
        GlobalSignal iamReady;
        iamReady.Type = QVariant::fromValue(SerialPortWorkerBasis::readyToWork);
        iamReady.Data = QVariant::fromValue(machine()->objectName());
        iamReady.TimeStamp = NOW2String;
        iamReady.DstStrs.append(SmallCoordinatorObjName);
        iamReady.SignalPriority = 200;
        basisptr->addAGlobalSignal(iamReady,true);
    }
}

void idleSerialPortWorker::onExit(QEvent *)
{
    anIf(SerialPortWorkerBasisDbgEn, anTrk("Leave idleSerialPortWorker"));
    basisptr->previousStateName = objectName();
}
