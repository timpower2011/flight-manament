#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
#define  MAX_MAYBAY 300
#define MAXHK 1000;

#define ASCII_SPACE 32
#define ASCII_0 48
#define ASCII_9 57
#define ASCII_A 65
#define ASCII_Z 90


#define STATUS_CB_CONVE 1
#define STATUS_CB_HETVE 2
#define STATUS_CB_HOANTAT 3

int KiemTraCoPhaiLaQuaKhu(int ngay, int thang, int nam, int gio, int phut);
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
	MAYBAY *DSMayBay[MAX_MAYBAY];
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
	//con tro
	chuyenbay *next = NULL;
};
// gan chuyenbay=CHUYENBAY
typedef struct chuyenbay CHUYENBAY;
typedef struct{
	int soluong=0;
	CHUYENBAY *pFirst = NULL,*pLast = NULL;
}   DS_CHUYENBAY;
//khai bao bien toan cuc


	
	
void Insert_BST(DS_HANHKHACH *&root,HANHKHACH &hanhkhach){
	if ( root == NULL){	
		root = new DS_HANHKHACH;
		root->hanhkhach = hanhkhach;
		return;
	}
	
	if ( strcmp(root->hanhkhach.cmnd , hanhkhach.cmnd) <0){
		Insert_BST(root->right, hanhkhach);
	} else
	if (strcmp(root->hanhkhach.cmnd , hanhkhach.cmnd) >0) {
		Insert_BST(root->left, hanhkhach);
	}
}
void InHanhKhach(HANHKHACH &hanhkhach){
	cout << hanhkhach.cmnd << endl;
	cout << hanhkhach.ho << endl;
	cout << hanhkhach.ten << endl;
	cout << hanhkhach.phai << endl;
}
void InThongTinHanhKhach(HANHKHACH &hanhkhach){
	cout <<  "	CMND" << setw(10) << "	HOTEN" << setw(10) << "	PHAI" << endl;
	cout << "	" << hanhkhach.cmnd << setw(10) << hanhkhach.ho <<" "<< hanhkhach.ten << setw(10) << hanhkhach.phai << endl << endl;
}
void PreOrder(DS_HANHKHACH *root){
	if (root!=NULL) {
		InHanhKhach(root->hanhkhach);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

void Search_BTS(DS_HANHKHACH *&root,HANHKHACH &hanhkhach,char cmnd[]){
	if ( root == NULL )
        return;
    if(strcmp(root->hanhkhach.cmnd, cmnd) == 0){
        hanhkhach = root->hanhkhach;
        return;
    }else if ( strcmp(root->hanhkhach.cmnd , cmnd ) >0 ){
        return Search_BTS( root->left,hanhkhach, cmnd );
    }else if( strcmp(root->hanhkhach.cmnd , cmnd) <0){
        return Search_BTS( root->right,hanhkhach, cmnd );
    }
}
int HanhKhachCoTonTai(DS_HANHKHACH *&root,char cmnd[]){
	if ( root == NULL )
        return 0;
    if(strcmp(root->hanhkhach.cmnd, cmnd) == 0){
        return 1;
    }else if ( strcmp(root->hanhkhach.cmnd , cmnd ) >0 ){
        return HanhKhachCoTonTai( root->left, cmnd );
    }else if( strcmp(root->hanhkhach.cmnd , cmnd) <0){
        return HanhKhachCoTonTai( root->right, cmnd );
    }
}

DS_HANHKHACH* minValueNode(DS_HANHKHACH* node) 
{ 
    DS_HANHKHACH* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
DS_HANHKHACH* XoaHanhKhach(DS_HANHKHACH *root, char cmnd[]) 
{ 
    if (root == NULL) return root; 
    if (strcmp(cmnd , root->hanhkhach.cmnd) < 0) 
        root->left = XoaHanhKhach(root->left, cmnd); 
    else if ( strcmp(cmnd , root->hanhkhach.cmnd) > 0) 
        root->right = XoaHanhKhach(root->right, cmnd); 
    else
    { 
        if (root->left == NULL) 
        { 
            DS_HANHKHACH *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            DS_HANHKHACH *temp = root->left; 
            free(root);
            return temp; 
        } 
        DS_HANHKHACH *temp = minValueNode(root->right); 
        strcpy(root->hanhkhach.cmnd, temp->hanhkhach.cmnd); 
        root->right = XoaHanhKhach(root->right, temp->hanhkhach.cmnd); 
    } 
    return root; 
} 
//graphics
void line(int x1, int y1, int x2, int y2, int color){
	float y;
	int x;
	for (x=x1; x<=2; x++){
		y = y1 + (x-x1)*(y2-y1)/(x2-x1);
		putpixel(x,round(y),color);
	}
}
// graphics
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}
// H�m t� m�u.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}


// ve menu
void HinhVuong(int x1,int y1, int x2, int y2){
	for(int i=x1;i<=x2; i++){
		gotoxy(i,y1);
		cout << "-";
	}
	for(int i=y1;i<=y2; i++){
		gotoxy(x1,i);
		cout << "-";
	}
		for(int i=x1;i<=x2; i++){
		gotoxy(i,y2);
		cout << "-";
	}
	for(int i=y1;i<=y2; i++){
		gotoxy(x2,i);
		cout << "-";
	}	
}

// luu file
void SaveMB(DS_MAYBAY &l){
	ofstream savefile;
	savefile.open("MayBay.txt", ios::out);
	savefile <<	 l.soluong << endl;
	for(int i=1; i<=l.soluong; i++){
		savefile << l.DSMayBay[i]->sohieuMB<<endl; 
		savefile << l.DSMayBay[i]->loai<<endl;
		savefile << l.DSMayBay[i]->soday<<endl;
		savefile << l.DSMayBay[i]->sodong<<endl;
	}
	savefile.close();
}


// a) danh sach may bay
void ThemMayBay(DS_MAYBAY &l,char sohieu[], char loai[], int soday, int sodong){
	l.soluong++; 
	l.DSMayBay[l.soluong] = new MAYBAY;
	
	strcpy(l.DSMayBay[l.soluong]->sohieuMB,sohieu);
	strcpy(l.DSMayBay[l.soluong]->loai,loai);
	l.DSMayBay[l.soluong]->soday = soday;
	l.DSMayBay[l.soluong]->sodong = sodong ;
}
void XoaMayBay(DS_MAYBAY &l, char sohieu[]){
	
	for (int i=1; i<= l.soluong; i++){
		if (strcmp(l.DSMayBay[i]->sohieuMB,sohieu) == 0) {
			delete l.DSMayBay[i];
			for (i; i<l.soluong; i++){
				l.DSMayBay[i] = l.DSMayBay[i+1];
			}
			l.soluong--;
			return;
		}
		
	}
}
static void XuatDanhSach(DS_MAYBAY &l){	
	cout << "\t\t\tSO HIEU\t\t";
	cout << " LOAI\t\t " ;
	cout << "SO DAY\t\t" ;
	cout << "SO DONG\t\t\n" ;
	
	for (int i=1; i<= l.soluong; i++){

		cout   <<   "\t\t\t  " << l.DSMayBay[i]->sohieuMB << "\t\t";
		cout  << l.DSMayBay[i]->loai<< "\t\t";
		cout << "  " <<l.DSMayBay[i]->soday<<"\t\t" ;
		cout  << "  " <<l.DSMayBay[i]->sodong << "\t\t\n"; 
	}
	cout << "==============================================================================================" << endl;
	
	
	
}
int KiemTraKhoangTrang(char ch[]){
	for (int i=0; i< strlen(ch); i++){
		// mascii " "=32
		if( (int) ch[i] == ASCII_SPACE) return 0;
	}
	return 1;
}
void InHoa(char ch[]){
	for (int i=0; i< strlen(ch); i++){
		ch[i] = toupper(ch[i]);
	}
}

int KiemTraSo(string so){
	//so.c_str(): doi ve kieu char
	for (int i=0; i< strlen(so.c_str()); i++){
		if (so[i] < ASCII_0 or so[i] > ASCII_9) return 0;
	}
	return 1;
}
// tra ve 1 la trung, 0 khong trung
int KiemTraSoHieuMB(DS_MAYBAY &l,char ch[]){
	// bat dau tu 1
	for (int i=1; i<= l.soluong; i++){
		if(strcmp(l.DSMayBay[i]->sohieuMB,ch) == 0) return 1;
	} 
	return 0;
}
int KiemTraMBDaCoCB(DS_CHUYENBAY listCB, char maCB[]){
		for(CHUYENBAY *i = listCB.pFirst; i!=NULL; i=i->next){
				if(strcmp(i->sohieuMB, maCB) == 0){
					return 0;
				}
		}
		return 1;
}
int confirm(){
	char ch[10];
	cout << endl << "Ban co chac khong [Y/N]: ";
	fflush(stdin);
	gets(ch);
	InHoa(ch);
	if(strcmp(ch,"Y") == 0) return 1;
	return 0;
}
// ky tu 65-90 
int KiemTraKiTu(char text[]){
	
	for(int i=0; i<strlen(text); i++){
		// neu khong la chu
		if( ((int)text[i] <ASCII_A || (int)text[i] >ASCII_Z) ) {
			// neu la so 48-57
			if (((int)text[i] >= ASCII_0 && (int)text[i] <= ASCII_9)) continue;		
			return 0; 
		}
	}
	return 1;
}
//nhap
void NhapThongTinMayBay(DS_MAYBAY &l){
		char sohieuMB[15], loai[40];
		string sodong_tam,soday_tam;
		int sodong,soday;
	
		system("cls");
		cout << "				========NHAP THONG TIN MAY BAY========" << endl;
		//nhap so hieu
		sohieuMB:
		cout << "So hieu may bay: "; 
		fflush(stdin);
		gets(sohieuMB);
		InHoa(sohieuMB);
		//sohieuMB ko chua khoang trang
		if (strlen(sohieuMB) == 0) return;
		if (KiemTraKhoangTrang(sohieuMB) == 0 || KiemTraKiTu(sohieuMB) == 0) {
			cout << "ERROR: SO HIEU KHONG CHUA KHOANG TRANG!!! MOI NHAP LAI" << endl;
			Sleep(1000);
			goto sohieuMB;	
		}
	
		//kiem tra trung
		if(KiemTraSoHieuMB(l,sohieuMB) == 1) {
			cout << "ERROR: SO HIEU DA CO!!! MOI NHAP LAI" << endl;
			goto sohieuMB;
		};	
			
		loai:
		fflush(stdin);
		cout << "Loai: " ;
		gets(loai);
		InHoa(loai);
		if (strlen(loai) == 0) return;
		if( KiemTraKiTu(loai) == 0) {
			cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
			goto loai;
		};
		day:
		cout << "So day: "; 
		fflush(stdin);
		getline(cin,soday_tam); 
		if (strlen( soday_tam.c_str() ) == 0) return;
		if ( KiemTraSo(soday_tam) == 0) {
			system("cls");
			cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;;
			goto day;
		}	
		soday = atoi(soday_tam.c_str());
		dong:
		cout << "Sodong: "; 
		fflush(stdin);
		getline(cin,sodong_tam);
		if (strlen(sodong_tam.c_str()) == 0) return;
		if ( KiemTraSo(sodong_tam) == 0) {
			system("cls");
			cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
			goto dong;
		} 
		sodong = atoi(sodong_tam.c_str());	
		ThemMayBay(l,sohieuMB,loai,soday,sodong);
}
// sua
void ChinhSuaMayBay(DS_MAYBAY &l,char sohieuMB[]){
	int vitri;
	char soHieu_tam[100]={};
	strcpy(soHieu_tam,sohieuMB);
	// sua may bay sai mat phan xuat thong tin may bay
	system("cls");
	cout << "					THONG TIN MAY BAY CAN SUA" << endl; 
	for (int i=1; i<=l.soluong; i++){
		if (strcmp(l.DSMayBay[i]->sohieuMB,soHieu_tam) == 0) {
			cout << "So hieu: " << l.DSMayBay[i]->sohieuMB << endl;
			cout << "Loai: " << l.DSMayBay[i]->loai << endl;
			cout << "Soday: " << l.DSMayBay[i]->soday << endl;
			cout << "Sodong: " << l.DSMayBay[i]->sodong << endl;
			cout << "==============================================================================================" << endl << endl;
			vitri=i;
		}
	}
		char temp_sohieuMB[15], loai[40];
		string sodong_tam,soday_tam;
		//nhap so hieu can sua
		sohieuMB:
		cout << "So hieu may bay: "; 	
		fflush(stdin);
		gets(temp_sohieuMB);
		//sohieuMB ko chua khoang trang
		InHoa(temp_sohieuMB);
		if(strlen(temp_sohieuMB) == 0) return;
		if (KiemTraKhoangTrang(temp_sohieuMB) == 0  || KiemTraKiTu(temp_sohieuMB) ==0 ) {
			cout << "ERROR: SO HIEU KHONG CHUA KHOANG TRANG!!! MOI NHAP LAI" << endl;
			goto sohieuMB;
		}
		//kiem tra trung	
		if((KiemTraSoHieuMB(l,temp_sohieuMB) == 1) && (strcmp(l.DSMayBay[vitri]->sohieuMB,temp_sohieuMB)!=0))  {
			cout << "ERROR: SO HIEU DA CO!!! MOI NHAP LAI";
			goto sohieuMB;
		};		
		loai:
		fflush(stdin);
		cout << "Loai: " ; 
		gets(loai);
		InHoa(loai);
		if (strlen(loai) == 0) return;
		if( KiemTraKiTu(loai) == 0) {
			cout << "ERROR: NHAP SAI!!! MOI NHAP LAI";
			goto loai;
		};	
		soday:
		cout << "So day: "; 
		getline(cin,soday_tam);
		if(strlen(soday_tam.c_str()) == 0) return;
		if ( KiemTraSo(soday_tam) == 0) {
			cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
			goto soday;
		}
		sodong:
		cout << "Sodong: "; 
		getline(cin,sodong_tam);
		if ( KiemTraSo(sodong_tam.c_str()) == 0) {
			cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
			goto sodong;
		}
		// thay doi sodong cua may bay
		// atoi: chuyen ky tu thanh so
		strcpy(l.DSMayBay[vitri]->sohieuMB,temp_sohieuMB);
		strcpy(l.DSMayBay[vitri]->loai,loai); 
		l.DSMayBay[vitri]->soday = atoi(soday_tam.c_str());
		l.DSMayBay[vitri]->sodong = atoi(sodong_tam.c_str());	
}
// menue danh sach may bay
void MenuDanhSachMayBay(DS_MAYBAY &l,DS_CHUYENBAY &listCB){
	int luachon=0;
	char chon[5];
	
	system("cls");
	cout << "\t\t\t ================= DANH SACH MAY BAY =================" << endl;
	// ham xuat list mb
	XuatDanhSach(l);
	// in ra
	cout << "THEM (T)		XOA(X)			SUA(S)			LUU(L)" << endl;
	// nhap lua chon
	cout << "Luachon: "; 
	cin >> chon;
	InHoa(chon);
	
	// chuyen lua chon sang so de su dung switch...case
	if ( strcmp(chon,"T")==0 ) luachon =1;
	if ( strcmp(chon,"X")==0 ) luachon=2;
	if ( strcmp(chon,"S")==0 ) luachon=3;
	if ( strcmp(chon,"L")==0 ) {
		SaveMB(l);
		system("cls");
		return;
	}
	// switch...case
	switch(luachon){
		case 1:{
			NhapThongTinMayBay(l);
			break;
		}
		case 2:{
			char masoMB[15];
			system("cls");
			XuatDanhSach(l);
			
			fflush(stdin);
			masoMB_c2:
			cout << "Nhap Ma So May Bay (Can Xoa): ";
			gets(masoMB);
			InHoa(masoMB);
			if(strlen(masoMB) == 0) break;
			if ( KiemTraSoHieuMB(l,masoMB) == 0 ){
				cout << "ERROR: Ma So Khong Ton Tai!!!!!!" << endl;
				goto masoMB_c2;
			}
			if (KiemTraMBDaCoCB(listCB,masoMB) == 0){
				cout << "ERROR: May Bay Da Co Chuyen Bay! Xoa that bai!!" << endl;
				Sleep(1000);
				break;
			} 
			if (confirm() == 0) break;
			XoaMayBay(l,masoMB);
			system("cls");
			cout << "DA XOA!!!!";
			Sleep(1000);
			break;
		}
		case 3:{
			char masoMB[15];
			system("cls");
			XuatDanhSach(l);
			masoMB_c3:
			fflush(stdin);
			cout << "Nhap So Hieu May Bay (Can Sua): ";
			gets(masoMB); 
			InHoa(masoMB);
			if(strlen(masoMB) == 0) break;
			if (KiemTraSoHieuMB(l,masoMB) == 0 ){
				cout << "ERROR: Ma So Khong Ton Tai!!!!!!" << endl;
				goto masoMB_c3;
			}
			if (KiemTraMBDaCoCB(listCB,masoMB) == 0){
				cout << "ERROR: May Bay Da Co Chuyen Bay! Sua that bai!!" << endl;
				Sleep(1000);
			} else ChinhSuaMayBay(l,masoMB);
			break;
		}
		default: MenuDanhSachMayBay(l,listCB);
}
	MenuDanhSachMayBay(l,listCB);
}

void LoadMB(DS_MAYBAY &l){
	ifstream readfile;
	readfile.open("MayBay.txt", ios::out);
	
	char sohieuMB[15],loai[30];
	int soday, sodong, i;
	readfile >> i;
	while(i > 0){
		readfile >> sohieuMB;
		readfile >> loai; 
		readfile >> soday;
		readfile >>	sodong;
		i--;
		ThemMayBay(l,sohieuMB,loai,soday,sodong);
	}
	readfile.close();
}
///////////////////////////////////////////////////////////////////////////////////////
//b
//ctdl

//chuyen tu cay nhi phan sang mang
void ChuyenDoi(DS_HANHKHACH  *listHK,HANHKHACH hk[],int &i){
	if (listHK!=NULL) {
		strcpy(hk[i].cmnd , listHK->hanhkhach.cmnd);
		hk[i].ho = listHK->hanhkhach.ho;
		hk[i].ten=listHK->hanhkhach.ten;
		hk[i].phai = listHK->hanhkhach.phai;
		i++;
		ChuyenDoi(listHK->left,hk,i);
		ChuyenDoi(listHK->right,hk,i);
	}
}
	
//save hanh khach tat ca chuyen bay
//*****
void SaveHK(DS_HANHKHACH *dshk, ofstream &savefile){
	// DS_HANHKHACH *temp;
	// while(dshk){
	// 	if (dshk->left==NULL){
	// 				cout << dshk->hanhkhach.cmnd << endl;
	// 				savefile << dshk->hanhkhach.cmnd << endl;
	// 				savefile << dshk->hanhkhach.ho << endl;
	// 				savefile << dshk->hanhkhach.ten << endl;
	// 				savefile << dshk->hanhkhach.phai << endl;
	// 				dshk = dshk->right;
	// 	} else {
	// 		temp = dshk->left;
	// 		while(temp->right && temp->right != dshk){
	// 			temp = temp->right;
	// 		}
	// 		if(temp->right == NULL){
	// 			    temp->right = dshk;
	// 			    cout << dshk->hanhkhach.cmnd << endl;
	// 				savefile << dshk->hanhkhach.cmnd << endl;
	// 				savefile << dshk->hanhkhach.ho << endl;
	// 				savefile << dshk->hanhkhach.ten << endl;
	// 				savefile << dshk->hanhkhach.phai << endl ;
	// 		     	dshk = dshk->left;
	// 		}
	// 		else{
	// 			temp->right = NULL;
	// 			dshk = dshk->right;
	// 		}
	// 	}
	// }
	if (dshk!=NULL) {
		savefile << dshk->hanhkhach.cmnd << endl;
		savefile << dshk->hanhkhach.ho << endl;
		savefile << dshk->hanhkhach.ten << endl;
		savefile << dshk->hanhkhach.phai << endl;
		SaveHK(dshk->left, savefile);
		SaveHK(dshk->right, savefile);
	}
	//  PreOrder(dshk);
}

//save ticket
void SaveTK(CHUYENBAY *cb){
	
	ofstream savefile;
	char fileName[100];
	strcpy(fileName,"TICKET"); 
	strcat(fileName,cb->machuyenbay);
	strcat(fileName,".txt");
	savefile.open(fileName,ios::out);
	for (int i=1; i<=cb->soLuongVe; i++){
		savefile << cb->ve[i]->cmnd << endl;
		savefile << cb->ve[i]->soDay << endl;
		savefile << cb->ve[i]->soDong << endl;
	}
	savefile.close();
}


void SaveCB(DS_CHUYENBAY &l,DS_HANHKHACH *listHK, DS_MAYBAY &listMB){

	ofstream savefile;
	savefile.open("ChuyenBay.txt", ios::out);
	savefile << l.soluong << endl; 
	for(CHUYENBAY *k=l.pFirst; k!=NULL; k=k->next){
		int gioiHanSoVe;
		MAYBAY *tempMB = new MAYBAY;
		for (int i=1; i<= listMB.soluong; i++){
				if ( strcmp(listMB.DSMayBay[i]->sohieuMB,k->sohieuMB) == 0) {
					gioiHanSoVe = listMB.DSMayBay[i]->soday*listMB.DSMayBay[i]->sodong;
					break;
				}
		}
		savefile << k->machuyenbay << endl;
		savefile << k->date.ngay << endl << k->date.thang << endl << k->date.nam << endl;
		savefile << k->time.gio << endl << k->time.phut << endl;
		savefile << k->sanbayden << endl;
		savefile << k->sohieuMB << endl;
		if (k->soLuongVe>=gioiHanSoVe) {
			k->trangthai=2;
		}
		if (KiemTraCoPhaiLaQuaKhu(k->date.ngay, k->date.thang, k->date.nam, k->time.gio, k->time.phut) && k->trangthai!=0) {
			k->trangthai=3;
		}
		savefile << k->trangthai << endl;
		savefile << k->soLuongVe << endl;
		SaveTK(k);
	}
	
	savefile.close();
}

int KiemTraCoPhaiLaQuaKhu(int ngay, int thang, int nam, int gio, int phut) {
	time_t now;
	time(&now);
	struct tm thoiGianCanCheck;
	thoiGianCanCheck.tm_year=nam-1900;
	thoiGianCanCheck.tm_mon=thang-1;
	thoiGianCanCheck.tm_mday=ngay;
	thoiGianCanCheck.tm_hour=gio;
	thoiGianCanCheck.tm_min=phut;
	thoiGianCanCheck.tm_sec=0;
	time_t thoiGianCanCheck_time = mktime(&thoiGianCanCheck);
	if (thoiGianCanCheck_time<now) {
		return 1;
	}
	return 0;
}

int KiemTraNamNhuan(int year){
//	chia het cho 4  
// AND khong chia het cho 100. 
// OR chia het cho 400.
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
				return 1;
		}
		return 0;
}

int KiemTraDate(int ngay,int thang, int nam,int gio, int phut){
	// if ( ngay >31 || ngay <0) return 0;
	// if  (thang > 12 || thang <0) return 0;
	// if (nam < 2020) return 0;
	// if ( ngay==29 && thang==2 && KiemTraNamNhuan(nam)==0 ) return 0;
	if (gio > 23 || gio<0) return 0;
	if (phut > 60 || phut <0) return 0;
	if (thang < 1 || thang > 12) 
    return 0; 
    if (ngay < 1 || ngay > 31) 
    return 0; 
  
    // Kiem tra ngay thang 2  
    if (thang == 2) 
    { 
        if (KiemTraNamNhuan(nam)) 
        return (ngay <= 29); 
        else
        return (ngay <= 28); 
    } 
  
    // thang 4,6,9,11 chi co 30 ngay
    if (thang == 4 || thang == 6 || 
        thang == 9 || thang == 11) {
         if (ngay>30) return 0;
				}

	return 1;
}
void ThemNodeChuyenBay(DS_CHUYENBAY &l,CHUYENBAY *tempCB){
		CHUYENBAY *t = new CHUYENBAY;
		CHUYENBAY *s = NULL;
		
		// chay den phan tu cuoi cung
		for (s=l.pFirst; s!=NULL && strcmp(s->machuyenbay,tempCB->machuyenbay) < 0  ; t=s,s=s->next);
	
			if ( s == l.pFirst){
					tempCB->next = l.pFirst;
					l.pFirst = tempCB;
					l.pLast = tempCB;
			} else if( s == l.pLast){
					l.pLast->next = tempCB;
					l.pLast = tempCB;
			} else
				{
							  {
								tempCB->next = s;
								t->next = tempCB;
							}
				}
}
int SoSanhDate(Date d1, Date d2){
	if (d1.ngay != d2.ngay || d1.thang != d2.thang || d1.nam != d2.nam ) return 0;
	return 1;
}
int KiemTraMaCBTrongChuyenBay(DS_CHUYENBAY &listCB,CHUYENBAY *chuyenbay){
		for (CHUYENBAY *i = listCB.pFirst; i!=NULL; i=i->next){
			// so sanh neu trong cung mot ngay, cung mot khung gio, thoi gian cua moi may bay phai cach nhau 3h
			if ( strcmp(i->sohieuMB,chuyenbay->sohieuMB) == 0 && SoSanhDate(i->date,chuyenbay->date) && abs(i->time.gio - chuyenbay->time.gio) <3){
					return 1;
			} 
		}
		return 0;
}
int KiemTraTrungMaCB(DS_CHUYENBAY &listCB,char *machuyenbay){
		for (CHUYENBAY *i = listCB.pFirst; i!=NULL; i=i->next){
				if (strcmp(i->machuyenbay,machuyenbay) == 0) {
					return 1;
				}
		}
		return 0;
}
int ChuyenBayCoTheXoaSua(DS_CHUYENBAY &listCB,char *machuyenbay){
		for (CHUYENBAY *i = listCB.pFirst; i!=NULL; i=i->next){
				if (strcmp(i->machuyenbay,machuyenbay) == 0 && i->soLuongVe == 0 && i->trangthai!=3) {
					return 1;
				} 
		}
		return 0;
}
int ChuyenBayDatVe(DS_CHUYENBAY &listCB,char *machuyenbay){
		for (CHUYENBAY *i = listCB.pFirst; i!=NULL; i=i->next){
				if (strcmp(i->machuyenbay,machuyenbay) == 0 && i->trangthai != 2 && i->trangthai!=3) {
					return 1;
				} 
		}
		return 0;
}
int ChuyenBayDaHoanTat(DS_CHUYENBAY &listCB,char *machuyenbay){
		for (CHUYENBAY *i = listCB.pFirst; i!=NULL; i=i->next){
				if (strcmp(i->machuyenbay,machuyenbay) == 0 && i->trangthai != 2 && i->trangthai!=3) {
					return 1;
				} 
		}
		return 0;
}
void ThemChuyenBay(DS_CHUYENBAY &l,DS_MAYBAY &maybay){
	char maCB[15],loai[100],sanbayden[100],sohieuMB[15];
	system("cls");
	CHUYENBAY *tempCB = new CHUYENBAY; 
	l.soluong++;
	fflush(stdin);
	
	// xuat ra dsach may bay de lua chon cho chuyen bay
	gotoxy(35,1);
	cout << "DANH SACH MAY BAY HIEN DANG CO" << endl;
	XuatDanhSach(maybay);
	chuyenbay:
	cout << "Nhap Ma Chuyen Bay: ";
	fflush(stdin);
	gets(maCB);
	InHoa(maCB);
	// kt khoang trang 
	if(strlen(maCB) == 0) return;
	if(KiemTraKhoangTrang(maCB) == 0 || strlen(maCB) ==0 || KiemTraKiTu(maCB) == 0){
		cout << "ERROR: Khong duoc chua khoang trang hoac bo trong!!!" << endl;
		goto chuyenbay;
	}
	if(KiemTraTrungMaCB(l,maCB)){
		cout << "Ma Chuyen Bay Bi Trung!" << endl;
		goto chuyenbay;
	}
	strcpy(tempCB->machuyenbay,maCB);
	/////////////
	char ngay[10],thang[10],nam[10],gio[10],phut[10];
	time:
	cout << "Nhap Ngay Gio Khoi Hanh" << endl;
	ngay:
	cout << "Ngay: "; 
	fflush(stdin); 
	gets(ngay);
	if(strlen(ngay) == 0) return;
	if(KiemTraSo(ngay) == 0 || atoi(ngay) > 31 || atoi(ngay) <0){
		cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
		goto ngay;
	}
	thang:
	cout << "Thang: "; 
	fflush(stdin); 
	gets(thang);
	if(strlen(thang) == 0) return;
    if(KiemTraSo(thang) == 0 || atoi(thang) > 12 ||  atoi(thang) <0){
		cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
		goto thang;
	}
	nam:
	cout << "Nam: ";
	fflush(stdin); 
	gets(nam);
	if(strlen(nam) == 0 ) return;
	if( KiemTraSo(nam) == 0 || (atoi(ngay)==29 &&  atoi(thang)==2 && KiemTraNamNhuan(atoi(nam))==0)){
		cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
		goto nam;
	}
	gio:
	cout << "Gio: ";
	fflush(stdin);  
	gets(gio);
	if(strlen(gio) == 0) return;
	if(KiemTraSo(gio) == 0 || atoi(gio) > 23 || atoi(gio) <0){
		cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
		goto gio;
	}
	phut:
	cout << "Phut: ";
	fflush(stdin);  
	gets(phut);
	if(strlen(phut) == 0) return;
	if(KiemTraSo(phut) == 0 || atoi(phut) > 60 || atoi(phut) <0){
		cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
		goto phut;
	}
	if (KiemTraDate(atoi(ngay), atoi(thang), atoi(nam) ,atoi(gio), atoi(phut))==0) {
		goto time;
	}
	if (KiemTraCoPhaiLaQuaKhu(atoi(ngay), atoi(thang), atoi(nam) ,atoi(gio), atoi(phut))) {
		cout << "ERROR: KHONG THE TAO CHUYEN BAY TRONG QUA KHU!!!" << endl;
		goto time;
	}
	tempCB->date.ngay = atoi(ngay);
	tempCB->date.thang = atoi(thang);
	tempCB->date.nam = atoi(nam);
	tempCB->time.gio = atoi(gio);
	tempCB->time.phut = atoi(phut);
	
	sanbayden:
	cout << "Nhap San Bay Den: ";
	fflush(stdin);
	gets(sanbayden);
	InHoa(sanbayden);
	if (strlen(sanbayden) == 0) return;
	if(KiemTraKhoangTrang(sanbayden)== 0 || KiemTraKiTu(sanbayden) == 0){
		cout << "ERROR: Khong duoc chua khoang trang hoac bo trong!!!" << endl << "Moi nhap lai!!!" << endl << endl;
		goto sanbayden;
	}
	strcpy(tempCB->sanbayden,sanbayden);
	
	tempCB->trangthai = STATUS_CB_CONVE;
	sohieuMB:
	fflush(stdin);
	cout << "Nhap so hieu MB: ";
	gets(sohieuMB);
	InHoa(sohieuMB);
	if(strlen(sohieuMB) == 0) return;
	 if(KiemTraKhoangTrang(sohieuMB)== 0 || strlen(sohieuMB) == 0 || KiemTraKiTu(sohieuMB) == 0){
		cout << "ERROR: Khong duoc chua khoang trang hoac bo trong!!!" << endl << "Moi nhap lai!!!" << endl << endl;
		goto sohieuMB;
	}
	// kiem tra sohieu da t
	 if (KiemTraSoHieuMB(maybay,sohieuMB) == 0 ){
		cout << "ERROR: SO HIEU MAY BAY KHONG TON TAI!!! MOI NHAP LAI" << endl;
		goto sohieuMB;
	}
	
	if(KiemTraMaCBTrongChuyenBay(l,tempCB)){
		cout << endl << "ERROR: May Bay Da Co Lich Trinh!!Nhap Lai..*" << endl << "ERROR: Moi May Bay Phai Bay Cach Nhau 3h*" << endl << endl;
		goto sohieuMB;
	}
	strcpy(tempCB->sohieuMB,sohieuMB);
	 // dsach hanh khach	
	ThemNodeChuyenBay(l,tempCB);

}
void XuatChuyenBay(DS_CHUYENBAY &l){
	system("cls");
	cout <<"		DANH SACH CHUYEN BAY" << endl ;
	for (CHUYENBAY *k=l.pFirst; k!=NULL; k=k->next){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),WHITE);
		cout << "=============================================================" << endl;
		cout << "Ma Chuyen Bay: "<<k->machuyenbay << endl;
		cout << "Thoi Gian: " << k->time.gio << "h:" << k->time.phut << "'" << "			Ngay: " << k->date.ngay << "/" << k->date.thang << "/" << k->date.nam << endl;
		cout << "Den San Bay: " << k->sanbayden << endl;
		cout << "So Hieu May Bay: " <<k->sohieuMB << endl;
		cout << "Trang Thai: ";
		if (k->trangthai == 1) {
			//doi mau chu
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			cout << "Con Ve";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		else if (k->trangthai == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),RED);
			cout << "Het Ve";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		else if (k->trangthai == 3){
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),GREEN);
			cout << "Hoan Tat";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	} else if (k->trangthai == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),RED);
		cout << "Chuyen Bay Bi Huy";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
		cout << endl;
	}
	cout << "=============================================================================" << endl;
}
void XoaChuyenBay(DS_CHUYENBAY &listCB, char *machuyenbay){
	CHUYENBAY *t;
	
	if (listCB.pFirst == NULL) return;
	
	if ( strcmp(listCB.pFirst->machuyenbay,machuyenbay) == 0) {
		t = listCB.pFirst;
		listCB.pFirst = listCB.pFirst->next;
		listCB.soluong--;
		delete t;
	} else
	// chay for tim phan tu
	for (CHUYENBAY *i=listCB.pFirst; i!=NULL;t=i, i = i->next){
		if (strcmp(i->machuyenbay,machuyenbay) == 0) {
			if (i == listCB.pLast){
				t->next = i->next;
				listCB.pLast = t;
				listCB.soluong--;
				delete i;
				break;
			} else {
				t->next = i->next;
				listCB.soluong--;
				delete i;
				break;
			}
		}
	}
	
	// xoa file danh sach ve
	char fileName[100]="TICKET";
	strcat(fileName,machuyenbay);
	strcat(fileName,".txt");
	remove(fileName);
}
void ChinhSuaChuyenBay(DS_CHUYENBAY &listCB, char *machuyenbay){
	cout << endl;
	int chon;
	system("cls");
	// in thong tin may bay can sua
	for (CHUYENBAY *k = listCB.pFirst; k!=NULL; k++){
				if ( strcmp(k->machuyenbay,machuyenbay) == 0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),WHITE);
				cout << "Ma Chuyen Bay: "<<k->machuyenbay << endl;
				cout << "Thoi Gian: " << k->time.gio << "h:" << k->time.phut << "'" << "			Ngay: " << k->date.ngay << "/" << k->date.thang << "/" << k->date.nam << endl;
				cout << "Den San Bay: " << k->sanbayden << endl;
				cout << "So Hieu May Bay: " <<k->sohieuMB << endl;
				cout << "Trang Thai: ";
				if (k->trangthai == 1) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
					cout << "Con Ve";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
				else if (k->trangthai == 2) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),RED);
					cout << "Het Ve";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
				else if (k->trangthai == 3){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),GREEN);
					cout << "Hoan Tat";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			} else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),RED);
				cout << "Chuyen Bay Bi Huy";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
				cout << endl;
			}	
		cout << "=================================================" << endl;
		cout << "1. Sua Thoi Gian Khoi Hanh." << endl << "2. Huy Chuyen."<<endl <<"3. Thoat" << endl;
		cout << "Nhap lua chon: " << endl; cin >> chon;
		
		while( chon!= 1 && chon != 2 && chon !=3 ){
			cout << "Nhap sai!!! "<< endl;
			cout << "Nhap lua chon: " ; cin >> chon;
		}
		switch(chon){
			case 1:{
				char ngay[10],thang[10],nam[10],gio[10],phut[10];
				time:
				cout << "Nhap Ngay Gio Khoi Hanh" << endl;
				ngay:
				cout << "Ngay: ";
				fflush(stdin); 
				gets(ngay);
				if(strlen(ngay) == 0) return;
				if(KiemTraSo(ngay) == 0 || atoi(ngay) > 31 || atoi(ngay) <0){
					cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
					goto ngay;
				}
				thang:
				cout << "Thang: "; 
				fflush(stdin); 
				gets(thang);
				if(strlen(thang) == 0) return;
			    if(KiemTraSo(thang) == 0 || atoi(thang) > 12 ||  atoi(thang) <0){
					cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
					goto thang;
				}
				nam:
				cout << "Nam: ";
				fflush(stdin); 
				gets(nam);
				if(strlen(nam) == 0 ) return;
				if( KiemTraSo(nam) == 0 || (atoi(ngay)==29 &&  atoi(thang)==2 && KiemTraNamNhuan(atoi(nam))==0 || atoi(nam) < 2020)){
					cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
					goto nam;
				}
				gio:
				cout << "Gio: "; 
				fflush(stdin); 
				gets(gio);
				if(strlen(gio) == 0) return;
				if(KiemTraSo(gio) == 0 || atoi(gio) > 24 || atoi(gio) <0){
					cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
					goto gio;
				}
				phut:
				cout << "Phut: ";
				fflush(stdin);  
				gets(phut);
				if(strlen(phut) == 0) return;
				if(KiemTraSo(phut) == 0 || atoi(phut) > 60 || atoi(phut) <0){
					cout << "ERROR: NHAP SAI!!! MOI NHAP LAI" << endl;
					goto phut;
				}
				k->date.ngay = atoi(ngay);
				k->date.thang = atoi(thang);
				k->date.nam = atoi(nam);
				k->time.gio = atoi(gio);
				k->time.phut = atoi(phut);	
				break;
			}
			case 2:{
				k->trangthai = 0;
				return;
			}
			case 3: return;
		}
			
			
	}
	
}
// 0: khong ton tai cb
int KiemTraMaCB(DS_CHUYENBAY &l,char maCB[]){
	
	for (CHUYENBAY *k=l.pFirst; k!=NULL; k=k->next){
		if ( strcmp(k->machuyenbay,maCB) == 0 ) return 1;
	}
	return 0;
}


