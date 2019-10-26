//
// Created by evgeny on 26.10.2019.
//

#ifndef CONTINUUM_REPORTER_H
#define CONTINUUM_REPORTER_H


class Reporter {

public:

    Reporter(Queue *, db *);

    ~Reporter();

    virtual void WorkCycle();

private:

    Queue *q;

    db *;

};


#endif //CONTINUUM_REPORTER_H
