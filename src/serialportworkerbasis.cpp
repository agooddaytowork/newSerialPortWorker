#include "serialportworkerbasis.h"

SerialPortWorkerBasis::SerialPortWorkerBasis(QObject *parent) :
    AbstractStateMachineBasis(parent)
{
    anIf(SerialPortWorkerBasisDbgEn, anAck("SerialPortWorkerBasis Constructed"));
}

SerialPortWorkerBasis::~SerialPortWorkerBasis()
{
    dispose();
    anIf(SerialPortWorkerBasisDbgEn, anWarn("SerialPortWorkerBasis Destroyed"));
}

void SerialPortWorkerBasis::initialize()
{
    anIf(SerialPortWorkerBasisDbgEn, anAck("SerialPortWorkerBasis Initialized"));
}

void SerialPortWorkerBasis::dispose()
{
    anIf(SerialPortWorkerBasisDbgEn && isInitiated, anWarn("Clean SerialPortWorkerBasis"));
    isInitiated = false;
}

void SerialPortWorkerBasis::In(const GlobalSignal &aGlobalSignal)
{
    if (aGlobalSignal.Type.typeName() == QStringLiteral("SerialPortWorkerBasis::Data"))
    {

    }
}

const QMetaEnum SerialPortWorkerBasis::DataMetaEnum = QMetaEnum::fromType<SerialPortWorkerBasis::Data>();
const QMetaEnum SerialPortWorkerBasis::ErrorMetaEnum = QMetaEnum::fromType<SerialPortWorkerBasis::Error>();
const QMetaEnum SerialPortWorkerBasis::WarningMetaEnum = QMetaEnum::fromType<SerialPortWorkerBasis::Warning>();
const QMetaEnum SerialPortWorkerBasis::NotificationMetaEnum = QMetaEnum::fromType<SerialPortWorkerBasis::Notification>();
const QMetaEnum SerialPortWorkerBasis::QSerialPortErrorMetaEnum = QMetaEnum::fromType<QSerialPort::SerialPortError>();
