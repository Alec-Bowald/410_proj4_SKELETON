#include <mutex>
#include <condition_variable>
//#include <lock_quard>

#include "../includes/baker.h"
#include "../includes/PRINT.h"
#include "../includes/constants.h"

using namespace std;

mutex m;
condition_variable cv;
Baker::Baker(int id) :
		id(id) {
	PRINT1(id);
}

Baker::~Baker() {
}

void Baker::bake_and_box(ORDER &anOrder) {
	DONUT newDonut;
	int orderDone = 0;
	int numberBoxes = anOrder.order_number;

	unique_lock<mutex> lck(m);
	while (orderDone != anOrder.number_donuts) {
		anOrder.boxes.at(numberBoxes).addDonut(newDonut);
		if(anOrder.boxes.at(numberBoxes).size() == 12) {
			numberBoxes += 1;
		}
		orderDone += 1;
	}


}

void Baker::beBaker() {

}
