//
// Created by Keenshi on 26.10.2019.
//

#include "Queue.h"

template<class T>
void Queue<T>::push(T value) {
	const std::lock_guard<std::mutex> guard(qmutex);
	q.push(value);
}

template<class T>
T Queue<T>::pop() {
	const std::lock_guard<std::mutex> guard(qmutex);
	T top = q.front();
	q.pop();
	return top;
}

template<class T>
bool Queue<T>::empty() {
	const std::lock_guard<std::mutex> guard(qmutex);
	return q.empty();
}
