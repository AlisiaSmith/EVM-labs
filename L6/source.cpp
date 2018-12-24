#include <iostream>
#include <libusb-1.0/libusb.h>
using namespace std;
 
void printdev(libusb_device *dev); //prototype of the function

int main() {
    libusb_device **devs; //указатель на указатель на устройство  
    libusb_context *ctx = NULL; //libusb сессия
    int r; //возвращаемое значение
    ssize_t cnt; //количество устройств
 
    r = libusb_init(&ctx); //инициализация сессии
    if(r < 0) {
   	 cout<<"Ошибка инициализации"<<r<<endl; //error
   	 return 1;
    }
 
    libusb_set_debug(ctx, 3); //установка уровня отладки 3
 
   cnt = libusb_get_device_list(ctx, &devs); //получение списка устройств
    if(cnt < 0) {
 cout<<"Список устройств не получен"<<endl; //ошибка    получения
    }
 
    cout<<"Количество устройств: "<< cnt <<endl;
 
  for(ssize_t i = 0; i < cnt; i++) {
    printdev(devs[i]);
    }
 
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx); //close the session
    return 0;
}
 
void printdev(libusb_device *dev) {
libusb_device_descriptor desc;
int r = libusb_get_device_descriptor(dev, &desc); //указатель на                устройство
char str[256];
 
    if (r < 0) {
    cout<<"Дескриптор устройства не получен"<<endl;
    return;
    }
libusb_device_handle* handle = NULL;   //указатель на дескриптор
r = libusb_open(dev, &handle);//открыть устройство (начать работать с устройством) и
                                                  	// получить дескриптор устройства, который далее можно использовать
                                                  	//для ввода/вывода данных
if (r < 0){
      cout << "Невозможно получить доступ к устройству" << endl;
   	 return;
    }
 cout << "Device Class: " << (int)desc.bDeviceClass << endl;
 
r = libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, (unsigned char*)str, 256); cout << "VendorID: " << desc.idVendor <<"  "<< str <<endl;
 
r = libusb_get_string_descriptor_ascii(handle, desc.iProduct, (unsigned char*)str, 256);
cout << "ProductID: " << desc.idProduct <<"  "<< str <<endl;
 
r = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, (unsigned char*)str, 256);
cout << "Serial Number: " << str <<endl ;	 
 
    libusb_close(handle);
 
    cout<<endl<<endl<<endl;  
}


