#include "weatherdetail.h"

WeatherDetail::WeatherDetail()
{
    m_desc = "";
    m_icon = "";
}

WeatherDetail::~WeatherDetail()
{

}

QString WeatherDetail::desc() const
{
    return m_desc;
}

void WeatherDetail::setDesc(const QString &desc)
{
    m_desc = desc;
}

QString WeatherDetail::icon() const
{
    return m_icon;
}

void WeatherDetail::setIcon(const QString &icon)
{
    m_icon = icon;
}


//weatherinfo
WeatherInfo::WeatherInfo()
{
    m_cityName = "";
    m_id = -1;
//    m_dateTime = null;
    m_temperature = 0.0;
    m_humidity = 0.0;
    m_pressure = 0.0;
    m_details.clear();
}

WeatherInfo::~WeatherInfo()
{

}

QString WeatherInfo::cityName() const
{
    return m_cityName;
}

void WeatherInfo::setCityName(const QString &cityName)
{
    m_cityName = cityName;
}

quint32 WeatherInfo::id() const
{
    return m_id;
}

void WeatherInfo::setId(quint32 id)
{
    m_id = id;
}

QDateTime WeatherInfo::dateTime() const
{
    return m_dateTime;
}

void WeatherInfo::setDateTime(const QDateTime &dateTime)
{
    m_dateTime = dateTime;
}

float WeatherInfo::temperature() const
{
    return m_temperature;
}

void WeatherInfo::setTemperature(float temperature)
{
    m_temperature = temperature;
}

float WeatherInfo::humidity() const
{
    return m_humidity;
}

void WeatherInfo::setHumidity(float humidity)
{
    m_humidity = humidity;
}

float WeatherInfo::pressure() const
{
    return m_pressure;
}

void WeatherInfo::setPressure(float pressure)
{
    m_pressure = pressure;
}

QList<WeatherDetail *> WeatherInfo::details() const
{
    return m_details;
}

void WeatherInfo::setDetails(const QList<WeatherDetail *> details)
{
    m_details = details;
}

QDebug operator <<(QDebug dbg, const WeatherDetail &w)
{
    dbg.nospace() << "("
                  << "Description: " << w.desc() << "; "
                  << "Icon: " << w.icon()
                  << ")";
    return dbg.space();
}

QDebug operator <<(QDebug dbg, const WeatherInfo &w)
{
    dbg.nospace() << "("
                  << "id: " << w.id() << "; "
                  << "City name: " << w.cityName() << "; "
                  << "Date time: " << w.dateTime().toString(Qt::DefaultLocaleLongDate) << ": " << endl
                  << "Temperature: " << w.temperature() << ", "
                  << "Pressure: " << w.pressure() << ", "
                  << "Humidity: " << w.humidity() << endl
                  << "Details: [";
    foreach (WeatherDetail *detail, w.details()) {
        dbg.nospace() << "( Description: " << detail->desc() << ", "
                      << "Icon: " << detail->icon() << "), ";
    }
    dbg.nospace() << "] )";
    return dbg.space();
}
