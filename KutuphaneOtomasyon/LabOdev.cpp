#include <iostream>
#include <fstream>
#include <string>
#include<windows.h>

using namespace std;


void KitapEkle() {
    string kitapAdi, yazarAdi;
    int stok;
    int fiyat;
    int barkod = 100;

    string s;
    ifstream dosya2("kitaplar.txt");
    while (!dosya2.eof() && dosya2.is_open()) // eof = dosyanın sonu mu kontrolünü yapmak için, bu döngüyü dosyanın içerisindeki son barkodu bulabilmek için kullanıyorum, yeni barkodu son barkoddan 1 fazla olacak şekilde ayarlıyorum. Eğer hiç ürün yoksa 100'den başlatıyorum.
    {
        getline(dosya2, s, '|');
    }
    if (!s.empty()) //burda dosyanın içerisinden gelen veri var mı diye kontrol sağlıyorum. Eğer veri gelmemiş ise barkod numarası default olarak 100'den başlayacak.
    {
        barkod = stoi(s) + 1; //stoi = string to integer, string'ten integer'a dönüşüm sağlıyorum. barkod numarasını dosyanın içerisindeki son barkoddan 1 fazla  olarak ayarlyorum.
    }
    dosya2.close();


    ofstream dosya("kitaplar.txt", ios::app);
    if (dosya.is_open()) {
        cout << "Kitap adini girin: ";
        getline(cin, kitapAdi);

        cout << "Yazar adini girin: ";
        getline(cin, yazarAdi);

        cout << "Stok girin:";
        cin >> stok;

        cout << "Fiyat girin: ";
        cin >> fiyat;


        dosya << kitapAdi << " | " << yazarAdi << " | " << stok << " | " << fiyat << " | " << barkod << " | " << endl;
        dosya.close();

        cout << "Kitap basariyla eklendi!" << endl << "Barkod numarasi: " << barkod << endl;
        Sleep(3000);
    }
    else {
        cout << "Dosya acilamadi." << endl;
        Sleep(3000);
    }
}

void KitaplariListele() {
    string satir;
    char tus;
    ifstream dosya("kitaplar.txt");

    if (dosya.is_open()) {
        while (getline(dosya, satir)) {
            cout << satir << '\n';
        }
        cout << "Menuye donmek i�in bir karaktere basip 'ENTER' 'e basiniz. ";
        cin >> tus;
        dosya.close();

    }
    else {
        cout << "Dosya acilamadi." << endl;
        Sleep(3000);
    }
}

void KitapAra(string arananKelime) {
    ifstream dosya("kitaplar.txt");
    string satir;
    char tus;
    int bulunanSayisi = 0;

    if (dosya.is_open()) {
        while (getline(dosya, satir)) {
            if (satir.find(arananKelime) != string::npos) {
                cout << satir << '\n';
                bulunanSayisi++;
            }
        }
        dosya.close();

        if (bulunanSayisi == 0) {
            cout << "Aradiginiz kelimeye uygun kitap bulunamadi. Ust menuye yonlendiriliyorsunuz..." << endl;
            Sleep(3000);
        }
        else {
            cout << "Toplam " << bulunanSayisi << " kitap bulundu." << endl;
            cout << "Gecmek i�in herhangi bir tusa bas�p 'ENTER' 'e basiniz ...  ";
            cin >> tus;
        }
    }
    else {
        cout << "Dosya acilamadi." << endl;
        Sleep(3000);
    }
}

