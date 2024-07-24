#include "StatusContainer.h"

void StatusContainer::init()
{
    for (uint8_t i = 0; i < MAX_DROIDS_COUNT; i++)
    {
        if (i < DROIDS_COUNT)
        {
            setStatus(i, STATUS_NOT_CONNECTED);
        } else {
            setStatus(i, STATUS_NOT_DEFINED);
        }
    }   
}

void StatusContainer::setStatus(uint8_t id, uint8_t statusCode)
{
    statusCodes[id] = statusCode;
}

uint8_t StatusContainer::getStatus(uint8_t id)
{
    return statusCodes[id];
}
