#ifndef MP3_H
#define MP3_H

#include <QWidget>
#include <QMultimedia>
#include<QMediaPlayer>
#include<QMediaPlaylist>
namespace Ui {
class MP3;
}

class MP3 : public QWidget
{
    Q_OBJECT
private:

    static MP3* Instance;

public:
    explicit MP3(QWidget *parent = nullptr);
    ~MP3();
    static MP3* getInstance();
    QMediaPlayer *player;
    QMediaPlaylist *list;
    int playStatu;
    int playMode;
    double maxTime;
    double preTime;
    double percent;
private slots:
    void on_play_clicked();

    void on_mode_2_clicked();

    void on_file_clicked();

    void positionChanged(qint64 time);

    void on_mode_clicked();

    void on_right_clicked();

    void on_left_clicked();

    void on_volume_sliderMoved(int position);

private:
    Ui::MP3 *ui;
};

#endif // MP3_H
