#include "schedule.h"

#define 学期开始 2015,9,7

#define 周一 1
#define 周二 2
#define 周三 3
#define 周四 4
#define 周五 5
#define 周六 6
#define 周日 7
#define 第(d1) ,d1,
#define 节到第(d2) d2
#define 节

std::vector<course_t> course_list = {
	course_t("计算机体系结构",			{course_time_t("教1-107", 周一 第(9)节到第(11)节, week_t(2,20))} ),
	course_t("数理逻辑与程序理论",		{course_time_t("教1-113", 周二 第(5)节到第(7)节,  week_t(2,20))} ),
	course_t("计算机算法设计与分析",		{course_time_t("教1-101", 周五 第(2)节到第(4)节,  week_t(2,20))} ),
	course_t("模式识别与机器学习",		{course_time_t("教1-107", 周一 第(5)节到第(7)节,  week_t(2,20))} ),
	course_t("VLSI测试与可测试性设计",	{course_time_t("教1-109", 周二 第(9)节到第(11)节, week_t(2,16))}	),
	course_t("随机过程",					{course_time_t("教1-109", 周三 第(5)节到第(7)节,  week_t(2,17))} ),
	course_t("电子领域学科与技术态势分析",{course_time_t("L-145",   周五 第(5)节到第(7)节,  week_t(2,15))} ),
	course_t("决策分析",					{course_time_t("教1-405", 周二 第(3)节到第(4)节,  week_t(2,15)),
										 course_time_t("教1-405", 周四 第(3)节到第(4)节,  week_t(2,15))} ),
	course_t("博弈论",					{course_time_t("教1-313", 周二 第(1)节到第(2)节,  week_t(2,14)),
										 course_time_t("教1-313", 周四 第(1)节到第(2)节,  week_t(2,14))} ),
	course_t("自然辩证法概论",			{course_time_t("教1-101", 周三 第(9)节到第(11)节, week_t(6) + week_t(7,16))} ), // week_t is concatenated by '+'.
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
}

void schedule::refresh(){
	static const QDate term_begin(学期开始);
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
