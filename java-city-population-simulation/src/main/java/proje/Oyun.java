/**
*
* @author Doğukan Samet SEVİNDİK-dogukan.sevindik@ogr.sakarya.edu.tr
* @since 15.04.2026
* <p>
* Simülasyonun ana mantığını barındıran kısım-sınıf nüfus artışı hesaplama,şehirlerin bölünmesi, ekran temizlenmesi (her turda vb) gibi işlemler burada yapılmakta.
* </p>
*/
package proje;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import com.github.javafaker.Faker;

public class Oyun {
	private List<Sehir> sehirler;
    private Faker faker;

    public Oyun() {
        this.sehirler = new ArrayList<>();
        this.faker = new Faker(Locale.forLanguageTag("tr"));
    }

    // Başlangıç sayılarını çözümleyip şehir insaasi
    public void sehirleriOlustur(String[] baslangicSayilari) {
        for (String s : baslangicSayilari) {
            int sayi = Integer.parseInt(s);
            int onlarBasamagi = sayi / 10;
            int birlerBasamagi = sayi % 10;

            int ilceSayisi = onlarBasamagi;
            if (ilceSayisi ==0) ilceSayisi = 1;
            int mahalleHedefi = birlerBasamagi;
            if (mahalleHedefi ==0) mahalleHedefi = 1;

            // 1.KURAL: Mahalle sayısı ilçeye tam bölünene kadar artıralım
            while (mahalleHedefi % ilceSayisi != 0) {
                mahalleHedefi++;
                if (mahalleHedefi > 9) {
                    mahalleHedefi = ilceSayisi;
                    break;
                }
            }

            int toplamMahalleSayisi = mahalleHedefi;
            int ilceBasinaMahalle = toplamMahalleSayisi / ilceSayisi;

            // 2.KURAL: Şehir nüfusu mahalle sayısına tam bölünene kadar artıralım
            int baslangicNufus = (onlarBasamagi * 10) + mahalleHedefi; 
            while (baslangicNufus % toplamMahalleSayisi != 0) {
                baslangicNufus++;
            }

            int mahalleBasinaKisi = baslangicNufus / toplamMahalleSayisi;

            // Şehir nesneleri olusturma
            Sehir yeniSehir = new Sehir(faker.address().city());
            for (int i = 0; i < ilceSayisi; i++) {
                Ilce yeniIlce = new Ilce(faker.address().cityName() + " İlçesi");
                for (int j = 0; j < ilceBasinaMahalle; j++) {
                    Mahalle yeniMahalle = new Mahalle(faker.address().streetName() + " Mahallesi");
                    for (int k = 0; k < mahalleBasinaKisi; k++) {
                        yeniMahalle.kisiEkle(new Kisi(faker.name().fullName(), faker.number().numberBetween(0, 51)));
                    }
                    yeniIlce.mahalleEkle(yeniMahalle);
                }
                yeniSehir.ilceEkle(yeniIlce);
            }
            sehirler.add(yeniSehir);
        }
    }

    public void turOynat() {
        List<Sehir> bolunmusYeniSehirler = new ArrayList<>();

        for (Sehir sehir : sehirler) {
            int mevcutNufus = sehir.nufus();
            
            for (Ilce ilce : sehir.getIlceler()) {
                ilce.yaslariArtir();
            }

            int katsayi = (mevcutNufus % 10) + ((mevcutNufus / 10) % 10);

            for (Ilce ilce : sehir.getIlceler()) {
                ilce.mahalleleriBuyut(katsayi, faker);
            }

            // Bölünme Kontrolü
            if (sehir.nufus() >= 1000) {
                int tasinacakIlceSayisi = sehir.getIlceler().size() / 2;
                if (tasinacakIlceSayisi > 0) {
                    Sehir yeniSehir = new Sehir(faker.address().city());
                    List<Ilce> eskiSehirKalanIlceler = new ArrayList<>();
                    List<Ilce> yeniSehirIlceleri = new ArrayList<>();

                    // İlçeleri paylaştırmaca (Tek sayı ise kurallar gereği eski şehirde 1 fazla kalır)
                    for (int i = 0; i < sehir.getIlceler().size(); i++) {
                        if (i < sehir.getIlceler().size() - tasinacakIlceSayisi) {
                            eskiSehirKalanIlceler.add(sehir.getIlceler().get(i));
                        } else {
                            yeniSehirIlceleri.add(sehir.getIlceler().get(i));
                        }
                    }

                    sehir.setIlceler(eskiSehirKalanIlceler);
                    yeniSehir.setIlceler(yeniSehirIlceleri);
                    bolunmusYeniSehirler.add(yeniSehir);
                }
            }
        }
        
        // Yeni oluşan şehirleri ana listede en sona ekle
        sehirler.addAll(bolunmusYeniSehirler);
    }

    public void durumlariYazdir() {
        for (int i = 0; i < sehirler.size(); i++) {
            System.out.print("[" + sehirler.get(i).nufus() + "]");
            if ((i + 1) % 5 == 0 || i == sehirler.size() - 1) {
                System.out.println();
            } else {
                System.out.print("-");
            }
        }
        System.out.println();
    }

    public void detayYazdir(int satir, int sutun) {
        int index = (satir * 5) + sutun;
        if (index < 0 || index >= sehirler.size()) {
            System.out.println("Hatalı koordinat girdiniz!");
            return;
        }

        Sehir secilen = sehirler.get(index);
        System.out.println("Şehir: " + secilen.getAd() + " - Nüfus: " + secilen.nufus());
        for (Ilce ilce : secilen.getIlceler()) {
            System.out.println("İlçe: " + ilce.getAd() + " - Nüfus: " + ilce.nufus());
            for (Mahalle mahalle : ilce.getMahalleler()) {
                System.out.println("Mahalle: " + mahalle.getAd() + " - Nüfus: " + mahalle.nufus());
                System.out.println("Kişiler:");
                for (Kisi kisi : mahalle.getKisiler()) {
                    System.out.println(kisi.toString());
                }
            }
        }
    }
}