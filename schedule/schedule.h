#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QtWidgets/QMainWindow>
#include "ui_schedule.h"
#include <qlocale.h>


struct week_t{
	int weeks[32];
	week_t(int begin, int end){
		for(int i = 0; i < 32; i++){
			weeks[i] = 0;
		}
		for(int i = begin; i <= end; i++){
			if(i > 0 && i < 32)
				weeks[i] = 1;
		}
	}
	week_t(int w){
		for(int i = 0; i < 32; i++){
			weeks[i] = 0;
		}
		if(w > 0 && w < 32)
			weeks[w] = 1;
	}
	week_t(){
		for(int i = 0; i < 32; i++){
			weeks[i] = 0;
		}
	}
	week_t& operator+(week_t& rhs){
		week_t merged;
		for(int i = 0; i < 32; i++){
			merged.weeks[i] = weeks[i] || rhs.weeks[i];
		}
		return merged;
	}
};
struct course_time_t{
	int dow;
	int div_begin;
	int div_end;
	week_t weeks;
	std::string loc;
	course_time_t(std::string loc, int dow, int div_begin, int div_end, week_t weeks) : loc(loc), dow(dow), div_begin(div_begin), div_end(div_end), weeks(weeks){};
	course_time_t();
};

struct course_t{
	std::string name;
	std::vector<course_time_t> times;
	course_t(std::string name, std::vector<course_time_t> times) : name(name), times(times){
	}
};

class schedule : public QMainWindow
{
	Q_OBJECT

public:
	QLabel* lbls[12];
	schedule(QWidget *parent = 0);
	~schedule();
public slots:
	void refresh();

private:
	Ui::scheduleClass ui;
};

#endif // SCHEDULE_H
