#include "uninitiatedserialportworker.h"

uninitiatedSerialPortWorker::uninitiatedSerialPortWorker(SerialPortWorkerBasis *parentBasis, QState *parent) :
    QState(parent),
    basisptr(parentBasis)
{
    setObjectName(QStringLiteral("uninitiatedSerialPortWorker"));
    anIf(SerialPortWorkerBasisDbgEn,anAck("uninitiatedSerialPortWorker Constructed"));
}

void uninitiatedSerialPortWorker::onEntry(QEvent *)
{
    anIf(SerialPortWorkerBasisDbgEn,anTrk("uninitiatedSerialPortWorker Entered"));
    basisptr->currentStateName = objectName();
    qApp->processEvents();
    if (!(basisptr->isInitiated))
    {
        if (basisptr->PortName.isEmpty())
        {
            GlobalSignal requestPortName;
            requestPortName.Type = QVariant::fromValue(SerialPortWorkerBasis::requestPortName);
            requestPortName.SignalPriority = 200;
            requestPortName.DstStrs.append(SmallCoordinatorObjName);
            emit basisptr->Out(requestPortName);
        }
        else
        {
            basisptr->initialize();
        }
    }
}

void uninitiatedSerialPortWorker::onExit(QEvent *)
{
    anIf(SerialPortWorkerBasisDbgEn,anTrk("Leave uninitiatedSerialPortWorker"));
    basisptr->previousStateName = objectName();
}
