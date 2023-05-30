#include <QCoreApplication>

#include <QMqttClient>
#include <QSettings>
#include <QDebug>

#define info qInfo().nospace().noquote()

QMqttClient *client;
QString topicColor;
QString messageColor;

const QHash<QString, char> colors
{
    {"black"  , '0'},
    {"red"    , '1'},
    {"green" , '2'},
    {"yellow" , '3'},
    {"blue"   , '4'},
    {"magenta", '5'},
    {"cyan"   , '6'},
    {"white"  , '7'},
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    client = new QMqttClient(&a);

    QSettings set("settings.ini", QSettings::IniFormat);
    if(set.allKeys().isEmpty()) {
        set.setValue("host", "127.0.0.1");
        set.setValue("port", 1883);
        set.setValue("defaultTopic", "#");
        set.setValue("colors/topic", "magenta");
        set.setValue("colors/message", "green");
    }

    topicColor = QString("\e[3") + colors.value(set.value("colors/topic", '7').toString()) + 'm';
    messageColor = QString("\e[3") + colors.value(set.value("colors/message", '7').toString()) + 'm';

    QString topic = set.value("defaultTopic", "#").toString();

    if(a.arguments().size() > 1) {
        topic = a.arguments()[1];
    }

    client->setHostname(set.value("host", "127.0.0.1").toString());
    client->setPort(set.value("port", 1883).toInt());

    info << "connecting to " << client->hostname() << ":" << client->port();

    QObject::connect(client, &QMqttClient::connected, [=] () { info << "client connected. Topic: " << topic; client->subscribe(topic); });

    QObject::connect(client, &QMqttClient::messageReceived, [] (const QByteArray &message, const QMqttTopicName &topic = QMqttTopicName()) {
        info << topicColor << topic.name() << "\e[0m:" << messageColor << QString::fromLocal8Bit(message) << Qt::endl;
    });

    client->connectToHost();

    return a.exec();
}
