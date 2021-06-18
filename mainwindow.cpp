#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QMessageBox>
#include <windows.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      class1("2019211318"),
      fn_building("functional_building") {
    ui->setupUi(this);

    start_pos = 0;
    end_pos = 0;
    mid_pos = 0;
    is_path_exist = false;
    is_repaint = true;
    is_simulation = false;
    is_cross_campus=false;
    is_logical_query=false;

    navigation_type = 0;
    which_campus = 0;

    path.push_back(0);
    path2.push_back(0);
    cur_pos.setX(0);
    cur_pos.setY(0);
    p_end.setX(0);
    p_end.setY(0);

    start_campus=0;
    mid_campus=0;
    end_campus=0;


    init_UI();
    initConnect();
    repaint();

}

void MainWindow::init_UI() {
    loc = new Loca[40];
    initgraph(loc);
    init_name_info(loc,1);
    init_distance(loc,1);

    loc2=new Loca[40];
    initgraph(loc2);
    init_name_info(loc2,2);
    init_distance(loc2,2);

    for (unsigned i = 0;i < 40;++i)
    {
        ui->start_combo_box->addItem(QString::fromStdString(loc[i].name));
        ui->end_combo_box->addItem(QString::fromStdString(loc[i].name));
        ui->mid_combo_box->addItem(QString::fromStdString(loc[i].name));
    }
    for (auto elem : course_name_map )
    {
        if(elem.first!="empty")
        {
            ui->course_combo_box_2->addItem(QString::fromStdString(elem.first));
        }
    }
    for (auto elem: function_name_map)
    {
        ui->fn_combo_box->addItem(QString::fromStdString(elem.first));
    }
}

void MainWindow::initConnect() {
    QObject::connect(ui->start_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(navigation_target_changed()));
    QObject::connect(ui->end_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(navigation_target_changed()));
    QObject::connect(ui->mid_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(navigation_target_changed()));
    QObject::connect(ui->navitype_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(navigation_target_changed()));
    QObject::connect(ui->navi_button, SIGNAL(clicked()), this, SLOT(start_navigation()));
    QObject::connect(ui->navitype_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(navigation_type_changed()));
    QObject::connect(ui->simu_button, SIGNAL(clicked()), this, SLOT(run_simulation()));
    QObject::connect(&simu_timer, SIGNAL(timeout()), this, SLOT(update_navi()));
    QObject::connect(ui->sc_combo_box,SIGNAL(currentIndexChanged(int)), this, SLOT(campus_changed()));
    QObject::connect(ui->ec_combo_box,SIGNAL(currentIndexChanged(int)), this, SLOT(campus_changed()));
    QObject::connect(ui->mc_combo_box,SIGNAL(currentIndexChanged(int)), this, SLOT(campus_changed()));
    QObject::connect(&clock_timer,SIGNAL(timeout()),this,SLOT(clock_update()));
    QObject::connect(ui->around_button,SIGNAL(clicked()),this,SLOT(show_around()));
    QObject::connect(ui->timetable_button, SIGNAL(clicked()), this, SLOT(timetable_query()));
    QObject::connect(ui->func_button, SIGNAL(clicked()), this, SLOT(functional_query()));
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPen pen = painter.pen();
    pen.setWidth(5);
    painter.setPen(pen);
    for (unsigned i = 0;i < 40;++i)
    {
        int x = 80 + 100 * (i % 5);
        int y = 80 + (100 * (i / 5));

        for (int j = 0; j < loc[i].path_num;++j)
        {
            if (loc[i].path[j].distance > 0)
            {
                painter.drawLine(x, y, 80 + (100 * (loc[i].path[j].to_loca % 5)), 80 + (100 * (loc[i].path[j].to_loca / 5)));
            }
        }
        x+=550;
        for (int j = 0; j < loc2[i].path_num;++j)
        {
            if (loc2[i].path[j].distance > 0)
            {
                painter.drawLine(x, y, 550+80 + (100 * (loc2[i].path[j].to_loca % 5)), 80 + (100 * (loc2[i].path[j].to_loca / 5)));
            }
        }
    }
    pen.setWidth(0);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    for (unsigned i = 0;i < 40;++i)
    {
        int x = 50 + (100 * (i % 5)), y = 50 + (100 * (i / 5));
        QRect rect(x, y, 30, 30);
        painter.drawRect(rect);
        painter.drawText(rect, QString::fromStdString(loc[i].name));
    }
    for (unsigned i = 0;i < 40;++i)
    {
        int x = 600 + (100 * (i % 5)), y = 50 + (100 * (i / 5));
        QRect rect(x, y, 30, 30);
        painter.drawRect(rect);
        painter.drawText(rect, QString::fromStdString(loc2[i].name));
    }

    if (is_path_exist)
    {
        pen.setWidth(5);
        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.setBrush(Qt::white);
        for (unsigned i = 0;i < path.size() - 1;++i)
        {
            int x1 = 80 + 100 * (path[i] % 5);
            int y1 = 80 + (100 * (path[i] / 5));
            int x2 = 80 + 100 * (path[i + 1] % 5);
            int y2 = 80 + 100 * (path[i + 1] / 5);
            painter.drawLine(x1, y1, x2, y2);
        }

        for (unsigned i = 0;i < path2.size() - 1;++i)
        {
            int x1 = 80 + 550 + 100 * (path2[i] % 5);
            int y1 = 80 + (100 * (path2[i] / 5));
            int x2 = 80 + 550 + 100 * (path2[i + 1] % 5);
            int y2 = 80 + 100 * (path2[i + 1] / 5);
            painter.drawLine(x1, y1, x2, y2);
        }
    }

    if (is_simulation == true)
    {
        pen.setWidth(5);
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        painter.drawPoint(p_end);
    }

    if(is_logical_query)
    {
        pen.setWidth(0);
        painter.setPen(pen);
        painter.setBrush(Qt::red);
        for (unsigned i=0; i<logical_pos.size(); ++i)
        {
            if(logical_pos[i]!=0)
            {
                int x = 70 + (100 * (logical_pos[i] % 5)), y = 70 + (100 * (logical_pos[i] / 5));
                QRect rect(x, y, 10, 10);
                painter.drawRect(rect);
            }
        }
    }
}

