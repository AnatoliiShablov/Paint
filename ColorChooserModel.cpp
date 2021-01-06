#include "ColorChooserModel.hpp"

ColorChooserModel::ColorChooserModel(QObject *parent)
    : QAbstractListModel{parent} {}

qint32 ColorChooserModel::currentColor() const { return _currentColor; }

QColor ColorChooserModel::indexToColor(qint32 index) const {
  return (index < 0 || index >= _colors.size()) ? QColor{"white"}
                                                : _colors[index];
}

qint32 ColorChooserModel::cellSize() const { return _cellSize; }

int ColorChooserModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return _colors.size();
}

QVariant ColorChooserModel::data(const QModelIndex &index, int role) const {
  if (index.isValid() && index.row() >= 0 && index.row() < _colors.size()) {
    switch (static_cast<ColorChooserModelRoles>(role)) {
      case ColorChooserModel::CellColorRole:
        return _colors[index.row()];
      case ColorChooserModel::CellNumberRole:
        return index.row() + 1;
    }
  }
  return {};
}

QHash<int, QByteArray> ColorChooserModel::roleNames() const {
  return {{ColorChooserModelRoles::CellColorRole, "cellColor"},
          {ColorChooserModelRoles::CellNumberRole, "cellNumber"}};
}

void ColorChooserModel::setColors(QList<QColor> colors) {
  emit beginResetModel();
  _colors = colors;
  emit endResetModel();
  setCurrentColor(0);
}

void ColorChooserModel::setCurrentColor(qint32 currentColor) {
  if (_currentColor != currentColor) {
    _currentColor = currentColor;
    emit currentColorChanged(_currentColor);
  }
}
