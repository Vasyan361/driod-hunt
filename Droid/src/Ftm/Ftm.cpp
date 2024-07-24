#include "Ftm.h"

xSemaphoreHandle ftmSemaphore;

typedef struct FtmData {
    uint32_t distance = 0;
    uint32_t time = 0;
} FtmData;

FtmData ftmData;

// Обработчик отчетов FTM с вычислением расстояния до Wi-Fi FTM точки доступа
void onFtmReport(arduino_event_t *event) {
    wifi_event_ftm_report_t * report = &event->event_info.wifi_ftm_report;
    if (report->status == FTM_STATUS_SUCCESS) {
        ftmData.distance = report->dist_est;
        ftmData.time = report->rtt_est;
        free(report->ftm_report_data);   // Указатель на отчет FTM освобожден после использования
    }
    
    xSemaphoreGive(ftmSemaphore);      // Сигнал о том, что отчет получен
}

void Ftm::init(const char * ssid, const char * password)
{
    ftmSemaphore = xSemaphoreCreateBinary();     // Создать двоичный семафор (ввод/вывод из любого потока/ISR)
    WiFi.onEvent(onFtmReport, ARDUINO_EVENT_WIFI_FTM_REPORT);             // Прослушивание событий отчета FTM

    WiFi.begin(ssid, password);    // Подключение к точке доступа с включенным FTM
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    // while (getFtmReport());    // Запрашивать отчеты FTM до тех пор, пока один из них не вернёт false
}

// Инициализация сеанса FTM и ожидание отчета FTM
void Ftm::callFtmReport()
{
    WiFi.initiateFTM(FTM_FRAME_COUNT, FTM_BURST_PERIOD);
    xSemaphoreTake(ftmSemaphore, portMAX_DELAY);
}


uint32_t Ftm::getDistance()
{
    return ftmData.distance;
}

uint32_t Ftm::getTime()
{
    return ftmData.time;
}
