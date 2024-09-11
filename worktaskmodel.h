#ifndef WORKTASKMODEL_H
#define WORKTASKMODEL_H
#include <QAbstractTableModel>
#include <QTime>
#include "worktask.h"

class WorkTaskModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    WorkTaskModel(QObject *parent = 0);

    void populateData(const QList<WorkTask> &workTasks);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<int> m_ids;
    QList<QString> m_descriptions;
    QList<QTime> m_initialTimes;
    QList<QTime> m_finalTimes;
    QList<QString> m_differences;
};

#endif // WORKTASKMODEL_H
