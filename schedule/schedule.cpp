#include "schedule.h"

#define TERM_BEGIN 2015,9,7

std::vector<course_t> course_list = {
	course_t("计算机体系结构",			{course_time_t("教1-107", 1, 9,11, week_t(2,20))} ),
	course_t("数理逻辑与程序理论",		{course_time_t("教1-113", 2, 5,7,  week_t(2,20))} ),
	course_t("计算机算法设计与分析",		{course_time_t("教1-101", 5, 2,4,  week_t(2,20))} ),
	course_t("模式识别与机器学习",		{course_time_t("教2-201", 1, 5,7,  week_t(2,20))} ),
	course_t("VLSI测试与可测试性设计",	{course_time_t("教1-109", 2, 9,11, week_t(2,16))}	),
	course_t("随机过程",					{course_time_t("教1-109", 3, 5,7,  week_t(2,17))} ),
	course_t("形式语言与自动机理论",		{course_time_t("教1-113", 5, 5,7,  week_t(2,17))} ),
	course_t("决策分析",					{course_time_t("教1-405", 2, 3,4,  week_t(2,15)),
										 course_time_t("教1-405", 4, 3,4,  week_t(2,15))} ),
	course_t("博弈论",					{course_time_t("教1-114", 2, 1,2,  week_t(2,14)),
										 course_time_t("教1-114", 4, 1,2,  week_t(2,14))} ),
	course_t("自然辩证法概论",			{course_time_t("教1-101", 3, 9,11, week_t(6) + week_t(7,16))} ), // week_t is concatenated by '+'.
};

schedule::schedule(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.calendarWidget, SIGNAL(selectionChanged()), this, SLOT(refresh()));
	lbls[1] = ui.lbl1;
	lbls[2] = ui.lbl2;
	lbls[3] = ui.lbl3;
	lbls[4] = ui.lbl4;
	lbls[5] = ui.lbl5;
	lbls[6] = ui.lbl6;
	lbls[7] = ui.lbl7;
	lbls[8] = ui.lbl8;
	lbls[9] = ui.lbl9;
	lbls[10] = ui.lbl10;
	lbls[11] = ui.lbl11;
	refresh();
#ifdef Q_OS_ANDROID
    //ui.lbl1->setText( QString::number(ui.verticalLayout_2->geometry().width()) );s
#endif

}

void schedule::refresh(){
	static const QDate term_begin(TERM_BEGIN);
	int days = term_begin.daysTo(ui.calendarWidget->selectedDate());
	int weeks = 1 + (days / 7);
	int dow = 1 + (days % 7);
	for (auto i = 1; i <= 11; i++){
		lbls[i]->setText(QString::number(i) + ":");
	}
	for (auto course = course_list.begin(); course != course_list.end(); course++){
		for (auto time = course->times.begin(); time != course->times.end(); time++){
			if(!time->weeks.weeks[weeks]) continue;
			if(time->dow!=dow) continue;
			for(int i = 1; i <= 11; i++){
				if(i >= time->div_begin && i <= time->div_end){
					QString str = lbls[i]->text();
					QString str2 = QString::fromLocal8Bit( (std::string(" ") + course->name + "," + time->loc).c_str() );
					lbls[i]->setText(str + str2);
				}
			}
		}
	}
}

schedule::~schedule()
{

}
