#ifndef PAINTMODEL_HPP
#define PAINTMODEL_HPP

#include <QAbstractTableModel>
#include <QColor>
#include <QFileInfo>
#include <QImage>
#include <vector>

#include "ColorChooserModel.hpp"

class PaintModel : public QAbstractTableModel {
 public:
  Q_OBJECT
 public:
  Q_PROPERTY(qint32 cellSize READ cellSize NOTIFY cellSizeChanged)
  // bool loaded Q_PROPERTY(qint32 cellSize READ cellSize NOTIFY
  // cellSizeChanged)

  enum PaintModelRoles {
    UserColorRole = Qt::UserRole + 1,
    ColorNumberRole,
    CorrectRole
  };

  PaintModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;
  QHash<int, QByteArray> roleNames() const override;

  qint32 cellSize() const;
  ColorChooserModel &colorChooserModel();

  void load(QString path) {
    QImage img(path);

    QList<QColor> list;
    QVector<QRgb> table = img.colorTable();
    for (int i = 0; i < table.size(); ++i) {
      list.push_back(table[i]);
    }

    _colorChooserModel.setColors(list);

    emit beginResetModel();
    _height = img.height();
    _width = img.width();
    _correctColors.resize(_height * _width);
    _userColors.fill(-1, _height * _width);
    for (qint32 i = 0; i < _height; ++i) {
      for (qint32 j = 0; j < _width; ++j) {
        _correctColors[i * _width + j] = list.indexOf(QColor(img.pixel(j, i)));
      }
    }
    emit endResetModel();
  }

 signals:
  void cellSizeChanged(qint32 cellSize);

 private:
  qint32 _cellSize = 60;

  qint32 _width;
  qint32 _height;

  QVector<qint32> _userColors;
  QVector<qint32> _correctColors;

  ColorChooserModel _colorChooserModel;
};

#endif  // PAINTMODEL_HPP
