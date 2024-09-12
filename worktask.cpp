#include "worktask.h"

WorkTask::WorkTask(QString description, QTime initialTime, QTime finalTime) : m_description{description}, m_initialTime{initialTime}, m_finalTime{finalTime}
{
    this->calculateDifference();
    m_id = ID;
    ID++;
}

int WorkTask::getId() const
{
    return this->m_id;
}

QString WorkTask::getDescription() const
{
    return this->m_description;
}

QTime WorkTask::getInitialTime() const
{
    return this->m_initialTime;
}

QTime WorkTask::getFinalTime() const
{
    return this->m_finalTime;
}

QString WorkTask::getDifference() const
{
    return m_difftime;
}

void WorkTask::calculateDifference()
{
    int finalSecs = QTime(0,0).secsTo(m_finalTime);
    int initialSecs = QTime(0,0).secsTo(m_initialTime);
    int diffSecs = finalSecs - initialSecs;
    m_difftime = QTime(0, 0).addSecs(diffSecs).toString("hh:mm");
    qDebug() << m_difftime << "\n";
}
