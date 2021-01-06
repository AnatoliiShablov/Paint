#ifndef COLORCHOOSERMODEL_HPP
#define COLORCHOOSERMODEL_HPP

#include <QAbstractListModel>
#include <QColor>
#include <QList>

class ColorChooserModel : public QAbstractListModel {
 public:
  Q_OBJECT
 public:
  Q_PROPERTY(qint32 currentColor READ currentColor WRITE setCurrentColor NOTIFY
                 currentColorChanged)

  Q_PROPERTY(qint32 cellSize READ cellSize NOTIFY cellSizeChanged)

 public:
  enum ColorChooserModelRoles {
    CellColorRole = Qt::UserRole + 1,
    CellNumberRole
  };

  ColorChooserModel(QObject *parent = nullptr);

  qint32 currentColor() const;
  QColor indexToColor(qint32 index) const;
  qint32 cellSize() const;

  int rowCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  QHash<int, QByteArray> roleNames() const;

  void setColors(QList<QColor> colors);
 public slots:
  void setCurrentColor(qint32 currentColor);

 signals:
  void currentColorChanged(qint32 currentColor);
  void cellSizeChanged(qint32 cellSize);

 private:
  QList<QColor> _colors;

  qint32 _currentColor = 0;
  qint32 _cellSize = 60;
};

#endif  // COLORCHOOSERMODEL_HPP
