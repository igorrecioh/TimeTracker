#include "worktaskmodel.h"
#include "worktask.h"

WorkTaskModel::WorkTaskModel(QObject *parent) : QAbstractTableModel(parent)
{

}

// Método para rellenar la tabla
void WorkTaskModel::populateData(const QList<WorkTask> &workTasks)
{
    m_ids.clear();
    m_descriptions.clear();
    m_initialTimes.clear();
    m_finalTimes.clear();
    m_differences.clear();

    for(auto& workTask : workTasks) {
        m_ids.append(workTask.getId());
        m_descriptions.append(workTask.getDescription());
        m_initialTimes.append(workTask.getInitialTime());
        m_finalTimes.append(workTask.getFinalTime());
        m_differences.append(workTask.getDifference());
    }
    return;
}

int WorkTaskModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_descriptions.length();
}

int WorkTaskModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant WorkTaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return m_ids[index.row()];
    } else if (index.column() == 1) {
        return m_descriptions[index.row()];
    } else if (index.column() == 2) {
        return m_initialTimes[index.row()];
    } else if (index.column() == 3) {
        return m_finalTimes[index.row()];
    } else if (index.column() == 4) {
        return m_differences[index.row()];
    }
    return QVariant();
}

QVariant WorkTaskModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("ID");
        } else if (section == 1) {
            return QString("Descripción");
        } else if (section == 2) {
            return QString("Hora inicio");
        } else if (section == 3) {
            return QString("Hora fin");
        } else if (section == 4) {
            return QString("Duración");
        }
    }
    return QVariant();
}