void ThemVe(CHUYENBAY *&cb,char cmnd[],int soDong,int soDay){
	cb->soLuongVe++;
	cb->ve[cb->soLuongVe] = new TICKET;
	strcpy(cb->ve[cb->soLuongVe]->cmnd,cmnd);
	cb->ve[cb->soLuongVe]->soDay = soDay;
	cb->ve[cb->soLuongVe]->soDong = soDong;
}
//load
void LoadTK(CHUYENBAY *&cb){
	ifstream readfile;
	char fileName[100];
	strcpy(fileName,"TICKET");
	strcat(fileName,cb->machuyenbay);
	strcat(fileName,".txt");
	
	readfile.open(fileName,ios::in);
	for (int i=1; i<= cb->soLuongVe; i++){
		cb->ve[i] = new TICKET;
		readfile >> cb->ve[i]->cmnd;
		readfile >> cb->ve[i]->soDay;
		readfile >> cb->ve[i]->soDong;
	}	
	readfile.close();
}
void LoadCB(DS_CHUYENBAY &l){
	ifstream readfile;
	readfile.open("ChuyenBay.txt", ios::in);
	readfile >> l.soluong;
	for (int i=1; i<=l.soluong; i++){
		CHUYENBAY *tempCB = new CHUYENBAY;
		// struct tm thoiGianCB;
	  // thoiGianCB.tm_year = tempCB->date.nam - 1900;
		// now = mktime(&thoiGianCB);
		// cout << ctime(&now);

		readfile >> tempCB->machuyenbay;
		readfile >>  tempCB->date.ngay;
		readfile >>  tempCB->date.thang; 
		readfile >>  tempCB->date.nam; 
		readfile >>  tempCB->time.gio;
		readfile >>  tempCB->time.phut;
		readfile >>  tempCB->sanbayden;
		readfile >>  tempCB->sohieuMB;
		readfile >>  tempCB->trangthai;
		readfile >> tempCB->soLuongVe;
		if (KiemTraCoPhaiLaQuaKhu(tempCB->date.ngay, tempCB->date.thang, tempCB->date.nam, tempCB->time.gio, tempCB->time.phut) && tempCB->trangthai!=0) {
			tempCB->trangthai=3;
		}
		LoadTK(tempCB);
		ThemNodeChuyenBay(l,tempCB);
	}
	readfile.close();
}
void LoadHK(DS_HANHKHACH *&listHK){
	HANHKHACH hk ;
	ifstream readfile;
	
		readfile.open("HANHKHACH.txt",ios::in);
		if(readfile.fail()) return;
		if ( readfile.peek() == std::ifstream::traits_type::eof() ) return;

		while(1)
		{
			if(readfile.eof()) break;
			readfile >> hk.cmnd;
			readfile >> hk.ho;
			readfile >> hk.ten;
			readfile >> hk.phai;
			Insert_BST(listHK,hk);
		}	
	readfile.close();
}

