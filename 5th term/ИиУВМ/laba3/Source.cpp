#include <iomanip>
#include "hexioctrl.h"
#include <io.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <sys/types.h>

using namespace std;

WORD data[256]; // 16битное целое число

BOOL GetSSDInfo ()
{
	WORD AS = 0x3F6; // альтернативный статус (при чтении) | не изменяет состояние устройства
    // бит 7 BSY busy 
    //       1 - занято
    // бит 6 DRDY device ready если 0 то доступны чтение и запись
    //       если состояние бита изменилось то оно не вернется до чтения регистра состояния
    //       если 1 то готово к выполнению вcех команд
    // бит 5 DF отказ устрйоства
    // бит 4 DSC индикатор завершения поиска трека или SERV нужно обсулживание
    // бит 3 DRQ готовность к обмену словом или байтом
    // бит 2 CORR индикатор исправленной ошибки данных
    // бит 1 IDX индекс, трактуется производителем
    // бит 0 ERR обшибка выполнения предыдущей операции

    // DC - управление устройством (при записи)

	WORD DR = 0x1F0; // регистр данных
    // 8/16 бит в зависимости от передаваемого типа данных, образение в режиме обмена PIO

	WORD DH = 0x1F6; // регистр адресcа (номера, устройства и головки или LBA[27:24])
    // выбор ведущего и ведомого утсройств, метода адресации
    // биты 7, 5 либо 1 1 до ATA-3, либо объявлены устаревшими
    // бит  6 = 1 указывает на режим адресации LBA, если 0 то CHS
    // бит  4 - DEV , 0-ведущее 1- ведомое устройство
    // биты 3-0 в режиме LBA старшие биты логического адреса 

    WORD CR = 0x1F7; // регистр команд (при записи)
    // сюда записать код команды и она начнет исполняться устройством

    // SR - регистр состояния (при чтении)

// пока устройство занято будет ждать система
    while (_inp(AS) & 0x80); //7 бит  busy
// работаем с мастер диском в режиме LBA (1110 0000)
    _outp(DH, (0 << 4) | 0xE0);
    
// бит 6 DRDY
    if (!_inp(AS) & 0x40)
        return false;       // не выполнится блок if
    
// IDENTIFY DEVICE 
    _outpw(CR, 0xEC);
// пока устройство занято будет ждать система
    while (_inp(AS) & 0x80);

// чтение 512 байт
    for (int i = 0; i < 256; i++)
        data[i] = _inpw(DR);

    return true;
}

void PrintData()
{
    // бит 2 (012) стоит hdd нет ssd
    cout << endl << setw(20) << setfill(' ') << left << "Disk:";
    if (data[217] & 0x4)
    {
        cout << " This is an HDD (rotational device)";
    }
    else 
    {
        cout << "This is an SSD";
    }

    cout << endl << endl <<setw (20) << "Model:";
    for (int i = 27; i <= 46; ++i)
        cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

    cout << endl <<setw (20) << "Manufacturer:";
    for (int i = 10; i <= 19; ++i)
        cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

    cout << endl <<setw (20) << "Serial Number:";
    for (int i = 10; i <= 19; ++i)
        cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

    cout << endl <<setw (20) << "Firmware Version:";
    for (int i = 23; i <= 26; ++i)
        cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

// размер сектора 512, поэтому умножаем, получаем байты, делим и делим и получаем мегабайты
    cout << endl <<setw (20) << "Total Size:";
    cout << setprecision(0) << (long double)(((ULONG*)data)[0]) * 512 / 1024 / 1024 << " MB";

    cout << endl <<setw (20) << "Interface:";

    switch (data[168] & 0x000F)
    {
        case 0x0000:
            cout << "No interface or unknown";
            break;
        case 0x0001:
            cout << "Parallel ATA (PATA)";
            break;
        case 0x000C:
            cout << "M.2 Interface";
            break;
        case 0x000D:
            cout << "U.2 Interface";
            break;
        case 0x000E:
            cout << "SCSI (Small Computer System Interface)";
            break;
        case 0x000F:
            cout << "IDE (Integrated Drive Electronics)";
            break;
        default:
            cout << "Unknown Interface";
            break;
    }

    cout << endl << endl << "PIO Support:\t\t";
    cout << (data[64] & 0x1 ? "PIO 3" : "") << "   " << (data[64] & 0x2 ? "PIO 4" : "");

    cout << endl << "Multiword DMA Support:\t";
    cout << (data[63] & 0x1 ? "MWDMA 0" : "") << " " << (data[63] & 0x2 ? "MWDMA 1" : "") << " " << (data[63] & 0x4 ? "MWDMA 2" : "");

    cout << endl << "Ultra DMA Support:\t";
    cout << (data[88] & 0x1 ? "UDMA 0" : "") << "  " << (data[88] & 0x2 ? "UDMA 1" : "") << "  " << (data[88] & 0x4 ? "UDMA 2" : "") << " " << (data[88] & 0x8 ? "UDMA 3" : "");

    cout << endl << endl;
}

int main()
{
    ALLOW_IO_OPERATIONS;

    if  (GetSSDInfo())
    {
        PrintData();
    }
    system("pause");
    return 0;
}