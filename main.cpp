#include "entrance.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSoundEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/prefix1/res/RIcon1.ico"));

    QSoundEffect *music = new QSoundEffect();
    music->setSource(QUrl::fromLocalFile(":/prefix1/res/RMusic1.wav"));
    music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
    music->setVolume(0.5f);  //设置音量，在0到1之间
    music->play();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Paydirt_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Entrance *e=Entrance::instance();
    e->show();
    return a.exec();
}
