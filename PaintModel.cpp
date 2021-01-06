#include "PaintModel.hpp"

PaintModel::PaintModel(QObject *parent)
    : QAbstractTableModel{parent},
      _width{15},
      _height{10},
      _userColors(_width * _height, -1),
      _correctColors(_width * _height, -1) {}

int PaintModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return static_cast<int>(_height);
}

int PaintModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return static_cast<int>(_width);
}

QVariant PaintModel::data(const QModelIndex &index, int role) const {
  if (index.isValid() && index.row() >= 0 && index.row() < _height &&
      index.column() >= 0 && index.column() < _width) {
    switch (static_cast<PaintModelRoles>(role)) {
      case PaintModel::UserColorRole:
        return _colorChooserModel.indexToColor(
            _userColors[index.row() * _width + index.column()]);
      case PaintModel::ColorNumberRole:
        return _correctColors[index.row() * _width + index.column()] + 1;
      case PaintModel::CorrectRole:
        return _userColors[index.row() * _width + index.column()] ==
               _correctColors[index.row() * _width + index.column()];
    }
  }
  return {};
}

bool PaintModel::setData(const QModelIndex &index, const QVariant &value,
                         int role) {
  if (index.isValid() && index.row() >= 0 && index.row() < _height &&
      index.column() >= 0 && index.column() < _width &&
      value.toInt() == _colorChooserModel.currentColor()) {
    switch (static_cast<PaintModelRoles>(role)) {
      case PaintModel::UserColorRole:
        if (_userColors[index.row() * _width + index.column()] !=
            _colorChooserModel.currentColor()) {
          _userColors[index.row() * _width + index.column()] =
              _colorChooserModel.currentColor();
          emit dataChanged(index, index);
          return true;
        }
      case PaintModel::ColorNumberRole:
      case PaintModel::CorrectRole:
        break;
    }
  }
  return false;
}

QHash<int, QByteArray> PaintModel::roleNames() const {
  return {{PaintModelRoles::UserColorRole, "cellColor"},
          {PaintModelRoles::ColorNumberRole, "cellNumber"},
          {PaintModelRoles::CorrectRole, "correct"}};
}

qint32 PaintModel::cellSize() const { return _cellSize; }

ColorChooserModel &PaintModel::colorChooserModel() {
  return _colorChooserModel;
}
