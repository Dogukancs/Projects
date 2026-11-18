/**
*
* @author Doğukan Samet SEVİNDİK-dogukan.sevindik@ogr.sakarya.edu.tr
* @since 10.04.2026
* <p>
* Sistemdeki en kücük hücre olacak bu sınıf gercek kisileri listeler halinde tutup çeşitli işlemleri sağlıyor.
* </p>
*/
package proje;

import java.util.ArrayList;
import java.util.List;
import com.github.javafaker.Faker;

public class Mahalle {
	private String ad;
    private List<Kisi> kisiler;

    public Mahalle(String ad) {
        this.ad = ad;
        this.kisiler = new ArrayList<>();
    }
    public void kisiEkle(Kisi k) {
        kisiler.add(k);
    }
    public int nufus() {
        return kisiler.size();
    }
    public void yaslariArtir() {
        for (Kisi k : kisiler) {
            k.yasArtir();
        }
    }
    // Nüfus artış
    public void buyu(int katsayi, Faker faker) {
        int mevcutNufus = nufus();
        int eklenecekKisiSayisi;

        if (katsayi == 0) {
            eklenecekKisiSayisi = 1; // Toplam sıfırsa sadece 1 kişi artar
        } else {
            int yeniNufus = mevcutNufus * katsayi;
            eklenecekKisiSayisi = yeniNufus - mevcutNufus;
        }

        for (int i = 0; i < eklenecekKisiSayisi; i++) {
            kisiEkle(new Kisi(faker.name().fullName(), 0)); // Yeni doğanlar veya göç edenler (yaş rastgele de olabilir, 0 olarak başlattık)
        }
    }
    public String getAd() { return ad; }
    public List<Kisi> getKisiler() { return kisiler; }
}