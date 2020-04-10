#include <mutex>
//#include <lock_quard>

#include "../includes/baker.h"
#include "../includes/PRINT.h"
#include "../includes/constants.h"
using namespace std;

Baker::Baker(int id) :
		id(id) {
	PRINT1(id);
}

Baker::~Baker() {
}

void Baker::bake_and_box(ORDER &anOrder) {
	DONUT newDonut;
	for (int i = 0; i < anOrder.number_donuts; i++) {
		anOrder.boxes.at(anOrder.order_number).addDonut(newDonut);
		if(anOrder.boxes.at(anOrder.order_number).size() == 12) {
			anOrder.boxes.at(anOrder.order_number + 1).addDonut(newDonut);
		}

	}

}

void Baker::beBaker() {

}
