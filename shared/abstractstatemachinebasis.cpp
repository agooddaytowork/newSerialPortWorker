#include "abstractstatemachinebasis.h"

AbstractStateMachineBasis::AbstractStateMachineBasis(QObject *parent) : QObject(parent)
{

}

void AbstractStateMachineBasis::addAGlobalSignal(const GlobalSignal &aGlobalSignal, bool isCommunicative)
{
    if (prioritizedBuffer.contains(aGlobalSignal.Priority))
    {
        prioritizedBuffer[aGlobalSignal.Priority].append(aGlobalSignal);
    }
    else
    {
        prioritizedBuffer.insert(aGlobalSignal.Priority, QList<GlobalSignal>({aGlobalSignal}));
    }
    deleteEmptyListsFromPrioritizedBuffer();
    if (isCommunicative)
        emit aGlobalSignalAdded();
}

void AbstractStateMachineBasis::deleteEmptyListsFromPrioritizedBuffer()
{
    while (prioritizedBuffer.size())
    {
        if (prioritizedBuffer.last().size())
            break;
        else
        {
            prioritizedBuffer.remove(prioritizedBuffer.lastKey());
        }
    }
}

void AbstractStateMachineBasis::clearPrioritizedBuffer()
{
    if (prioritizedBuffer.size())
        prioritizedBuffer.clear();
}
