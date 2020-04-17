/*
 * Authors: Jackie Brown, Alec Bowald
 */


#include <mutex>
#include <condition_variable>
//#include <lock_quard>

#include "../includes/baker.h"
#include "../includes/PRINT.h"
#include "../includes/constants.h"
#include "../includes/externs.h"

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
	int orderDone = 0;
	int numberBoxes = 0;
	Box firstBox;
	anOrder.boxes.push_back(firstBox);

	while (orderDone != anOrder.number_donuts) {
		DONUT newDonut;
		if (anOrder.boxes.at(numberBoxes).size() == 12) {
			Box newBox;
			anOrder.boxes.push_back(newBox);
			numberBoxes += 1;
		}
		anOrder.boxes.at(numberBoxes).addDonut(newDonut);
		orderDone += 1;
	}

}

void Baker::beBaker() {
	while (!b_WaiterIsFinished || !order_in_Q.empty()) {
		ORDER newOrder;
		unique_lock<mutex> lck(m);
		while (order_in_Q.empty()) {
			cv_order_inQ.wait(lck);
		}
		mutex_order_inQ.lock();  //might need to be revisited
		newOrder = order_in_Q.front();
		order_in_Q.pop();
		mutex_order_inQ.unlock();
		bake_and_box(newOrder);
		if (newOrder.order_number != UNINITIALIZED) {
			mutex_order_outQ.lock();
			order_out_Vector.push_back(newOrder);
			mutex_order_outQ.unlock();
		}
	}
}
