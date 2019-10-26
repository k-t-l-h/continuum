#ifndef CONTINUUM_WORKER_H
#define CONTINUUM_WORKER_H


class AbstractWorker {

public:

    virtual Worker(Queue *, n);

    virtual ~Worker();

    virtual void WorkCycle();

private:

    Queue *queue;

    Container *array;

};


#endif //CONTINUUM_WORKER_H
