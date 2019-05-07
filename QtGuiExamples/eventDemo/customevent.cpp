#include "customevent.h"
#include <QEvent>

const QEvent::Type CustomEvent::EventType = (QEvent::Type)QEvent::registerEventType(QEvent::User+100);

static const int mEvent1 = QEvent::registerEventType(CUSTOM_EVENT_1);
static const int mEvent2 = QEvent::registerEventType(CUSTOM_EVENT_2);
static const int mEvent3 = QEvent::registerEventType(CUSTOM_EVENT_3);
//...
static const int mEventn = QEvent::registerEventType(CUSTOM_EVENT_n);
CustomEvent::CustomEvent():
    QEvent(EventType)
{

}

CustomEvent::CustomEvent(int type) :
    QEvent(static_cast<QEvent::Type>(type)),
    m_id(0)
{

}

int CustomEvent::getType(CustomEventType cEvent)
{
    int mRet = mEvent1;
    switch(cEvent) {
    case CUSTOM_EVENT_1:
        mRet = mEvent1;
        break;
    case CUSTOM_EVENT_2:
        mRet = mEvent2;
        break;
    case CUSTOM_EVENT_3:
        mRet = mEvent3;
        break;
    case CUSTOM_EVENT_n:
        mRet = mEventn;
        break;
    default:
        break;
    }
    return mRet;
}
