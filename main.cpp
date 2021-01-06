#include "PaintModel.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  PaintModel paintModel;
  paintModel.load("/home/anatolii/instagram.png");

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  engine.rootContext()->setContextProperty("paintModel", &paintModel);
  engine.rootContext()->setContextProperty("colorChooserModel", &paintModel.colorChooserModel());

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
