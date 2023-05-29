#include "mesdialog.h"
#include "ui_mesdialog.h"
#include <QFont>
#include <QProcess>
#include <QFile>
#include<QTextStream>
#include <QDebug>

Mesdialog::Mesdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mesdialog)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    this->setModal(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->frame->setObjectName("mydialog");
    ui->frame->setStyleSheet("QFrame#mydialog{background-color:#ffffff;border:none;border-radius:15px;color:rgb(100,100,100);}" );

//    this->ToShowEnglish();

    connect(ui->Button_cancel,SIGNAL(released()),this,SLOT(CancelPressed()));
    connect(ui->Button_ok,SIGNAL(released()),this,SLOT(OkPressed()));
}

Mesdialog::~Mesdialog()
{
    delete ui;
}

void Mesdialog::ShowOkButton()
{
    ui->Button_cancel->close();
    ui->Button_ok->move(this->geometry().x()+150,ui->Button_ok->y()+110);
}

void Mesdialog::CancelPressed()
{
   this->close();
}

void Mesdialog::OkPressed()
{
    this->close();
//    if(which_Mesdialog)
//    {
//        QProcess::execute("cd /");
//        QProcess::execute("reboot");
//    }
}

void Mesdialog::ToShowChinese()
{
    QFont ft;
//    ft.setPointSize(36);
//    ft.setWeight(75);
#ifdef WINDOWS
    ft.setPointSize(24);
#endif

    if(which_Mesdialog)
    {
        ui->Button_cancel->setFont(ft);
        ui->Button_cancel->setText("取消");
        ui->Button_cancel->setStyleSheet("border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:8px;"
                                         "border-bottom-right-radius:8px;background-color:#ffffff;color:#000000;"
                                         "background:transparent;border:1px solid #D3D3D3;");
        ui->Button_cancel->show();
        ui->Button_ok->move(300,110);
    }
    else
    {
        ui->Button_cancel->close();
        ui->Button_ok->move(150,110);
    }

    ui->Button_ok->setFont(ft);
    ui->Button_ok->setText("确定");
    ui->Button_ok->setStyleSheet("border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:8px;"
                                 "border-bottom-right-radius:8px;background-color:#ffffff;color:#0000FF;"
                                 "background:transparent;border:1px solid #D3D3D3;");

    ui->label_title->setFont(ft);
    ui->label_title->setText("提示");
    ui->label_title->setAlignment(Qt::AlignCenter);

    ui->label_ques->setFont(ft);
    if(which_Mesdialog)
        ui->label_ques->setText("控制频率1~10Hz!");
    else
    {
        QString tips;
        QFile date("/bin/logtips");
            if(date.open(QIODevice::ReadWrite|QIODevice::Text))
            {
                QTextStream in(&date);
                tips = in.readAll();
                tips = tips.left(3);
                qDebug()<<tips;
                int cmp;
                cmp = QString::compare(tips,"yes");
                if(cmp == 0)
                    ui->label_ques->setText("日志导出成功!");
                else
                    ui->label_ques->setText("日志导出失败 请插入U盘");
            }
            date.close();
//       ui->label_ques->setText("日志导出成功");
    }

    ui->label_ques->setAlignment(Qt::AlignCenter);


}

void Mesdialog::ToShowEnglish()
{
    QFont ft;
    ft.setPointSize(34);
    ft.setWeight(75);
#ifdef WINDOWS
    ft.setPointSize(18);
#endif
    if(which_Mesdialog)
    {
        ui->Button_cancel->setFont(ft);
        ui->Button_cancel->setText("CANCEL");
        ui->Button_cancel->setStyleSheet("border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:8px;"
                                         "border-bottom-right-radius:8px;background-color:#ffffff;color:#000000;"
                                         "background:transparent;border:1px solid #D3D3D3;");
        ui->Button_cancel->show();
        ui->Button_ok->move(300,110);
    }
    else
    {
        ui->Button_cancel->close();
        ui ->Button_ok->move(150,110);
     }


    ui->Button_ok->setFont(ft);
    ui->Button_ok->setText("OK");
    ui->Button_ok->setStyleSheet("border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:8px;"
                                 "border-bottom-right-radius:8px;background-color:#ffffff;color:#0000FF;"
                                 "background:transparent;border:1px solid #D3D3D3;");


    ui->label_title->setFont(ft);
    ui->label_title->setText("Tips");
    ui->label_title->setAlignment(Qt::AlignCenter);

    ui->label_ques->setFont(ft);
    if(which_Mesdialog)
        ui->label_ques->setText("The control frequency range is 1~10Hz!");//ui->label_ques->setText("Are you sure to reboot the system?");
    else
    {
        QString tips;
        QFile date("/bin/logtips");
            if(date.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                QTextStream in(&date);
                tips = in.readAll();
                tips = tips.left(3);
                qDebug()<<tips;
                int cmp;
                cmp = QString::compare(tips,"yes");
                if(cmp == 0)
                    ui->label_ques->setText("Log export succeeded!");
                else
                    ui->label_ques->setText("Log export failed please insert usbdisk");
            }
            date.close();
//      ui->label_ques->setText("Log export succeeded!");
    }

    ui->label_ques->setAlignment(Qt::AlignCenter);

}
