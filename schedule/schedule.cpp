#include "schedule.h"

#define ѧ�ڿ�ʼ 2015,9,7

#define ��һ 1
#define �ܶ� 2
#define ���� 3
#define ���� 4
#define ���� 5
#define ���� 6
#define ���� 7
#define ��(d1) ,d1,
#define �ڵ���(d2) d2
#define ��

std::vector<course_t> course_list = {
	course_t("�������ϵ�ṹ",			{course_time_t("��1-107", ��һ ��(9)�ڵ���(11)��, week_t(2,20))} ),
	course_t("�����߼����������",		{course_time_t("��1-113", �ܶ� ��(5)�ڵ���(7)��,  week_t(2,20))} ),
	course_t("������㷨��������",		{course_time_t("��1-101", ���� ��(2)�ڵ���(4)��,  week_t(2,20))} ),
	course_t("ģʽʶ�������ѧϰ",		{course_time_t("��1-107", ��һ ��(5)�ڵ���(7)��,  week_t(2,20))} ),
	course_t("VLSI������ɲ��������",	{course_time_t("��1-109", �ܶ� ��(9)�ڵ���(11)��, week_t(2,16))}	),
	course_t("�������",					{course_time_t("��1-109", ���� ��(5)�ڵ���(7)��,  week_t(2,17))} ),
	course_t("��������ѧ���뼼��̬�Ʒ���",{course_time_t("L-145",   ���� ��(5)�ڵ���(7)��,  week_t(2,15))} ),
	course_t("���߷���",					{course_time_t("��1-405", �ܶ� ��(3)�ڵ���(4)��,  week_t(2,15)),
										 course_time_t("��1-405", ���� ��(3)�ڵ���(4)��,  week_t(2,15))} ),
	course_t("������",					{course_time_t("��1-313", �ܶ� ��(1)�ڵ���(2)��,  week_t(2,14)),
										 course_time_t("��1-313", ���� ��(1)�ڵ���(2)��,  week_t(2,14))} ),
	course_t("��Ȼ��֤������",			{course_time_t("��1-101", ���� ��(9)�ڵ���(11)��, week_t(6) + week_t(7,16))} ), // week_t is concatenated by '+'.
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
	static const QDate term_begin(ѧ�ڿ�ʼ);
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
