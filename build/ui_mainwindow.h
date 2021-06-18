/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *start_combo_box;
    QComboBox *end_combo_box;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *navitype_combo_box;
    QPushButton *navi_button;
    QFrame *line;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *class_combo_box;
    QLabel *label_6;
    QComboBox *mid_combo_box;
    QPushButton *simu_button;
    QComboBox *sc_combo_box;
    QComboBox *ec_combo_box;
    QComboBox *mc_combo_box;
    QLabel *time_label;
    QLabel *label_7;
    QPushButton *around_button;
    QComboBox *course_combo_box_2;
    QComboBox *course_combo_box_3;
    QLabel *label_8;
    QPushButton *timetable_button;
    QLabel *label_9;
    QComboBox *fn_combo_box;
    QPushButton *func_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1542, 821);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        start_combo_box = new QComboBox(centralwidget);
        start_combo_box->setObjectName(QString::fromUtf8("start_combo_box"));
        start_combo_box->setGeometry(QRect(1260, 110, 87, 21));
        start_combo_box->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        end_combo_box = new QComboBox(centralwidget);
        end_combo_box->setObjectName(QString::fromUtf8("end_combo_box"));
        end_combo_box->setGeometry(QRect(1260, 180, 90, 20));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1170, 70, 91, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1170, 150, 71, 20));
        label_2->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1170, 30, 91, 31));
        label_3->setFont(font);
        navitype_combo_box = new QComboBox(centralwidget);
        navitype_combo_box->addItem(QString());
        navitype_combo_box->addItem(QString());
        navitype_combo_box->addItem(QString());
        navitype_combo_box->addItem(QString());
        navitype_combo_box->setObjectName(QString::fromUtf8("navitype_combo_box"));
        navitype_combo_box->setGeometry(QRect(1260, 40, 91, 22));
        navi_button = new QPushButton(centralwidget);
        navi_button->setObjectName(QString::fromUtf8("navi_button"));
        navi_button->setGeometry(QRect(1400, 40, 93, 61));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(1150, 0, 20, 881));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1290, 0, 91, 31));
        label_4->setFont(font);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1250, 390, 141, 41));
        label_5->setFont(font);
        class_combo_box = new QComboBox(centralwidget);
        class_combo_box->addItem(QString());
        class_combo_box->setObjectName(QString::fromUtf8("class_combo_box"));
        class_combo_box->setGeometry(QRect(1310, 450, 91, 22));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1160, 210, 91, 31));
        label_6->setFont(font);
        mid_combo_box = new QComboBox(centralwidget);
        mid_combo_box->setObjectName(QString::fromUtf8("mid_combo_box"));
        mid_combo_box->setGeometry(QRect(1260, 240, 87, 22));
        simu_button = new QPushButton(centralwidget);
        simu_button->setObjectName(QString::fromUtf8("simu_button"));
        simu_button->setGeometry(QRect(1400, 120, 93, 71));
        sc_combo_box = new QComboBox(centralwidget);
        sc_combo_box->addItem(QString());
        sc_combo_box->addItem(QString());
        sc_combo_box->setObjectName(QString::fromUtf8("sc_combo_box"));
        sc_combo_box->setGeometry(QRect(1260, 80, 91, 22));
        ec_combo_box = new QComboBox(centralwidget);
        ec_combo_box->addItem(QString());
        ec_combo_box->addItem(QString());
        ec_combo_box->setObjectName(QString::fromUtf8("ec_combo_box"));
        ec_combo_box->setGeometry(QRect(1260, 150, 91, 22));
        mc_combo_box = new QComboBox(centralwidget);
        mc_combo_box->addItem(QString());
        mc_combo_box->addItem(QString());
        mc_combo_box->setObjectName(QString::fromUtf8("mc_combo_box"));
        mc_combo_box->setGeometry(QRect(1260, 210, 91, 22));
        time_label = new QLabel(centralwidget);
        time_label->setObjectName(QString::fromUtf8("time_label"));
        time_label->setGeometry(QRect(1040, 10, 91, 41));
        time_label->setFont(font);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1270, 270, 61, 41));
        label_7->setFont(font);
        around_button = new QPushButton(centralwidget);
        around_button->setObjectName(QString::fromUtf8("around_button"));
        around_button->setGeometry(QRect(1260, 310, 93, 71));
        course_combo_box_2 = new QComboBox(centralwidget);
        course_combo_box_2->setObjectName(QString::fromUtf8("course_combo_box_2"));
        course_combo_box_2->setGeometry(QRect(1310, 480, 91, 22));
        course_combo_box_3 = new QComboBox(centralwidget);
        course_combo_box_3->addItem(QString());
        course_combo_box_3->addItem(QString());
        course_combo_box_3->addItem(QString());
        course_combo_box_3->addItem(QString());
        course_combo_box_3->addItem(QString());
        course_combo_box_3->addItem(QString());
        course_combo_box_3->setObjectName(QString::fromUtf8("course_combo_box_3"));
        course_combo_box_3->setGeometry(QRect(1310, 510, 91, 22));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(1180, 430, 141, 51));
        label_8->setFont(font);
        timetable_button = new QPushButton(centralwidget);
        timetable_button->setObjectName(QString::fromUtf8("timetable_button"));
        timetable_button->setGeometry(QRect(1420, 450, 93, 71));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(1180, 560, 111, 41));
        label_9->setFont(font);
        fn_combo_box = new QComboBox(centralwidget);
        fn_combo_box->setObjectName(QString::fromUtf8("fn_combo_box"));
        fn_combo_box->setGeometry(QRect(1310, 570, 91, 22));
        func_button = new QPushButton(centralwidget);
        func_button->setObjectName(QString::fromUtf8("func_button"));
        func_button->setGeometry(QRect(1420, 570, 93, 71));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1542, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\240\241\345\233\255\345\257\274\350\210\252", nullptr));
        label->setText(QApplication::translate("MainWindow", "\350\265\267\345\247\213\345\234\260\347\202\271", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\347\233\256\347\232\204\345\234\260", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\345\257\274\350\210\252\347\255\226\347\225\245", nullptr));
        navitype_combo_box->setItemText(0, QApplication::translate("MainWindow", "\346\231\256\351\200\232\345\257\274\350\210\252", nullptr));
        navitype_combo_box->setItemText(1, QApplication::translate("MainWindow", "\344\275\277\347\224\250\350\207\252\350\241\214\350\275\246", nullptr));
        navitype_combo_box->setItemText(2, QApplication::translate("MainWindow", "\351\200\224\345\276\204\345\234\260\347\202\271", nullptr));
        navitype_combo_box->setItemText(3, QApplication::translate("MainWindow", "\350\200\203\350\231\221\346\213\245\346\214\244\345\272\246", nullptr));

        navi_button->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\345\257\274\350\210\252", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\345\257\274\350\210\252", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\351\200\273\350\276\221\344\275\215\347\275\256", nullptr));
        class_combo_box->setItemText(0, QApplication::translate("MainWindow", "2019211318", nullptr));

        label_6->setText(QApplication::translate("MainWindow", "\351\200\224\345\276\204\345\234\260\347\202\271", nullptr));
        simu_button->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\250\241\346\213\237", nullptr));
        sc_combo_box->setItemText(0, QApplication::translate("MainWindow", "\346\240\241\345\214\272A", nullptr));
        sc_combo_box->setItemText(1, QApplication::translate("MainWindow", "\346\240\241\345\214\272B", nullptr));

        ec_combo_box->setItemText(0, QApplication::translate("MainWindow", "\346\240\241\345\214\272A", nullptr));
        ec_combo_box->setItemText(1, QApplication::translate("MainWindow", "\346\240\241\345\214\272B", nullptr));

        mc_combo_box->setItemText(0, QApplication::translate("MainWindow", "\346\240\241\345\214\272A", nullptr));
        mc_combo_box->setItemText(1, QApplication::translate("MainWindow", "\346\240\241\345\214\272B", nullptr));

        time_label->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "\346\237\245\345\221\250\350\276\271", nullptr));
        around_button->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        course_combo_box_3->setItemText(0, QApplication::translate("MainWindow", "\347\251\272", nullptr));
        course_combo_box_3->setItemText(1, QApplication::translate("MainWindow", "\345\221\250\344\270\200", nullptr));
        course_combo_box_3->setItemText(2, QApplication::translate("MainWindow", "\345\221\250\344\272\214", nullptr));
        course_combo_box_3->setItemText(3, QApplication::translate("MainWindow", "\345\221\250\344\270\211", nullptr));
        course_combo_box_3->setItemText(4, QApplication::translate("MainWindow", "\345\221\250\345\233\233", nullptr));
        course_combo_box_3->setItemText(5, QApplication::translate("MainWindow", "\345\221\250\344\272\224", nullptr));

        label_8->setText(QApplication::translate("MainWindow", "\347\224\261\350\257\276\347\250\213\350\241\250\346\237\245\350\257\242", nullptr));
        timetable_button->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\347\224\261\345\212\237\350\203\275\346\237\245\350\257\242", nullptr));
        func_button->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
