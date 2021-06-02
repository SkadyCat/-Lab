#include "mp3.h"
#include "ui_mp3.h"
#include "resources.h"
#include"fileviewwidget.h"
#include<QDebug>
MP3::MP3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MP3)
{
    ui->setupUi(this);

    this->setFixedSize(400,700);
    this->setPalette(Resources::getInstance()->getQPallete("bacground",400,700));
    player = new QMediaPlayer();
    list = new QMediaPlaylist();
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    player->setPlaylist(list);
    preTime = 0;
    maxTime = 0;


}

MP3* MP3::Instance;
MP3* MP3::getInstance(){

    if(Instance == NULL){
        Instance = new MP3();
    }
    return  Instance;
}
void MP3::positionChanged(qint64 time){


    preTime = time;
    maxTime = player->duration();
    qDebug()<<preTime<<"<>"<<maxTime;
    int second = maxTime/1000;
    int m = second/60;
    int s = second - m*60;

    int second1 = preTime/1000;
    int m1 = second1/60;
    int s1 = second1 - m1*60;
    percent = preTime/maxTime;
    qDebug()<<percent*100.;
    ui->percent->setValue(percent*100.);
    ui->time->setText(QString::number(m).append(".").append(QString::number(s)));

    ui->time_2->setText(QString::number(m1).append(".").append(QString::number(s1)));

}
MP3::~MP3()
{
    delete ui;
}

void MP3::on_play_clicked()
{
    if(playStatu%2== 0){


        player->play();
        ui->play->setText("stop");
    }
    if(playStatu%2 == 1){

        player->stop();
        ui->play->setText("play");
    }

    playStatu++;
}

void MP3::on_mode_2_clicked()
{

}

void MP3::on_file_clicked()
{
    FileViewWidget::getInstance()->operation = [](QString* path){


        qDebug()<<path->toStdString().c_str();

        MP3::getInstance()->list->addMedia(QMediaContent(QUrl::fromLocalFile(path->toStdString().c_str())));
        return 0;
    };
    FileViewWidget::getInstance()->showDialog();
}

void MP3::on_mode_clicked()
{
    switch(playMode%4){
        case 0:
        list->setPlaybackMode(QMediaPlaylist::Sequential);
        ui->mode->setText("Sequential");
        break;

    case 1:
        list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->mode->setText("CurrentItemInLoop");
        break;

    case 2:
        list->setPlaybackMode(QMediaPlaylist::Random);
        ui->mode->setText("Random");
        break;

    case 3:
        list->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        ui->mode->setText("CurrentItemOnce");

        break;

    }
    playMode++;
}

void MP3::on_right_clicked()
{
    list->next();
}

void MP3::on_left_clicked()
{
    list->previous();
}

void MP3::on_volume_sliderMoved(int position)
{
    player->setVolume(position);
}
