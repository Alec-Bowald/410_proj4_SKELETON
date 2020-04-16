#include <string>
#include "stdlib.h"

#include "../includes/waiter.h"
#include "../includes/externs.h"

using namespace std;

Waiter::Waiter(int id,std::string filename):id(id),myIO(filename){
}

Waiter::~Waiter()
{
}

//gets next Order(s) from file_IO
int Waiter::getNext(ORDER &anOrder){
	return myIO.getNext(anOrder);

}

void Waiter::beWaiter() {
	ORDER newOrder;
	while(getNext(newOrder) != NO_ORDERS){
		getNext(newOrder);
		order_in_Q.push(newOrder);
		cv_order_inQ.notify_all();
	}
	b_WaiterIsFinished = true;
}

