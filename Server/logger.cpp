#include "logger.h"

Logger Logger::instance;

Logger& Logger::getLogger()
{
    return instance;
}
