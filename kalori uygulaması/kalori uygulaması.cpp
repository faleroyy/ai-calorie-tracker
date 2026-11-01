#include <iostream>
#include <string>
#include <clocale>
#include <thread>  // Bekletme işlemleri için
#include <chrono>  // Zaman işlemleri için
#include <fstream> // Yapay zekadan gelen dosyayı okumak için

using namespace std;

int main() {
    setlocale(LC_ALL, "Turkish");
    bool devamEt = true; //  Program kendini tekrarlasın
    bool profilHazir = false; // Profil açık değil
    int secim, secimCinsiyet, aktiviteSecim, amacSecim, yas, pIhtiyac = 0, KIhtiyac = 0, yIhtiyac = 0;
    double kilo, boy, vki = 0, bmr = 0, gunlukIhtiyac = 0, hedefKalori = 0;
    double alinanKalori = 0, alinanProtein = 0, alinanKarbo = 0, alinanYag = 0;
    string hedefMetni = "", vkiDurumu = "";

    // Kalori takibi ve Özel Diyet için değişkenler
    string bugunYenenler = "";
    string ozelDiyetListesi = "Henüz özel bir diyet listesi oluşturmadınız. (Menü 6'dan oluşturabilirsiniz)";

    while (devamEt) {
        cout << "\n###############################################" << endl;
        cout << "#                                             #" << endl;
        cout << "#              KALORİ-TAKİP                   #" << endl;
        cout << "#      ---------------------------------      #" << endl;
        cout << "#  [1] Profil Oluştur ve Hedef Hesapla        #" << endl;
        // 2 numaralı menü silindi
        cout << "#  [3] Mevcut Durum ve Diyet Özeti            #" << endl;
        cout << "#  [4] Sistemden Güvenli Çıkış                #" << endl;
        cout << "#  [5] AI Kamera/Fotoğraf Analizi             #" << endl;
        cout << "#  [6] Özel Diyet Listemi Oluştur             #" << endl;
        cout << "#  [7] Manuel Yemek / Kalori Ekle             #" << endl;
        cout << "#  [8] HTML Web Dashboard Raporu Al           #" << endl;
        cout << "#                                             #" << endl;
        cout << "###############################################" << endl;
        cout << "\n>> İşlem Seçiniz: ";
        cin >> secim;

        switch (secim) {
        case 1:
            cout << "\n>>> KULLANICI BİLGİLERİ" << endl;
            cout << "---------------------------------------" << endl;
            cout << "Cinsiyet (1: Erkek / 2: Kadın): ";
            cin >> secimCinsiyet;
            if (secimCinsiyet != 1 && secimCinsiyet != 2) {
                cout << "\n[!] Yanlış Giriş! Lütfen 1 veya 2 seçiniz." << endl;
                break;
            }
            cout << "Vücut Ağırlığı (kg): ";
            cin >> kilo;
            cout << "Boy Uzunluğu (cm): ";
            cin >> boy;
            cout << "Yaş: ";
            cin >> yas;

            // --- ENTEGRASYON: VKİ burada arka planda hesaplanıyor ---
            vki = kilo / ((boy / 100.0) * (boy / 100.0));
            if (vki < 18.5) vkiDurumu = "Zayıf";
            else if (vki <= 25) vkiDurumu = "Normal";
            else if (vki <= 30) vkiDurumu = "Kilolu";
            else vkiDurumu = "Obezite";

            // Bazal Metabolizma Hesaplama
            if (secimCinsiyet == 1)
            {
                bmr = (10 * kilo) + (6.25 * boy) - (5 * yas) + 5;
            }
            else
            {
                bmr = (10 * kilo) + (6.25 * boy) - (5 * yas) - 161;
            }

            // Aktivite Seviyesi Seçimi
            cout << "\n>>> AKTİVİTE SEVİYESİ" << endl;
            cout << "1. Masa başı (Hareketsiz)" << endl;
            cout << "2. Az Hareketli (Haftada 1-3 gün spor)" << endl;
            cout << "3. Orta Hareketli (Haftada 3-5 gün spor)" << endl;
            cout << "4. Çok Hareketli (Haftada 6-7 gün ağır spor)" << endl;
            cout << "Seçiminiz: ";
            cin >> aktiviteSecim;

            switch (aktiviteSecim) {
            case 1: gunlukIhtiyac = bmr * 1.2; break;
            case 2: gunlukIhtiyac = bmr * 1.375; break;
            case 3: gunlukIhtiyac = bmr * 1.55; break;
            case 4: gunlukIhtiyac = bmr * 1.725; break;
            default: gunlukIhtiyac = bmr * 1.2;
            }

            // Hedef Belirleme
            cout << "\n>>> AMACINIZ NEDİR?" << endl;
            cout << "1. Kilo Vermek (Yağ Yakımı)" << endl;
            cout << "2. Kiloyu Korumak" << endl;
            cout << "3. Kilo Almak (Kas Kütlesi/Hacim)" << endl;
            cout << "Seçiminiz: ";
            cin >> amacSecim;

            if (amacSecim == 1) {
                hedefKalori = gunlukIhtiyac - 500;
                hedefMetni = "Yağ Yakımı / Kilo Verme";
                pIhtiyac = kilo;
                KIhtiyac = kilo * 1.3;
                yIhtiyac = kilo * 0.6;
            }
            else if (amacSecim == 3) {
                hedefKalori = gunlukIhtiyac + 500;
                hedefMetni = "Kilo Alma / Kas Gelişimi";
                pIhtiyac = kilo * 2;
                KIhtiyac = kilo * 3.5;
                yIhtiyac = kilo * 0.9;
            }
            else {
                hedefKalori = gunlukIhtiyac;
                hedefMetni = "Mevcut Kiloyu Koruma";
                pIhtiyac = kilo * 1.3;
                KIhtiyac = kilo * 3.5;
                yIhtiyac = kilo * 0.7;
            }

            // Profil Hazır
            profilHazir = true;

            cout << "\n[*] PROFİL GÜNCELLENDİ!" << endl;
            cout << "[=>] Hedefinize Göre Almanız Gereken: " << hedefKalori << " kcal" << endl;
            cout << "---------------------------------------" << endl;
            break;

            // CASE 2 TAMAMEN SİLİNDİ

        case 3:
            if (!profilHazir) {
                cout << "\n[!] Önce 1. seçenekten profilinizi oluşturun!" << endl;
            }
            else {
                cout << "\n>>> MEVCUT DURUM VE GÜNLÜK TAKİP ÖZETİ" << endl;
                cout << "---------------------------------------" << endl;

                // --- ENTEGRASYON: VKİ'yi ve Hedefi direk burada gösteriyoruz ---
                cout << "[->] VKİ Değeriniz : " << vki << " (" << vkiDurumu << ")" << endl;
                cout << "[->] Hedefiniz     : " << hedefMetni << endl;
                cout << "---------------------------------------" << endl;

                cout << "Bazal Metabolizma (BMR): " << bmr << " kcal" << endl;
                cout << "Günlük Toplam Harcama: " << gunlukIhtiyac << " kcal" << endl;
                cout << "Günlük Alman Gereken: " << hedefKalori << " kcal" << endl;
                cout << "---------------------------------------" << endl;
                cout << "GÜNLÜK ALMANIZ GEREKEN MAKROLAR" << endl;
                cout << "Protein:" << pIhtiyac << " gr" << endl;
                cout << "Karbohidrat:" << KIhtiyac << " gr" << endl;
                cout << "Yağ:" << yIhtiyac << " gr" << endl;

                cout << "---------------------------------------" << endl;
                cout << "Öğün Planınız:" << endl;
                cout << "---------------------------------------" << endl;
                if (hedefKalori < 1600)
                {
                    cout << "[Kahvaltı] 2 haşlanmış yumurta (150 kcal), 1 dilim tam buğday ekmeği (70 kcal), bol yeşillik ve 5 zeytin (50 kcal)." << endl;
                    cout << "[Öğle] 150g Izgara Tavuk Göğsü (250 kcal), Mevsim salata (yağsız) (50 kcal), 1 bardak ayran (60 kcal)." << endl;
                    cout << "[Akşam] 8 yemek kaşığı zeytinyağlı sebze yemeği (200 kcal), 1 kase yağsız yoğurt (100 kcal)." << endl;
                    cout << "[Ara Öğün] 10 adet çiğ badem (70 kcal) veya 1 küçük elma (60 kcal)." << endl;
                }
                else if (hedefKalori >= 1600 && hedefKalori <= 2400)
                {
                    cout << "[Kahvaltı] 3 yumurtalı peynirli omlet (350 kcal), 2 dilim tam buğday ekmeği (140 kcal), 10 zeytin (100 kcal)." << endl;
                    cout << "[Öğle] 200g Izgara Tavuk veya Hindi (350 kcal), 6 yemek kaşığı bulgur pilavı (200 kcal), salata (80 kcal)." << endl;
                    cout << "[Akşam] 200g Izgara Biftek veya Balık (400 kcal), 1 porsiyon haşlanmış sebze (100 kcal), 1 kase cacık (120 kcal)." << endl;
                    cout << "[Ara Öğün] 1 tam ceviz (50 kcal) + 1 muz (100 kcal)." << endl;
                }
                else
                {
                    cout << "[Kahvaltı] 4 yumurtalı menemen (450 kcal), 3 dilim ekmek (210 kcal), 2 kaşık fıstık ezmesi & bal (180 kcal)." << endl;
                    cout << "[Öğle] 250g Kırmızı Et veya Tavuk (450 kcal), 10 yemek kaşığı pirinç pilavı (350 kcal), 1 kase mercimek çorbası (150 kcal)." << endl;
                    cout << "[Akşam] 250g Tavuk/Et (450 kcal), 1 tabak tam buğday makarna (350 kcal), 1 kase tam yağlı yoğurt (150 kcal)." << endl;
                    cout << "[Ara Öğün] 1 bardak süt (120 kcal) + 50g yulaf ezmesi ve kuruyemiş (300 kcal)." << endl;
                }

                // İlerleme Çubuğu ve Özel Diyet Gösterimi
                cout << "\n>>> GÜNLÜK KALORİ TAKİBİ VE DURUM ÖZETİ" << endl;
                cout << "---------------------------------------" << endl;
                cout << "Alınan Kalori  : " << alinanKalori << " kcal" << endl;
                double kalan = hedefKalori - alinanKalori;
                cout << "Kalan Kalori   : " << (kalan < 0 ? 0 : kalan) << " kcal "
                    << (kalan < 0 ? "(HEDEFİ AŞTINIZ!)" : "") << endl;

                int barGenislik = 20;
                int doluluk = (hedefKalori > 0) ? (int)((alinanKalori / hedefKalori) * barGenislik) : 0;
                if (doluluk > barGenislik) doluluk = barGenislik;

                cout << "İlerleme       : [";
                for (int i = 0; i < barGenislik; ++i) {
                    if (i < doluluk) cout << "#";
                    else cout << "-";
                }
                cout << "]\n---------------------------------------" << endl;

                if (!bugunYenenler.empty()) {
                    cout << "[!] Bugün Yenilenler Listesi:\n" << bugunYenenler;
                    cout << "---------------------------------------" << endl;
                }

                cout << "ÖZEL DİYET LİSTENİZ:\n" << ozelDiyetListesi << endl;
            }
            break;

        case 4:
            cout << "\n[+] Çıkış yapıldı. Sağlıklı kal!" << endl;
            devamEt = false;
            break;

        case 5:
        {
            string dosyaYolu;
            cout << "\n=============================================\n";
            cout << "[AI] YAPAY ZEKA GORUNTU ISLEME MODULU\n";
            cout << "=============================================\n";
            cout << "Lutfen analiz edilecek fotografin adini girin: ";
            cin >> dosyaYolu;

            cout << "\n[*] Görüntü işleniyor...\n";

            string komut;

            if (profilHazir == false) {
                komut = "py ai_motoru.py \"" + dosyaYolu + "\" YOK";
            }
            else {
                string kiloBilgisi = to_string((int)kilo) + " kg";
                string hedefBilgisi = hedefMetni;
                komut = "py ai_motoru.py \"" + dosyaYolu + "\" \"" + kiloBilgisi + ", Hedef: " + hedefBilgisi + "\"";
            }

            system(komut.c_str());

            ifstream dosyaOku("ai_veri.txt");
            string yemekAdi;
            double yemekKalori = 0;

            if (dosyaOku.is_open()) {
                getline(dosyaOku, yemekAdi);
                dosyaOku >> yemekKalori;
                dosyaOku.close();

                if (yemekKalori > 0) {
                    char cevap;
                    cout << "\n[?] Bu besini (" << yemekAdi << " - " << yemekKalori << " kcal) yediniz mi?\nGünlük kalorinize eklensin mi? (E/H): ";
                    cin >> cevap;

                    if (cevap == 'E' || cevap == 'e') {
                        alinanKalori += yemekKalori;
                        bugunYenenler += "- " + yemekAdi + " (" + to_string((int)yemekKalori) + " kcal) [AI Analizi]\n";
                        cout << "[+] Afiyet olsun! " << yemekKalori << " kcal sisteme işlendi.\n";
                    }
                    else {
                        cout << "[-] Besin günlüğe eklenmedi.\n";
                    }
                }
            }

            cout << "\n---------------------------------------------\n";
            cout << "[i] Analiz tamamlandi. Ana menuye donuluyor...\n";
            break;
        }

        case 6:
        {
            cout << "\n>>> ÖZEL DİYET LİSTESİ OLUŞTURMA\n";
            cout << "Lütfen günlük diyet planınızı tek bir satır halinde yazın.\n";
            cout << "(Örn: Sabah 2 yumurta yulaf, Öğle ızgara tavuk, Akşam sebze)\n\nYazın: ";
            cin.ignore();
            getline(cin, ozelDiyetListesi);

            cout << "\n[*] Harika! Özel diyet listeniz kaydedildi.\n";
            cout << "[i] Menü 3'ten mevcut durumunuza bakarak listenizi görebilirsiniz.\n";
            break;
        }

        case 7:
        {
            if (!profilHazir) {
                cout << "\n[!] Önce 1. seçenekten profilinizi oluşturun!\n";
                break;
            }
            string isim;
            double mk, mp, mc, my;

            cout << "\n>>> MANUEL YEMEK VE MAKRO EKLEME\n";
            cout << "Yemek Adı (Örn: Izgara Tavuk): ";
            cin.ignore();
            getline(cin, isim);

            cout << "Kalori: "; cin >> mk;
            cout << "Protein (gr): "; cin >> mp;
            cout << "Karbohidrat (gr): "; cin >> mc;
            cout << "Yağ (gr): "; cin >> my;

            // Girilen değerleri genel toplama ekliyoruz
            alinanKalori += mk;
            alinanProtein += mp;
            alinanKarbo += mc;
            alinanYag += my;

            // Günlüğe makro detaylarıyla birlikte yazıyoruz
            bugunYenenler += "- " + isim + " (" + to_string((int)mk) + " kcal - P:" + to_string((int)mp) + " K:" + to_string((int)mc) + " Y:" + to_string((int)my) + ") [Manuel]\n";

            cout << "\n[+] Harika! Veriler günlüğünüze başarıyla eklendi.\n";
            cout << "[i] Menü 3'ten dolan kalori ve makro hedeflerinizi kontrol edebilirsiniz.\n";
            break;
        }
        case 8:
        {
            if (!profilHazir) {
                cout << "\n[!] Önce 1. seçenekten profilinizi oluşturun!\n";
                break;
            }

            cout << "\n[*] Web Dashboard oluşturuluyor...\n";

            ofstream htmlDosya("rapor.html");

            int yuzde = 0;
            if (hedefKalori > 0) {
                yuzde = (int)((alinanKalori / hedefKalori) * 100);
                if (yuzde > 100) yuzde = 100;
            }

            htmlDosya << "<!DOCTYPE html>\n<html lang='tr'>\n<head>\n"
                << "<meta charset='windows-1254'>\n<title>Kalori Takip Pro - Rapor</title>\n"
                << "<style>\n"
                << "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background-color: #121212; color: #ffffff; margin: 0; padding: 30px; }\n"
                << ".container { max-width: 800px; margin: auto; background: #1e1e1e; padding: 30px; border-radius: 12px; box-shadow: 0 8px 16px rgba(0,0,0,0.5); border: 1px solid #333; }\n"
                << "h1 { color: #4CAF50; text-align: center; border-bottom: 2px solid #333; padding-bottom: 15px; margin-top: 0; }\n"
                << ".card { background: #2c2c2c; padding: 20px; border-radius: 8px; margin-bottom: 20px; }\n"
                << "h2 { color: #03A9F4; margin-top: 0; }\n"
                << ".progress-bg { background: #444; border-radius: 20px; height: 30px; width: 100%; overflow: hidden; margin-top: 10px; }\n"
                << ".progress-bar { background: linear-gradient(90deg, #4CAF50, #8BC34A); height: 100%; color: white; text-align: center; line-height: 30px; font-weight: bold; width: " << yuzde << "%; transition: width 1s ease-in-out; }\n"
                << ".over-limit { background: linear-gradient(90deg, #f44336, #e91e63) !important; }\n"
                << ".makro-grid { display: flex; justify-content: space-between; gap: 10px; }\n"
                << ".makro-box { background: #333; padding: 15px; border-radius: 8px; flex: 1; text-align: center; }\n"
                << ".makro-val { font-size: 24px; font-weight: bold; color: #FFC107; }\n"
                << ".list { font-family: monospace; font-size: 16px; color: #a5d6a7; white-space: pre-wrap; }\n"
                << "</style>\n</head>\n<body>\n"
                << "<div class='container'>\n"
                << "<h1>&#128640; KALORİ TAKİP PRO - GÜNLÜK RAPOR</h1>\n"

                << "<div class='card'>\n"
                << "<h2>&#128100; Profil Özeti</h2>\n"
                << "<p><strong>VKİ Değeriniz:</strong> " << vki << " (" << vkiDurumu << ")</p>\n"
                << "<p><strong>Hedefiniz:</strong> " << hedefMetni << "</p>\n"
                << "</div>\n"

                << "<div class='card'>\n"
                << "<h2>&#128293; Günlük Kalori Durumu</h2>\n"
                << "<p>Hedef: <strong>" << hedefKalori << " kcal</strong> | Alınan: <strong>" << alinanKalori << " kcal</strong></p>\n"
                << "<div class='progress-bg'>\n";

            if (alinanKalori > hedefKalori) {
                htmlDosya << "<div class='progress-bar over-limit' style='width:100%;'>HEDEF AŞILDI!</div>\n";
            }
            else {
                htmlDosya << "<div class='progress-bar'>" << yuzde << "%</div>\n";
            }

            htmlDosya << "</div>\n</div>\n"

                << "<div class='card'>\n"
                << "<h2>&#129385; Makro Hedefleri</h2>\n"
                << "<div class='makro-grid'>\n"
                << "<div class='makro-box'><div>Protein</div><div class='makro-val'>" << alinanProtein << " / " << pIhtiyac << "g</div></div>\n"
                << "<div class='makro-box'><div>Karbonhidrat</div><div class='makro-val'>" << alinanKarbo << " / " << KIhtiyac << "g</div></div>\n"
                << "<div class='makro-box'><div>Yağ</div><div class='makro-val'>" << alinanYag << " / " << yIhtiyac << "g</div></div>\n"
                << "</div>\n</div>\n"

                << "<div class='card'>\n"
                << "<h2>&#127869; Bugün Yenilen Besinler</h2>\n"
                << "<div class='list'>" << (bugunYenenler.empty() ? "Henüz bir besin kaydı girmediniz." : bugunYenenler) << "</div>\n"
                << "</div>\n"

                << "</div>\n</body>\n</html>";

            htmlDosya.close();

            cout << "[+] HTML Dosyası başarıyla üretildi!\n";
            cout << "[*] Tarayıcınızda açılıyor...\n";

            system("start rapor.html");

            break;
        }

        default:
            cout << "\n[!] Geçersiz seçim!" << endl;
        }
    }
    return 0;
}