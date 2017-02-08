#include "logentity.h"

LogEntity::LogEntity()
{

}

LogEntity::LogEntity(LogEntity &record)
{
    m_id = record.id();
    m_name = record.name();
    m_leftIrisTemplate = record.leftIrisTemplate();
    m_rightIrisTemplate = record.rightIrisTemplate();
    m_faceFeatureTemplate = record.faceFeatureTemplate();
    m_leftIrisPath = record.leftIrisPath();
    m_rightIrisPath = record.rightIrisPath();
    m_faceImagePath = record.faceImagePath();
}


