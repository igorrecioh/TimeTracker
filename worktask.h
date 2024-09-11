#ifndef WORKTASK_H
#define WORKTASK_H

#include <QString>
#include <QTime>

class WorkTask
{
private:
    inline static int ID = 0;
    int m_id;
    QString m_description;
    QTime m_initialTime;
    QTime m_finalTime;
    QString m_difftime;

public:
    WorkTask(QString description, QTime initialTime, QTime finalTime);
    int getId() const;
    QString getDescription() const;
    QTime getInitialTime() const;
    QTime getFinalTime() const;
    QString getDifference() const;
    void calculateDifference();
};

#endif // WORKTASK_H