void MainWindow::navigation_target_changed() {
    start_pos = ui->start_combo_box->currentIndex();
    end_pos = ui->end_combo_box->currentIndex();
    mid_pos = ui->mid_combo_box->currentIndex();
}

void MainWindow::start_navigation() {
    which_campus=start_campus;
    if(start_campus==0 && end_campus==0)
    {
        switch (navigation_type)
        {
        case 0:
            path = Dj(loc, start_pos, end_pos);
        break;
        case 1:
        path = Dj_cyc(loc, start_pos, end_pos, 3);
        break;
        case 2:
        path = Dj_muti(loc, &mid_pos, 1, start_pos, end_pos);
        break;
        case 3:
        path = Dj_crowd(loc, start_pos, end_pos);
        break;
        }
        path2 =vector<int>{0};

        string info="Get path in campus A.";
        for (unsigned i=0; i<path.size()-1; ++i) {
            info+=loc[path[i]].name+"->";
        }
        info+=loc[path.back()].name;
        lprint(info);
    }
    if(start_campus == 1 && end_campus==1)
    {
        switch (navigation_type)
        {
        case 0:
        path2 = Dj(loc2, start_pos, end_pos);
        break;
        case 1:
        path2 = Dj_cyc(loc2, start_pos, end_pos, 3);
        break;
        case 2:
        path2 = Dj_muti(loc2, &mid_pos, 1, start_pos, end_pos);
        break;
        case 3:
        path2 = Dj_crowd(loc2, start_pos, end_pos);
        break;
        }
        path =vector<int>{0};

        string info="Get path in campus B.";
        for (unsigned i=0; i<path2.size()-1; ++i) {
            info+=loc2[path2[i]].name+"->";
        }
        info+=loc2[path2.back()].name;
        lprint(info);
    }
    int campus_A_gate=37;
    int campus_B_gate=38;
    if(start_campus==0 && end_campus==1)
    {
        is_cross_campus=true;
        switch (navigation_type)
        {
        case 0:
        path = Dj(loc, start_pos, campus_A_gate);
        path2 =Dj(loc2, campus_B_gate, end_pos);
        break;
        case 1:
        path = Dj_cyc(loc, start_pos, campus_A_gate, 3);
        path2 = Dj_cyc(loc2,campus_B_gate,end_pos,3);
        break;
        case 2:
            QMessageBox::warning(this,
                tr("警告"),
                tr("跨校区导航无法使用途径点"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
        break;
        case 3:
        path = Dj_crowd(loc, start_pos, campus_A_gate);
        path2 =Dj_crowd(loc2,campus_B_gate,end_pos);
        break;
        }

        string info="Get path in 2 campus.";
        for (unsigned i=0; i<path.size(); ++i) {
            info+=loc[path[i]].name+"(A)->";
        }
        info+="Bus->";
        for (unsigned i=0; i<path2.size()-1; ++i) {
            info+=loc2[path2[i]].name+"(B)->";
        }
        info+=loc2[path2.back()].name+"(B)";
        lprint(info);
    }

    if(start_campus == 1 && end_campus == 0)
    {
        is_cross_campus=true;
        switch (navigation_type)
        {
        case 0:
        path2 = Dj(loc2, start_pos, campus_B_gate);
        path =Dj(loc, campus_A_gate, end_pos);
        break;
        case 1:
        path2 = Dj_cyc(loc2, start_pos, campus_B_gate, 3);
        path = Dj_cyc(loc,campus_A_gate,end_pos,3);
        break;
        case 2:
            QMessageBox::warning(this,
                tr("警告"),
                tr("跨校区导航无法使用途径点"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
        break;
        case 3:
        path2 = Dj_crowd(loc2, start_pos, campus_B_gate);
        path = Dj_crowd(loc,campus_A_gate,end_pos);
        break;
        }
        string info="Get path in 2 campus.";
        for (unsigned i=0; i<path2.size(); ++i) {
            info+=loc2[path2[i]].name+"(B)->";
        }
        info+="Bus->";
        for (unsigned i=0; i<path.size()-1; ++i) {
            info+=loc[path[i]].name+"(A)->";
        }
        info+=loc[path.back()].name+"(A)";
        lprint(info);
    }

    is_path_exist = true;
    repaint();
}

double MainWindow::get_distance(int which,int start, int destination) {
    Loca *_loc;
    if(which==0)
    {
        _loc=loc;
    }
    else
    {
        _loc=loc2;
    }

    for (int i = 0; i < _loc[start].path_num; ++i)
    {
        if (_loc[start].path[i].to_loca == destination)
        {
            switch (navigation_type)
            {
            case 0:
            return _loc[start].path[i].distance;
            case 1:
            return _loc[start].path[i].distance / 3;
            case 2:
            return _loc[start].path[i].distance;
            case 3:
            return _loc[start].path[i].distance * _loc[start].path[i].crowding;
            }
        }
    }
    for (int i = 0; i < _loc[destination].path_num; ++i)
    {
        if (_loc[destination].path[i].to_loca == start)
        {
            switch (navigation_type)
            {
            case 0:
            return _loc[destination].path[i].distance;
            case 1:
            return _loc[destination].path[i].distance / 3;
            case 2:
            return _loc[destination].path[i].distance;
            case 3:
            return _loc[destination].path[i].distance * _loc[destination].path[i].crowding;
            }
        }
    }
    lprint("Error in get_distance.");
    return 0;
}

double get_X(int i) {
    i = 80 + 100 * (i % 5);
    return static_cast<double>(i);
}

double get_Y(int i) {
    i = 80 + (100 * (i / 5));
    return static_cast<double>(i);
}

void MainWindow::run_simulation() {
    is_simulation = true;
    is_repaint = false;
    is_path_exist = true;
    simu_timer.start(35);
    clock_timer.start(400);
    string s_info;
    s_info="Simulation start.";
    lprint(s_info);
}

void MainWindow::update_navi() {
    static unsigned i = -1;
    static double distance = -1;
    static double curr_len = 0;
    double dx, dy;
    if(is_cross_campus==false)
    {
        if(start_campus==0)
        {
            which_campus=0;
            cur_pos.setX(get_X(path[i]));
            cur_pos.setY(get_Y(path[i]));

            if (curr_len > distance)
            {
                ++i;
                string s_info;
                s_info=ui->time_label->text().toStdString()+". Arrive at " + loc[path[i]].name+".";
                lprint(s_info);
                if (i < path.size() - 1)
                {
                    distance = get_distance(0,path[i], path[i + 1]);
                }
                curr_len = 0;
            }
            if (curr_len <= distance && i < path.size() - 1)
            {
                double radiation = curr_len / distance;
                dx = (1 - radiation) * get_X(path[i]) + radiation * get_X(path[i + 1]);
                dy = (1 - radiation) * get_Y(path[i]) + radiation * get_Y(path[i + 1]);
                p_end.setX(dx);
                p_end.setY(dy);
                repaint();
                curr_len += 2;
            }
            if (i >= path.size() - 1)
            {
                i=-1;
                distance = -1;
                curr_len=0;
                is_simulation = false;
                is_repaint = true;
                is_path_exist = false;
                simu_timer.stop();
                clock_timer.stop();
                repaint();
            }
        }
        if(start_campus==1)
        {
            which_campus=1;
            cur_pos.setX(get_X(path2[i]));
            cur_pos.setY(get_Y(path2[i]));

            if (curr_len > distance)
            {
                ++i;
                string s_info;
                s_info=ui->time_label->text().toStdString()+". Arrive at " + loc2[path2[i]].name+".";
                lprint(s_info);
                if (i < path2.size() - 1)
                {
                    distance = get_distance(1,path2[i], path2[i + 1]);
                }
                curr_len = 0;
            }
            if (curr_len <= distance && i < path2.size() - 1)
            {
                double radiation = curr_len / distance;
                dx = (1 - radiation) * get_X(path2[i]) + radiation * get_X(path2[i + 1]);
                dy = (1 - radiation) * get_Y(path2[i]) + radiation * get_Y(path2[i + 1]);
                p_end.setX(dx+550);
                p_end.setY(dy);
                repaint();
                curr_len += 2;
            }
            if (i >= path2.size() - 1)
            {
                i=-1;
                distance = -1;
                curr_len=0;
                is_simulation = false;
                is_repaint = true;
                is_path_exist = false;
                simu_timer.stop();
                clock_timer.stop();
                repaint();
            }
        }
    }
    else
    {
        if(which_campus==start_campus)
        {
            if(start_campus==0)
            {
                cur_pos.setX(get_X(path[i]));
                cur_pos.setY(get_Y(path[i]));

                if (curr_len > distance)
                {
                    ++i;
                    string s_info;
                    s_info=ui->time_label->text().toStdString()+". Arrive at " + loc[path[i]].name+"(A).";
                    lprint(s_info);
                    if (i < path.size() - 1)
                    {
                        distance = get_distance(0,path[i], path[i + 1]);
                    }
                    curr_len = 0;
                }
                if (curr_len <= distance && i < path.size() - 1)
                {
                    double radiation = curr_len / distance;
                    dx = (1 - radiation) * get_X(path[i]) + radiation * get_X(path[i + 1]);
                    dy = (1 - radiation) * get_Y(path[i]) + radiation * get_Y(path[i + 1]);
                    p_end.setX(dx);
                    p_end.setY(dy);
                    repaint();
                    curr_len += 2;
                }
                if (i >= path.size() - 1)
                {
                    string s_info;
                    i=-1;
                    distance = -1;
                    curr_len=0;
                    clock.hour++;
                    clock.minute=0;
                    lprint(std::to_string(clock.hour)+":"+std::to_string(clock.minute)+". Bus arrive.");
                    clock.hour++;
                    lprint(std::to_string(clock.hour)+":"+std::to_string(clock.minute)+". Arrive campus B.");
                    which_campus=end_campus;

                }
            }
            if(start_campus==1)
            {
                cur_pos.setX(get_X(path2[i]));
                cur_pos.setY(get_Y(path2[i]));

                if (curr_len > distance)
                {
                    ++i;
                    string s_info;
                    s_info=ui->time_label->text().toStdString()+". Arrive at " + loc2[path2[i]].name+"(B).";
                    lprint(s_info);
                    if (i < path2.size() - 1)
                    {
                        distance = get_distance(1,path2[i], path2[i + 1]);
                    }
                    curr_len = 0;
                }
                if (curr_len <= distance && i < path2.size() - 1)
                {
                    double radiation = curr_len / distance;
                    dx = (1 - radiation) * get_X(path2[i]) + radiation * get_X(path2[i + 1]);
                    dy = (1 - radiation) * get_Y(path2[i]) + radiation * get_Y(path2[i + 1]);
                    p_end.setX(dx+550);
                    p_end.setY(dy);
                    repaint();
                    curr_len += 2;
                }
                if (i >= path2.size() - 1)
                {
                    i=-1;
                    distance = -1;
                    curr_len=0;
                    clock.hour++;
                    clock.minute=0;
                    lprint(std::to_string(clock.hour)+":"+std::to_string(clock.minute)+". Bus arrive.");
                    clock.hour++;
                    lprint(std::to_string(clock.hour)+":"+std::to_string(clock.minute)+". Arrive campus B.");
                    which_campus=end_campus;
                }
            }
        }
        else
        {
            if(end_campus==0)
            {
                cur_pos.setX(get_X(path[i]));
                cur_pos.setY(get_Y(path[i]));

                if (curr_len > distance)
                {
                    ++i;
                    string s_info;
                    s_info=ui->time_label->text().toStdString()+". Arrive at " + loc[path[i]].name+"(A).";
                    lprint(s_info);
                    if (i < path.size() - 1)
                    {
                        distance = get_distance(0,path[i], path[i + 1]);
                    }
                    curr_len = 0;
                }
                if (curr_len <= distance && i < path.size() - 1)
                {
                    double radiation = curr_len / distance;
                    dx = (1 - radiation) * get_X(path[i]) + radiation * get_X(path[i + 1]);
                    dy = (1 - radiation) * get_Y(path[i]) + radiation * get_Y(path[i + 1]);
                    p_end.setX(dx);
                    p_end.setY(dy);
                    repaint();
                    curr_len += 2;
                }
                if (i >= path.size() - 1)
                {
                    i=-1;
                    distance = -1;
                    curr_len=0;
                    is_simulation = false;
                    is_repaint = true;
                    is_path_exist = false;
                    simu_timer.stop();
                    clock_timer.stop();
                    repaint();
                }
            }
            if(end_campus==1)
            {
                cur_pos.setX(get_X(path2[i]));
                cur_pos.setY(get_Y(path2[i]));

                if (curr_len > distance)
                {
                    ++i;
                    string s_info;
                    s_info=ui->time_label->text().toStdString()+". Arrive at " + loc2[path2[i]].name+"(B).";
                    lprint(s_info);
                    if (i < path2.size() - 1)
                    {
                        distance = get_distance(1,path2[i], path2[i + 1]);
                    }
                    curr_len = 0;
                }
                if (curr_len <= distance && i < path2.size() - 1)
                {
                    double radiation = curr_len / distance;
                    dx = (1 - radiation) * get_X(path2[i]) + radiation * get_X(path2[i + 1]);
                    dy = (1 - radiation) * get_Y(path2[i]) + radiation * get_Y(path2[i + 1]);
                    p_end.setX(dx+550);
                    p_end.setY(dy);
                    repaint();
                    curr_len += 2;
                }
                if (i >= path2.size() - 1)
                {
                    i=-1;
                    distance = -1;
                    curr_len=0;
                    is_simulation = false;
                    is_repaint = true;
                    is_path_exist = false;
                    simu_timer.stop();
                    clock_timer.stop();
                    repaint();
                }
        }
        }
    }
}

void MainWindow::navigation_type_changed() {
    navigation_type = ui->navitype_combo_box->currentIndex();
}

void MainWindow::campus_changed(){
    if(start_campus!=ui->sc_combo_box->currentIndex())
    {
        start_campus=ui->sc_combo_box->currentIndex();
        if(start_campus==0)
        {
            ui->start_combo_box->clear();
            for (int i=0;i<40;++i)
            {
                ui->start_combo_box->addItem(QString::fromStdString(loc[i].name));
            }
        }
        else
        {
            ui->start_combo_box->clear();
            for (int i=0;i<40;++i)
            {
                ui->start_combo_box->addItem(QString::fromStdString(loc2[i].name));
            }
        }
    }
    if(end_campus!=ui->ec_combo_box->currentIndex())
    {
        end_campus=ui->ec_combo_box->currentIndex();
        if(end_campus==0)
        {
            ui->end_combo_box->clear();
            for (int i=0;i<40;++i)
            {
                ui->end_combo_box->addItem(QString::fromStdString(loc[i].name));
            }
        }
        else
        {
            ui->end_combo_box->clear();
            for (int i=0;i<40;++i)
            {
                ui->end_combo_box->addItem(QString::fromStdString(loc2[i].name));
            }
        }
    }
    if(mid_campus!=ui->mc_combo_box->currentIndex())
    {
        mid_campus=ui->mc_combo_box->currentIndex();
        if(mid_campus==0)
        {
            ui->mid_combo_box->clear();
            for (int i=0;i<40;++i)
            {
                ui->mid_combo_box->addItem(QString::fromStdString(loc[i].name));
            }
        }
        else
        {
            ui->mid_combo_box->clear();
            for (int i=0;i<40;++i)
            {
                ui->mid_combo_box->addItem(QString::fromStdString(loc2[i].name));
            }
        }
    }
}

void MainWindow::clock_update(){
    clock.inc();
    string s_time;
    if(clock.hour/10==0)
    {
        s_time="0"+std::to_string(clock.hour)+":";
    }
    else
    {
        s_time=std::to_string(clock.hour)+":";
    }
    if(clock.minute/10==0)
    {
        s_time+="0"+std::to_string(clock.minute);
    }
    else
    {
        s_time+=std::to_string(clock.minute);
    }
    ui->time_label->setText(QString::fromStdString(s_time));
}

void MainWindow::show_around(){
    vector<int> around;
    string s_around;
    Loca *_loc;
    if(start_campus==0)
    {
       _loc=loc;
    }
    else
    {
       _loc=loc2;
    }
    around=search(_loc,start_pos);
    for (unsigned i=0;i<around.size();++i)
    {
        s_around+= _loc[around[i]].name + "\n";
    }
    QString qs_around=QString::fromStdString(s_around);
    lprint(s_around);
    const char* cs_around=s_around.c_str();
    QMessageBox::information(this,
        tr("周边建筑"),
        tr(cs_around),
        QMessageBox::Ok | QMessageBox::Cancel,
        QMessageBox::Ok);
}

void MainWindow::timetable_query(){
    is_logical_query=true;
    if(ui->course_combo_box_3->currentIndex() != 0)
    {
        int day=ui->course_combo_box_3->currentIndex();
        logical_pos.clear();
        logical_pos.push_back(class1.find_pos("2019211318",ui->course_combo_box_2->currentText().toStdString(),day));
    }
    else
    {
        logical_pos=class1.find_pos("2019211318",ui->course_combo_box_2->currentText().toStdString());
    }

        repaint();

    is_logical_query=false;
}

void MainWindow::functional_query(){
    is_logical_query=true;
    QString qs_fn=ui->fn_combo_box->currentText();
    string s_fn=qs_fn.toStdString();
    logical_pos=fn_building.find_pos(s_fn);
    for (unsigned i=0;i<logical_pos.size() ;++i ) {
        cout<<logical_pos[i]<<" ";
    }
    repaint();
    is_logical_query=false;
}

MainWindow::~MainWindow() {
    delete ui;
    delete[] loc;
}

void _clock::inc(){

    ++minute;
    if(minute>=60)
    {
        minute=0;
        ++hour;
    }
    hour%=24;
}

_clock::_clock(){
    hour=8;
    minute=0;
}

_clock::~_clock(){

}

