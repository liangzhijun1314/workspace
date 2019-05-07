#ifndef CUSTOMEVENT_H
#define CUSTOMEVENT_H
#include <QEvent>

enum CustomEventType {
    CUSTOM_EVENT_1 = QEvent::User+100,
    CUSTOM_EVENT_2,
    CUSTOM_EVENT_3,
    //....
    CUSTOM_EVENT_n,
};

class CustomEvent : public QEvent
{
public:
    CustomEvent();
    explicit CustomEvent(int type);

    inline int getId() {return m_id;}
    inline void setId(int id) {m_id = id;}
    static int getType(CustomEventType cEvent);

public:
    static const Type EventType ;
private:
    int m_id;
};

#endif // CUSTOMEVENT_H