void MenuDanhSachChuyenBay(DS_CHUYENBAY &l,DS_HANHKHACH *listHK, DS_MAYBAY &maybay){
	y:
	char chon[5];
	int luachon;
	XuatChuyenBay(l);
	cout << "Them (T)		Xoa(X)			Sua(S)			Luu(L)" << endl;
	cout << "Nhap lua chon: ";
	fflush(stdin);
	gets(chon);
	InHoa(chon);
	if (strlen(chon)==0) return;

	if (strcmp(chon,"T") == 0) luachon = 1;
	else if (strcmp(chon,"X") == 0) luachon = 2;
	else if (strcmp(chon,"S") == 0) luachon = 3;
	else if (strcmp(chon,"L") == 0) {
		SaveCB(l,listHK, maybay);
		return;
	} else goto y;
	
	switch (luachon){
		case 1:{
			ThemChuyenBay(l,maybay);
			break;
		}
		case 2:{
			char maCB[15];
		  XuatChuyenBay(l);
			cout << "Nhap (Thoat) de tro lai. " << endl;
			t:  cout << "Nhap ma chuyen bay can xoa: "; 
			fflush(stdin);
			gets(maCB);
			InHoa(maCB);	
			if(strcmp(maCB,"THOAT")==0) break;	
			switch (KiemTraMaCB(l,maCB)==0 ? 1 : 0 | ChuyenBayCoTheXoaSua(l, maCB)==0 ? 2 : 0)
			{
			case 1:  
					std::cout << ">>> Chuyen bay khong ton tai!!! Moi nhap lai: " << std::endl;
					Sleep(500);
					goto t;
					break; // skipped
			case 2: // Match!
					std::cout << ">>> Khong the XOA, do chuyen bay da co khach DAT VE hoac DA HOAN TAT !!!" << std::endl;
					Sleep(500);
					goto t;
			}
			XoaChuyenBay(l,maCB);
			break;
		}
		case 3:{
			char maCB[15];
			XuatChuyenBay(l);
			cout << "Nhap (Thoat) de tro lai. " << endl;
			x: cout << "Nhap ma chuyen bay can sua: "; 
			fflush(stdin);
			gets(maCB);
			InHoa(maCB);	
			if(strcmp(maCB,"THOAT")==0) break;
			// kiem tra maCB co ton tai		
			// if (KiemTraMaCB(l,maCB)==0) {
			// 	std::cout << ">>> Chuyen bay khong ton tai!!! Moi nhap lai: " << std::endl;
			// 	Sleep(500);
			// 	goto x	;
			// }
			// if (==0) {
			// 	std::cout << ">>> Khong the chinh sua, do chuyen bay da co khach dat ve!!!" << std::endl;
			// 	Sleep(500);
			// 	goto x	;
			// }
			switch (KiemTraMaCB(l,maCB)==0 ? 1 : 0 | ChuyenBayDatVe(l, maCB)==0 ? 2 : 0)
			{
			case 1:  
					std::cout << ">>> Chuyen bay khong ton tai!!! Moi nhap lai: " << std::endl;
					Sleep(500);
					goto x;
					break; // skipped
			case 2: // Match!
					std::cout << ">>> Khong the chinh sua, do chuyen bay da co khach DAT VE hoac DA HOAN TAT !!!" << std::endl;
					Sleep(500);
					goto x;
			}
			ChinhSuaChuyenBay(l,maCB);
			break;
		}
			
	}
	MenuDanhSachChuyenBay(l,listHK,maybay);

}

