//begin
#include <QApplication>
#include <QLabel>
#include <QDebug>
#include <QTextStream>
#include <QThreadPool>
#include <QDir>


void createSettingsFile() {
    qDebug()<<QDir::currentPath();
    const QString filePath = QDir::currentPath() + "/settings.properties";
    QFile file(filePath);
    if (file.exists()) {
        if (!file.remove()) {
            qDebug() << "Failed to remove existing settings.properties!";
            return;
        }
    }
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "ver = 1.0\n";
        out << "type = alpha-test\n";
        file.close();
        qDebug() << "settings.properties created at:" << filePath;
    } else {
        qDebug() << "Failed to create settings.properties!";
    }
}

void createSettingsFile(const QString &path) {
    const QString filePath = path + "/settings.properties";
    QFile file(filePath);
    if (file.exists()) {
        if (!file.remove()) {
            qDebug() << "Failed to remove existing settings.properties!";
            return;
        }
    }
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "ver = 1.0\n";
        out << "type = alpha-test\n";
        file.close();
        qDebug() << "settings.properties created at:" << filePath;
    } else {
        qDebug() << "Failed to create settings.properties!";
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 使用 QtConcurrent::run 在全局线程池中异步创建文件

    QThreadPool::globalInstance()->start([]{
    createSettingsFile();
    });

    /*
    QString path = "D:/CLionProjects";
    QThreadPool::globalInstance()->start([path]{
    createSettingsFile(path);
    });
    */

    QLabel label("Hello world!", nullptr);
    label.resize(800, 600);                 // 设置窗口大小 800x600
    label.setAlignment(Qt::AlignTop);
    label.show();

    return QApplication::exec();
}
//end