void KitapSat() {

    int arananBarkod;
    string ad, yazar, stok, fiyat, barkod;
    ifstream dosya("kitaplar.txt");
    ofstream dosya2("gecici.txt");

    if (!dosya.is_open())
    {
        cout << "Dosya acilamadi." << endl;
    }
    else {
        cout << "Barkod numarasi giriniz" << endl;

        cin >> arananBarkod;

        bool urunBulundu = false;
        bool satinAlindi = false;
        string son;
        while (!dosya.eof()) //burada dosyanın sonuna kadar bütün verileri tek tek çekiyorum.
        {
            getline(dosya, ad, '|'); //ilk | işaretine kadar olan veriyi ad'a alıyorum
            getline(dosya, yazar, '|'); //sonraki | işaretine kadar olan veriyi yazar değişkenine atıyorum. Aşağıdakiler de aynı şekilde.
            getline(dosya, stok, '|');
            getline(dosya, fiyat, '|');
            getline(dosya, barkod, '|');

            if (arananBarkod == stoi(barkod) && son != barkod) //burada arananBarkod'un şu anki gelen verideki barkod ile eşleşip eşleşmediğini kontrol ediyorum. Ayrıca bir önceki gelen verideki barkod numarası ile şimdi gelen barkod numarası aynı mı diye kontrol yapıyorum (Aynı verinin birden fazla kez yazılmaması için)
            {
                urunBulundu = true;
                if (stoi(stok) > 0) //stok var mı diye kontrol sağlıyorum.
                {
                    dosya2 << ad << " | " << yazar << " | " << stoi(stok) - 1 << " | " << fiyat << " | " << arananBarkod << " | " << endl; //gelen verideki stoğu 1 azaltıp gecici.txt dosyasına yazdırıyorum.
                    cout << "Urun basariyla satin alindi\n" << "Odeyeceginiz tutar =" << fiyat << "TL" << endl;
                    satinAlindi = true;
                }
                else
                {
                    cout << "Bu urunun stogu bulunmamaktadir." << endl;
                    break;
                }
            }
            else if (son != barkod) {
                dosya2 << ad << " | " << yazar << " | " << stok << " | " << fiyat << " | " << barkod << " | " << endl;
            }
            son = barkod;

        }
        dosya.close();
        dosya2.close();

        if (satinAlindi) // eğer satın alınma yapılmış ise kitaplar.txt'den gecici.txt'e aktarılmış güncel veriyi kullanabilmek için öncelikle; kitaplar.txt'yi siliyorum, gecici.txt'yi kitaplar.txt olarak yeniden adlandırıyorum. 
        {
            remove("kitaplar.txt");
            rename("gecici.txt", "kitaplar.txt");
        }
        if (!urunBulundu) { //barkodun eşleşip eşleşmediğini kontrol ediyorum.
            cout << "Barkoda ait urun bulunamadi" << endl;
        }
    }



    Sleep(3000);
}

void KitapSil() {
    int arananBarkod;
    string ad, yazar, stok, fiyat, barkod;
    ifstream dosya("kitaplar.txt");
    ofstream dosya2("gecici.txt");

    if (!dosya.is_open())
    {
        cout << "Dosya acilamadi." << endl;
    }
    else {
        cout << "Barkod numarasi giriniz" << endl;

        cin >> arananBarkod;

        bool urunBulundu = false;
        string son;
        while (!dosya.eof())
        {
            getline(dosya, ad, '|');
            getline(dosya, yazar, '|');
            getline(dosya, stok, '|');
            getline(dosya, fiyat, '|');
            getline(dosya, barkod, '|');

            if (arananBarkod == stoi(barkod)) //aranan barkod, dosyadan gelen barkod ile eşleşiyor mu onun kontrolünü yapıyorum. stoi yapmamın sebebi string olarak gelen veride \n işaretinden kurtulamamam. bu yüzden gelen veriyi integer'a çevirip string ifadeden kurtuluyorum ve kontrolümü sağlıyorum.
            {
                urunBulundu = true; //eşleşen veriyi gecici.txt dosyasına yazdırmıyorum, silme işlemini sağlıyorum. ürünün silme işleminin yapıldığına dair bir flag tutuyorum.
            }
            else if (son != barkod) { //gelen önceki veriyi şu anki veriyle kıyaslıyorum. Aynı verinin birden fazla yazılmasını engellemek için kontrol sağlıyorum.
                dosya2 << ad << " | " << yazar << " | " << stok << " | " << fiyat << " | " << barkod << " | " << endl;
            }
            son = barkod;

        }
        dosya.close();
        dosya2.close();


        if (!urunBulundu) {
            cout << "Barkoda ait urun bulunamadi" << endl;
        }
        else {
            cout << "Kitap Basariyla Silindi.";
            remove("kitaplar.txt");
            rename("gecici.txt", "kitaplar.txt");
        }
    }



    Sleep(3000);
}

int main() {
    setlocale(LC_ALL, "tr_TR.UTF-8");
    while (true) {
        system("CLS");
        cout << "\t MENU \n" << string(20, '-') << endl;
        cout << "\n1. Kitap Ekle\n2. Kitaplari Listele\n3. Kitap Ara\n4. Kitap Satis\n5. Kitap Sil\n6. Cikis\nSeciminizi yapin: ";
        string secim;
        getline(cin >> ws, secim);

        if (secim == "1") {

            KitapEkle();

        }
        else if (secim == "2") {

            KitaplariListele();

        }
        else if (secim == "3") {

            cout << "Aranacak kelimeyi girin: ";

            string arananKelime;

            getline(cin, arananKelime);

            KitapAra(arananKelime);
        }
        else if (secim == "4")
        {
            KitapSat();
        }
        else if (secim == "5")
        {
            KitapSil();
        }
        else if (secim == "6") {
            cout << "Programdan cikiliyor..." << endl;

            Sleep(2000);
            break;
        }
        else {
            cout << "Gecersiz bir secim yaptiniz. Tekrar deneyin." << endl;
            Sleep(2000);

        }
    }

    return 0;
}