//c
int NhapThongTinHK(HANHKHACH &hanhkhach){
	system("cls");	
	char ho[50],ten[50],phai[50];
	HinhVuong(30,10,85,25);
	gotoxy(25,26);
	cout << "_ Ho, Ten, Phai khong duoc chua khoang trang hay bo trong. ";
	gotoxy(25,27);
	cout << "_ CMND phai la so. " ;
	gotoxy(42,13);
	cout << "===NHAP THONG TIN HANH KHACH MOI===";
  gotoxy(35,15);
	cout<<"CMND: " << hanhkhach.cmnd;
x:	gotoxy(35,17);
	cout <<"Ho: ";
	fflush(stdin);
	gets(ho);
	InHoa(ho);
	if(strlen(ho) == 0)	return 0;
	
	if(KiemTraKiTu(ho) == 0){
		gotoxy(35,17);
		cout << "                        ";
		goto x;
	}
	hanhkhach.ho = ho;
	
y:	gotoxy(35,19);
	cout <<"Ten: ";
	fflush(stdin);
	gets(ten);
	InHoa(ten);
	if(strlen(ten) == 0) return 0;
	if(KiemTraKiTu(ten) == 0){
		gotoxy(35,19);
		cout << "                     ";
		goto y;
	}
	hanhkhach.ten = ten;
	
	
z:	gotoxy(35,21);
	cout<<"Phai (NAM/NU): ";
	gets(phai);
	InHoa(phai);
	if(strlen(phai) == 0) return 0;
	if(KiemTraKhoangTrang(phai)==0  ){
		gotoxy(35,21);
		cout << "                     ";
		goto z;
	}
	
	if( strcmp(phai,"NAM") != 0 && strcmp(phai,"NU") !=0){
		gotoxy(35,21);
		cout << "                     ";
		goto z;
	}
	hanhkhach.phai = phai;
	return 1;
}

