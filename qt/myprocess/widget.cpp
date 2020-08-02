#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    myprocess = new QProcess(this);
    connect(myprocess,SIGNAL(readyRead()),this,SLOT(slotProgressRead()));
    connect(myprocess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(slotProcessError(QProcess::ProcessError)));
    connect(myprocess,SIGNAL(readyReadStandardError()),this,SLOT(slotreadyReadStandardError()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
   QString cmd = ui->cmdlnt->text();
   QString  agrument = ui->optlnt->text();
   QStringList agruments = agrument.split(" ");

   if(agruments.isEmpty())
   {
     myprocess->start(cmd);
   }
   else
       myprocess->start(cmd,agruments);
}

void Widget::slotProgressRead()
{
    while(!myprocess->atEnd())
    {
       QString str = (QString) myprocess->readAll();
        ui->textEdit->append(str);
    }
}

void Widget::slotProcessError(QProcess::ProcessError e)
{
    switch (e) {
        case QProcess::FailedToStart:
                qDebug() << "FailedToStart" << endl;
        break;
        case QProcess::Crashed:
            qDebug() << "Crashed" << endl;
        break;
        case QProcess::Timedout:
            qDebug() << "Timedout" << endl;
        break;
        case QProcess::WriteError:
            qDebug() << "WriteError" << endl;
        break;
        case QProcess::ReadError:
            qDebug() << "ReadError" << endl;
        break;
        default:
            qDebug() << "UnknownError" << endl;
        break;

    }
}

void Widget::slotreadyReadStandardError()
{
    while(!myprocess->atEnd())
    {
        QString strerr = myprocess->readAllStandardError().replace("\n","");
         qDebug() <<"stderror:" << strerr <<endl;
    }
}
