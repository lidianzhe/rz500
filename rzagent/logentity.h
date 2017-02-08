#ifndef LOGENTITY_H
#define LOGENTITY_H
#include <QString>

class LogEntity
{
public:
    LogEntity();
    LogEntity(LogEntity &record);

    const int id() {return m_id;}
    const QString &name() {return m_name;}
    const QByteArray &leftIrisTemplate() {return m_leftIrisTemplate;}
    const QByteArray &rightIrisTemplate() {return m_rightIrisTemplate;}
    const QByteArray &faceFeatureTemplate() {return m_faceFeatureTemplate;}
    const QString &leftIrisPath() {return m_leftIrisPath;}
    const QString &rightIrisPath() {return m_rightIrisPath;}
    const QString &faceImagePath() {return m_faceImagePath;}

    const int if_UserNo() {return m_if_UserNo;}


    void setId(int id) {m_id = id;}
    void setName(QString &name) {m_name = name;}
    void setLeftIrisTemplate(QByteArray &leftIrisTemplate) {m_leftIrisTemplate = leftIrisTemplate;}
    void setRightIrisTemplate(QByteArray &rightIrisTemplate) {m_rightIrisTemplate = rightIrisTemplate;}
    void setFaceFeatureTemplate(QByteArray &faceFeatureTemplate) {m_faceFeatureTemplate = faceFeatureTemplate;}
    void setLeftIrisPath(QString &leftIrisPath) {m_leftIrisPath = leftIrisPath;}
    void setRightIrisPath(QString &rightIrisPath) {m_rightIrisPath = rightIrisPath;}
    void setFaceImagePath(QString &faceImagePath) {m_faceImagePath = faceImagePath;}
    void setIf_UserNo(int if_UserNo){m_if_UserNo=if_UserNo;}
private:
    int m_id;
    QString m_name;
    QByteArray m_leftIrisTemplate;
    QByteArray m_rightIrisTemplate;
    QByteArray m_faceFeatureTemplate;
    QString m_leftIrisPath;
    QString m_rightIrisPath;
    QString m_faceImagePath;
    int m_if_UserNo;
};

#endif // LOGENTITY_H