void XuatChuyenBayTrongDSV(DS_CHUYENBAY &listCB){
	int stt=0;
	
	cout << "STT" << setw(10) << "MaCB" << setw(22) << "NoiDen" << setw(30)<< "ThoiGian" << setw(30) << "TrangThai" << endl;

	for (CHUYENBAY *k = listCB.pFirst; k!=NULL; k=k->next){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			cout <<++stt << setw(10) <<  k->machuyenbay << setw(22) << k->sanbayden << setw(18) <<"("<< k->time.gio << ":" << k->time.phut << ") " << k->date.ngay<<
			"-" << k->date.thang << "-" << k->date.nam << setw(27);
			if (k->trangthai == 1) {
			//doi mau chu
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			cout << "Con Ve";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		else if (k->trangthai == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),RED);
			cout << "Het Ve";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		else if (k->trangthai == 3){
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),GREEN);
			cout << "Hoan Tat";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	} else if (k->trangthai == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),RED);
		cout << "Chuyen Bay Bi Huy";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	cout << endl;
	}
	cout << "===================================================================================================" << endl;
}

void DatVe(DS_CHUYENBAY &listCB,DS_HANHKHACH *&listHK, DS_MAYBAY &listMB,CHUYENBAY *cb,HANHKHACH hanhkhach,char soVe[]){
	int soDay=0,soDong=0;
	char tam,soDay_tam[100]={},soDong_tam[100]={};

	for (int i=0; i<strlen(soVe); i++){
		if ( int(int(soVe[i]) >=ASCII_0 and int(soVe[i]) <= ASCII_9) ){
			tam = soVe[i];  
			strcat(soDong_tam,&tam);
			continue;
		}
		//doi chu ra so day
		tam = (char) ((int)soVe[i]-16);  
		strcat(soDay_tam,&tam);
	}
	// chuyen ky tu thanh int
	soDay = atoi(soDay_tam);
	soDong = atoi(soDong_tam);
	
	//them ve vao trong chuyen bay
	Insert_BST(listHK,hanhkhach);
	// them ve vao chuyen bay
	ThemVe(cb,hanhkhach.cmnd,soDong,soDay);
	// them ve vao trong listHK
	SaveCB(listCB,listHK,listMB);
	ofstream savefile;
	savefile.open("HANHKHACH.txt", ios::out);
	SaveHK(listHK, savefile);
	savefile.close();
	system("cls");
	std::cout << "=> DAT VE THANH CONG! CHUONG TRINH SE TU DONG QUAY VE MENU CHINH." << std::endl;
	Sleep(3000);
}
// ve da ton tai return 1;	
int KiemTraGheTrong(TICKET *arr[],int &soLg,int soday,int sodong){
	//n = solg ve
	if (soLg==0) return 0; 
	for (int i=1; i<=soLg; i++){
		if ( (arr[i]->soDong == sodong) and (arr[i]->soDay==soday)){
			return 1;
		}
	}
	return 0;
}
int KiemTraVeDat(CHUYENBAY *tempCB,MAYBAY *tempMB,char soVe[],char cmnd[]){
	//de tach phan doi ve thanh so dong, so day
	int soDay=0,soDong=0;
	char tam,soDay_tam[100]={},soDong_tam[100]={};
	//A3
	for (int i=0; i<strlen(soVe); i++){		
		if ( int(soVe[i]) >=48 and int(soVe[i]) <= 57) {
			tam = soVe[i];
			//
			strcat(soDong_tam,&tam);
			continue;
		}
		//doi chu ra so day: 
		tam = (char) ((int)soVe[i]-16); 
		strcat(soDay_tam,&tam);
	} 
	//tim ra duoc vitri ghe ngoi khach dat
	//soday = 1, sodong = 3
	///////////////////////////////////////////////////////
	//1: ghe khong tontai
	//2: ghe da duoc dat
	//3: hanh khach da co mat trong chuyen bay
	//0: so ve hop le
	soDay = atoi(soDay_tam);
	soDong = atoi(soDong_tam); 
	// kiem tra so day cho phep cua maybay
	if (soDay > tempMB->soday || soDay < 1) return 1;
	// kiem tra so day cho phep cua maybay
	if (soDong > tempMB->sodong || soDong <1 ) return 1;
	
	// kiem tra ghe da ton tai
	for (int i=1; i<= tempCB->soLuongVe; i++){ 
		if ( (tempCB->ve[i]->soDong == soDong) and (tempCB->ve[i]->soDay==soDay)){
			return 2;
		}
	}
	// kiem tra cmnd da ton tai trong cb
	for (int i=1; i<= tempCB->soLuongVe; i++){
		if ( strcmp( tempCB->ve[i]->cmnd, cmnd) ==0 )  {
			return 3;
		}
	}
	return 0;
	
}

