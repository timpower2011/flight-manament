#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
#define  MAX 300
#define MAXHK 1000;

// thuoc tinh cua mot cai may bay
typedef struct {
	char sohieuMB[15];
	char loai[40];
	int soday;
	int sodong;
} MAYBAY;
//thuoc tinh date

typedef struct {
	int ngay, thang, nam;
} Date; 
//thuoc tinh time
typedef struct {
	int gio, phut, giay;
} TIME;
//ve
typedef struct {
	char cmnd[15];
	int soDay,soDong;
} TICKET;
typedef struct {
	char cmnd[15];
	string ho, ten, phai;
} HANHKHACH;
//danh sach may bay
typedef struct{
	int soluong = 0;
	MAYBAY *DSMayBay[MAX];
} DS_MAYBAY;
//cay nhi phan tim kiem
 struct NODE {
	HANHKHACH hanhkhach;
	NODE *left = NULL;
	NODE *right = NULL;	
};
typedef struct NODE DS_HANHKHACH;
struct chuyenbay{
	// soluong ve de save
	char machuyenbay[15];
	Date date;
	TIME time;
	char sanbayden[50];
	int trangthai;
	char sohieuMB[15];
	int soLuongVe=0;
	TICKET *ve[1000];
	
	chuyenbay *next = NULL;
};
// gan chuyenbay=CHUYENBAY
typedef struct chuyenbay CHUYENBAY;
typedef struct{
	int soluong=0;
	CHUYENBAY *pFirst =NULL,*pLast=NULL;
}   DS_CHUYENBAY;
//khai bao bien toan cuc
	DS_MAYBAY listMB;
	DS_CHUYENBAY listCB;
	DS_HANHKHACH *listHK = NULL;
/////////////////////////////////////////
/////////////////////////////////////////	
	
