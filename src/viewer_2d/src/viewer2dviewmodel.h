#ifndef VIEWER2DVIEWMODEL_H
#define VIEWER2DVIEWMODEL_H

#include <QObject>

class Viewer2DViewModel : public QObject
{
    Q_OBJECT
public:
    explicit Viewer2DViewModel(QObject *parent = nullptr);

signals:
};

#endif // VIEWER2DVIEWMODEL_H