void XuatGheNgoi(DS_CHUYENBAY &listCB,DS_MAYBAY &listMB,DS_HANHKHACH *&listHK,HANHKHACH hanhkhach,char maCB[]){
	int soDay=0,soDong=0;
	char maMB[20];
	CHUYENBAY *tempCB = new CHUYENBAY;
	MAYBAY *tempMB = new MAYBAY;
	system("cls");
	
	//tim chuyen bay co maCB
	for (CHUYENBAY *k=listCB.pFirst; k!=NULL; k=k->next){
		if (strcmp(k->machuyenbay,maCB) == 0) {
			strcpy(maMB,k->sohieuMB);
			tempCB = k;
			break;
		}
	}
	gotoxy(35,10);
	cout << "========== MOI CHON GHE NGOI ==========" << endl;
	// tim so day so dong cua maybay
	for (int i=1; i<= listMB.soluong; i++){
		if ( strcmp(listMB.DSMayBay[i]->sohieuMB,maMB) == 0) {
			soDay = listMB.DSMayBay[i]->soday;
			soDong = listMB.DSMayBay[i]->sodong;
			tempMB = listMB.DSMayBay[i];
			break;
		}
	}
	// danh dau nhung ghe da dat
	for (int i=1; i<= soDay; i++)
		for (int j=1; j<=soDong; j++){
			gotoxy(8+i*15,13+j);
			// doi so sang A,B,C...
			cout << char (64+i) << j;
			if(KiemTraGheTrong(tempCB->ve,tempCB->soLuongVe,i,j) == 1){
				gotoxy(8+i*15,13+j);
				cout << "*****";
			}
		}
	cout << endl<< "==================================================================================================="<<endl;
	
	char soVe[15];
x:	cout << "Nhap (Thoat) de tro ve." << endl;
	cout << "Nhap vitri ghe: "; 
	gets(soVe);
	InHoa(soVe);
	if (strcmp(soVe,"THOAT")==0) return;
	
	while (KiemTraVeDat(tempCB,tempMB,soVe,hanhkhach.cmnd) != 0){
			switch(KiemTraVeDat(tempCB,tempMB,soVe,hanhkhach.cmnd)){
				case 1: {
					cout << endl<<"GHE KHONG TON TAI" << endl;
					goto x;	
					break;
				}
				case 2: {
					cout << endl<<"GHE DA CO NGUOI DAT" << endl;
					goto x;
					break;
				}
				case 3:{
					system("cls");
					cout << endl<<"HANH KHACH DA CO MAT TREN CHUYEN BAY";
					Sleep(1500);
					return;
				}
				default: goto x;	
			}		
	}
	DatVe(listCB,listHK,listMB,tempCB,hanhkhach,soVe);
}
void MenuDatVe(DS_CHUYENBAY &listCB,DS_MAYBAY &listMB,DS_HANHKHACH *&listHK){
	char maCB[15],soVe[15],cmnd[50];
	HANHKHACH *hanhkhach = new HANHKHACH;
	//nhap thong tin ve va tra ve
  system("cls");	
	HinhVuong(30,10,75,25);
	gotoxy(25,26);
	cout << "_ CMND phai la so. 9 hoac 12 chu so " ;
	gotoxy(42,13);
	cout << "===NHAP SO CMND===";
  a:	gotoxy(35,15);
	cout <<"CMND: ";
	fflush(stdin);
	gets(cmnd);
	InHoa(cmnd);
	if(strlen(cmnd) == 0)	return;
	
	if(KiemTraSo(cmnd) == 0 || (strlen(cmnd) != 9 && strlen(cmnd) != 12)){
		gotoxy(35,15);
		cout << "                        ";
		goto a;
	}
	if (HanhKhachCoTonTai(listHK, cmnd)) {
	Search_BTS(listHK,*hanhkhach,cmnd);
	} else {
		strcpy(hanhkhach->cmnd, cmnd);
		if(NhapThongTinHK(*hanhkhach) == 0) return;
	}
	system("cls");
	cout << "				=======THONG TIN HANH KHACH=======" << endl;
	InThongTinHanhKhach(*hanhkhach);
	cout << "				=======DANH SACH CHUYEN BAY=======" << endl;
	XuatChuyenBayTrongDSV(listCB);
x:	cout << "Nhap (THOAT) de tro ve" << endl;
	cout << "Nhap MaCB can dat: ";
	gets(maCB);
	InHoa(maCB);
	if(strcmp(maCB,"THOAT") == 0) return;
	switch (KiemTraMaCB(listCB,maCB)==0 ? 1 : 0 | ChuyenBayDatVe(listCB, maCB)==0 ? 2 : 0)
			{
			case 1:  
					std::cout << ">>> Chuyen bay khong ton tai!!! Moi nhap lai: " << std::endl;
					Sleep(500);
					goto x;
					break; // skipped
			case 2: // Match!
					std::cout << ">>> Khong the DAT VE, do chuyen bay da HET VE hoac DA HOAN TAT !!!" << std::endl;
					Sleep(500);
					goto x;
			}
	//datve trong xuatghengoi
	XuatGheNgoi(listCB,listMB,listHK,*hanhkhach,maCB);
}
//d
void HuyVe(DS_CHUYENBAY &listCB,DS_HANHKHACH *&listHK, DS_MAYBAY listMB){
	char maCB[100],tempCMND[15];
x:	system("cls");
	cout << "	        	==================== HUY VE =======================" ;
	HinhVuong(30,1,65,10);
	gotoxy(0,10);
	
	fflush(stdin);
	gotoxy(33,3);
	cout << "Nhap CMND: ";
	gets(tempCMND);
	if(strlen(tempCMND) == 0) return;
	if(KiemTraSo(tempCMND) == 0  || KiemTraKhoangTrang(tempCMND)==0 ){
		system("cls");
		cout << "CMND La So Va Khong Chua Khoang Trang";
		Sleep(1500);
		goto x;	
	}
	if (atoi(tempCMND)<1 || (strlen(tempCMND) != 9 && strlen(tempCMND) != 12) ){
		system("cls");
		cout << "CMND Khong Dung";
		Sleep(1000);
		goto x;
	}	
	fflush(stdin);
	gotoxy(33,7);
	cout <<"NHAP MA CHUYEN BAY: ";
	gets(maCB);
	InHoa(maCB);
	if(strlen(maCB) == 0) return;
	if(KiemTraKhoangTrang(maCB)==0 ){
		system("cls");
		cout << "Ma Chuyen Bay Khong Duoc chua Khong Trang Hoac Bo Trong";
		Sleep(1500);
		goto x;	
	}

	switch (KiemTraMaCB(listCB,maCB)==0 ? 1 : 0 | ChuyenBayDaHoanTat(listCB, maCB)==0 ? 2 : 0)
			{
			case 1:  
					system("cls");
					std::cout << ">>> Chuyen bay khong ton tai!!! Moi nhap lai: " << std::endl;
					Sleep(1000);
					goto x;
					break; // skipped
			case 2: // Match!
					system("cls");
					std::cout << ">>> Khong the HUY VE, do chuyen bay DA HOAN TAT !!!" << std::endl;
					Sleep(1000);
					goto x;
			}
	
	CHUYENBAY *tempCB;
	int check=1;
	// ERROR: Kiem tra trong chuyen bay co ton tai CMND can xoa
	for (tempCB = listCB.pFirst; tempCB!=NULL; tempCB=tempCB->next){
		if ( strcmp(tempCB->machuyenbay,maCB) == 0) {
			check = 0;
			break;
		}
	}
	if (check == 1){
		system("cls");
		cout << "Ve Hoac So CMND Khong Ton Tai Trong CB";
		Sleep(2000);
		return;
	}
	
	check =1;
	for(int i=1; i<= tempCB->soLuongVe; i++){
		if (strcmp(tempCB->ve[i]->cmnd, tempCMND) == 0) {
			check = 0;
			break;
		}
	}
	if (check == 1){
		system("cls");
		cout << "So CMND Khong Ton Tai";
		Sleep(2000);
		return;
	}
	
	//xoa hk
	listHK = XoaHanhKhach(listHK, tempCMND);
	// xoa ve
	for (int i=1; i<=tempCB->soLuongVe; i++){
		if(strcmp(tempCB->ve[i]->cmnd, tempCMND) == 0) {
			for (int j=i; j<tempCB->soLuongVe; j++){
				tempCB->ve[j] = tempCB->ve[j+1];
			}
			tempCB->soLuongVe--;
			break;
		}
	}
	
	SaveCB(listCB,listHK,listMB);
	ofstream savefile;
	savefile.open("HANHKHACH.txt", ios::out);
	SaveHK(listHK, savefile);
	savefile.close();
	system("cls");
	cout << "Da Huy Ve!!!" ;
	Sleep(1500);
}
//e
void InDanhSachHanhKhach(DS_CHUYENBAY &listCB,DS_HANHKHACH *&listHK){
	int stt=0;
	char maCB[15];
x:	system("cls");
	XuatChuyenBay(listCB);
	cout << "Nhap Ma Chuyen Bay: ";
	fflush(stdin);
	gets(maCB);
	InHoa(maCB);
	if(strlen(maCB)==0) return;
	if(KiemTraMaCB(listCB,maCB) == 0){
		system("cls");
		cout << "Ma Chuyen Bay Khong Ton Tai";
		Sleep(2000);
		return;
	}
	if(KiemTraKhoangTrang(maCB)==0){
		system("cls");
		cout << "Ma Chuyen Bay Khong Duoc Chua Khoang Trang Hoac Bo Trong";
		goto x;
	}
	CHUYENBAY *k;
	for (k=listCB.pFirst;k!=NULL;k=k->next){
		if ( strcmp(k->machuyenbay,maCB) == 0) break;
	}
	HANHKHACH *tempHK = new HANHKHACH;
	system("cls");
	cout << "	DANH SACH HANH KHACH THUOC CHUYEN BAY " << k->machuyenbay << endl << endl;
	cout << "Ngay Khoi Hanh: " << k->date.ngay <<"/" << k->date.thang <<"/" << k->date.nam << " " << k->time.gio << ":" << k->time.phut << "  Noi Den: " << k->sanbayden<<endl;
	cout << "STT" << setw(10) << "	SO VE" << setw(13) << "	CMND" << setw(10) << "	HOTEN" << setw(10) << "	PHAI" << endl;

	for (int i=1; i<= k->soLuongVe; i++){
		cout << i << setw(10) << char(k->ve[i]->soDay + 64) << k->ve[i]->soDong << setw(16) << k->ve[i]->cmnd << setw(16);
		Search_BTS(listHK,*tempHK,k->ve[i]->cmnd);
		cout << tempHK->ho <<" "<< tempHK->ten << setw(16) << tempHK->phai << endl;
	}
	
	char luachon[5];
	cout << "Nhap (THOAT) de tro ve: ";
	fflush(stdin);
	gets(luachon);
	InHoa(luachon);
	while(strcmp(luachon,"THOAT") !=0 ){
		cout << "Nhap (THOAT) de tro ve: ";
		fflush(stdin);
		gets(luachon);
		InHoa(luachon);
	}
}
//f
void TimKiemChuyenBay(DS_CHUYENBAY &listCB,DS_MAYBAY &listMB){
	char sanBayDen[100];
	Date date;
x:	system("cls");
	cout << "========TRA CUU CHUYEN BAY========" << endl;
	cout << "Nhap San Bay Den: ";
	gets(sanBayDen);
	InHoa(sanBayDen);
	if( strlen(sanBayDen)==0) return;
	while(KiemTraKhoangTrang(sanBayDen)==0){
		system("cls");
		cout << "TEN SAN BAY KHONG DUOC CHUA KHOANG TRANG HOAC BO TRONG !!!";
		Sleep(2000);
		goto x;
	}
	char ngay[10],thang[10],nam[10];
	cout << "== Nhap thoi gian =="<<endl;
	cout<<"Ngay: "; 	
	gets(ngay);
	if(strlen(ngay) == 0) return;
	cout << "Thang: "; 
	gets(thang);
	if(strlen(thang) == 0) return;
	cout << "Nam: "; 
	gets(nam);
	if(strlen(nam) == 0) return;
	date.ngay = atoi(ngay);
	date.thang = atoi(thang);
	date.nam = atoi(nam);
	int i;
	system("cls");
	cout << "Ma Chuyen Bay" << right << setw(13) << "Thoi Gian" << right <<setw(16) << "\tSo Luong" << endl;
	for (CHUYENBAY *k=listCB.pFirst; k!=NULL; k=k->next){
		if(SoSanhDate(date,k->date) && strcmp(k->sanbayden,sanBayDen) == 0){
			// tim kiem phan tu chuyen bay
			for( i=1; i<= listMB.soluong; i++){
				if (strcmp(k->sohieuMB,listMB.DSMayBay[i]->sohieuMB) == 0) break;
			}
			cout << k->machuyenbay << right << setw(13)<< "(" << k->time.gio <<":" << k->time.phut << ")" << k->date.ngay << "/" << k->date.thang << "/" << k->date.nam << right <<setw(16)
			<< (listMB.DSMayBay[i]->soday* listMB.DSMayBay[i]->sodong)- k->soLuongVe << endl;
		}	
	}

	cout  << "Nhap (THOAT) de tro ve: ";
	fflush(stdin);
	char luachon[7];
	gets(luachon);
	InHoa(luachon);
	fflush(stdin);
	while( strcmp(luachon,"THOAT") !=0 ){
		cout << endl << "Nhap (THOAT) de tro ve: ";
		gets(luachon);
	}
	return;
	
}
//g
void InDanhSachGheCuaChuyenBay(DS_CHUYENBAY &listCB,DS_MAYBAY &listMB){
	char maCB[15]={};
	char maMB[15],chon[2];
	int soDay,soDong;
	CHUYENBAY *tempCB;
	MAYBAY *tempMB;
 
	start:
	system("cls");
	cout << "\n\n\t\t  ==============TRA CUU DANH SACH GHE TREN CHUYEN BAY==============" << endl;
	HinhVuong(30,10,66,14);
	gotoxy(32,12);
	cout << "MaCB: ";
	fflush(stdin);
	gets(maCB);
	InHoa(maCB);
	if(strlen(maCB) == 0) return;
	if(KiemTraKiTu(maCB) == 0){
		system("cls");
		cout << "ERROR: KHONG DUOC CHUA KY TU DAC BIET HOAC KHOANG TRANG!!";
		Sleep(1000);
		goto start;
	}
	if( KiemTraKhoangTrang(maCB) == 0){
		system("cls");
		cout << "ERROR: KHONG DUOC DE TRONG HOAC CO KHOANG TRANG!!";
		Sleep(1000);
		goto start;
	}
	if(KiemTraMaCB(listCB,maCB) == 0){
		system("cls");
		cout << "ERROR: CHUYEN BAY KHONG TON TAI!!";
		Sleep(1000);	
		goto start;
	}
	

	system("cls");
	cout << "\n\t\t     ==============TRA CUU DANH SACH GHE TREN CHUYEN BAY==============" << endl;
	cout << "\n\n\n\t\tCHUYENBAY: " << maCB << endl;
	// tim cb
	// tim ra cai node luu chuyen bay
	for (CHUYENBAY *k=listCB.pFirst; k!=NULL; k=k->next){
		if (strcmp(k->machuyenbay,maCB) == 0) {
			strcpy(maMB,k->sohieuMB);
			tempCB = k;
			break;
		}
	}
	gotoxy(35,10);
	
	// tim so day so dong cua maybay
	for (int i=1; i<= listMB.soluong; i++){
		if ( strcmp(listMB.DSMayBay[i]->sohieuMB,maMB) == 0) {
			soDay = listMB.DSMayBay[i]->soday;
			soDong = listMB.DSMayBay[i]->sodong;
			tempMB = listMB.DSMayBay[i];
			break;
		}
	}
	
	// danh dau nhung ghe da dat
	// i soday, j so dong
	for (int i=1; i<= soDay; i++)
		for (int j=1; j<=soDong; j++){
			gotoxy(8+i*15,8+j);
			cout << char (64+i) << j;
			if(KiemTraGheTrong(tempCB->ve,tempCB->soLuongVe,i,j) == 1){
				gotoxy(8+i*15,8+j);
				cout << "*****";
			}
		}
	cout << endl<< "==================================================================================================="<<endl;

	while(strcmp(chon,"THOAT") !=0){
		cout << "Nhap (THOAT) de thoat: ";
		fflush(stdin);
		gets(chon);
		InHoa(chon);
	}
}
//h
void ThongKeSoLanThucHienChuyenBay(DS_CHUYENBAY &listCB,DS_MAYBAY &listMB){
	int thongke[300] = {};
	DS_MAYBAY tempListMB = listMB;
	
	
	// gan ma chuyen bay va so luong ve ban tu DSLK vao mang
	for(CHUYENBAY *k=listCB.pFirst ; k!=NULL; k=k->next){
		int i=1;
		char tempMaCB[15];
		 
		for ( i; i< listMB.soluong; i++)
			if ( strcmp(tempListMB.DSMayBay[i]->sohieuMB,k->sohieuMB) == 0) break;
			
		thongke[i]++;
	}
	
	// selection sort
	int max;
	for (int i=1; i<listMB.soluong; i++ ){
		max = i;
		for(int k=i+1; k<=listMB.soluong; k++)
			if(thongke[max] < thongke[k]) max = k;
	
		swap(thongke[i],thongke[max]);
		swap(tempListMB.DSMayBay[i],tempListMB.DSMayBay[max]);
	}
	
	system("cls");
	cout << "\n\t\t       ==============So Lan Thuc Hien Chuyen Bay==============" << endl;
	cout << "\n\t   SoHieuMayBay \t\t LoaiMayBay \t\t\t SoLuot "<< endl;
	for(int i=1; i<= listMB.soluong; i++){
		//cout << "\n\t      " << tempListMB.DSMayBay[i]->sohieuMB << "\t\t\t   " 
		cout <<setw(20) << right << tempListMB.DSMayBay[i]->sohieuMB;
		cout << setw(28) << right << tempListMB.DSMayBay[i]->loai;
		cout << setw(28) << right << thongke[i] << endl;
	}
	cout << endl<< "==================================================================================================="<<endl;
	char chon[20];
	while( strcmp(chon,"THOAT") !=0){
		cout << "Nhap (THOAT) de thoat: ";
		fflush(stdin);
		gets(chon);
		InHoa(chon);
	}
}

