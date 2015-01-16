#include <QtQml>
#include <QtQml/QQmlContext>

#include "backend.h"

#include "pingscanner.h"
#include "networkinfo.h"
#include "networkaddress.h"


void BackendPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("NetworkScanner"));

    qmlRegisterType<PingProcess>(uri, 1, 0, "PingProcess");
    qmlRegisterType<PingScanner>(uri, 1, 0, "PingScanner");
    qmlRegisterType<NetworkInfo>(uri, 1, 0, "NetworkInfo");
    qmlRegisterType<NetworkAddress>(uri, 1, 0, "NetworkAddress");
}

void BackendPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}

