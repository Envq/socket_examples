# socket_examples
Examples of how to use sockets in different languages

QT version: 5.15


```c++
// STACK ALLOCATION
ServerUDP server;
QObject::connect(&server, SIGNAL(finished()), &app, SLOT(quit()), Qt::QueuedConnection);
server.init("127.0.0.1", 2000);
return app.exec();

// HEAP ALLOCATION
auto server = new ServerUDP();
QObject::connect(server, SIGNAL(finished()), server,
                    SLOT(deleteLater()));
QObject::connect(server, SIGNAL(finished()), &app, SLOT(quit()), Qt::QueuedConnection);
server->init("127.0.0.1", 2000);
return app.exec();

// The trick is to connect the deleteLater() slot with the finished() custom signal
```