//menu chinh
int Menu(){
	system("cls");
	char chon[5];
	int luachon;
	gotoxy(11,8);
	cout << "===========================MENU DAT VE MAY BAY===========================";
	HinhVuong(20,10,80,27);
	gotoxy(40,11);
	cout << "1. Dat Ve May Bay";
	gotoxy(35,13);
	cout << "2. Cap Nhat Danh Sach May Bay";
	gotoxy(33,15);
	cout << "3. Cap Nhat Danh Sach Chuyen Bay";
	gotoxy(33,17);
	cout << "	   4. Huy Ve";
	gotoxy(33,19);
	cout << "  5. In Danh Sach Chuyen Bay";
	gotoxy(33,21);
	cout << "    6. Tra Cuu Chuyen Bay";
	gotoxy(25,23);
	cout << "    7. Tra Cuu Vi Tri Ghe Tren Chuyen Bay";
	gotoxy(21,25);
	cout << "    8. Thong Ke So Lan May Bay Thuc Hien Chuyen Bay";
	gotoxy(1,28);
	cout << endl << "Nhap lua chon cua ban: ";
	gets(chon);
	luachon = atoi(chon);
	return luachon;

}
int main(){	
	DS_MAYBAY listMB;
	DS_CHUYENBAY listCB;
	DS_HANHKHACH *listHK = NULL;
	LoadMB(listMB);
	LoadCB(listCB);
	LoadHK(listHK);
	int luachon;
	
	while(1){
	switch(Menu()){
		case 1:{
			MenuDatVe(listCB,listMB,listHK);
			break;
		}
		case 2: {
			MenuDanhSachMayBay(listMB,listCB);
			break;
		}
		case 3:{
			MenuDanhSachChuyenBay(listCB,listHK,listMB);
			break;
		}
		case 4:{
			HuyVe(listCB,listHK,listMB);
			break;
		}
		case 5: {
			InDanhSachHanhKhach(listCB,listHK);
			break;
		}
		case 6:{
			TimKiemChuyenBay(listCB,listMB);
			break;
		}
		case 7: {
			InDanhSachGheCuaChuyenBay(listCB,listMB);
			break;
		}
		case 8: {
			ThongKeSoLanThucHienChuyenBay(listCB,listMB);
			break;
		}
	}
}
	
	getch();
	return 0;
}
