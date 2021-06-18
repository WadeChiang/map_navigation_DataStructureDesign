#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QTimer>
#include "graph.h"
#include "functional_building.h"
#include "timetable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct _clock{
    int hour;
    int minute;
    _clock();
    ~_clock();
    void inc();
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent*);

private:
    Ui::MainWindow* ui;

    Loca* loc;
    Loca* loc2;

    int start_pos, end_pos, mid_pos;
    int navigation_type;
    QTimer simu_timer;
    QTimer clock_timer;

    _clock clock;

    bool is_path_exist;
    bool is_repaint;
    bool is_simulation;
    bool is_cross_campus;
    bool is_logical_query;

    int which_campus;

    vector<int> path,path2;
    vector<int> logical_pos;

    int start_campus,mid_campus,end_campus;

    QPointF cur_pos, p_end;

    class_timetable class1;

    functional_building fn_building;


    void init_UI();
    void initConnect();

    double get_distance(int which,int start, int destination);

private slots:
    void navigation_target_changed();
    void start_navigation();
    void navigation_type_changed();
    void run_simulation();
    void update_navi();
    void campus_changed();
    void clock_update();
    void show_around();
    void timetable_query();
    void functional_query();
};
#endif // MAINWINDOW_H
