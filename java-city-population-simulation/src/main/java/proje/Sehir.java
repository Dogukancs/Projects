/**
*
* @author Doğukan Samet SEVİNDİK-dogukan.sevindik@ogr.sakarya.edu.tr
* @since 14.04.2026
* <p>
* En üst kısım olarak belirlenen şehir sınıfı kendisine bağlı ilçelerin nüfuslarını toplayarak genel popülasyonu yönetir.
*/
package proje;

import java.util.ArrayList;
import java.util.List;

public class Sehir {
	private String ad;
    private List<Ilce> ilceler;

    public Sehir(String ad) {
        this.ad = ad;
        this.ilceler = new ArrayList<>();
    }
    public void ilceEkle(Ilce i) {
        ilceler.add(i);
    }
    public int nufus() {
        int toplam = 0;
        for (Ilce i : ilceler) {
            toplam += i.nufus();
        }
        return toplam;
    }
    public String getAd() { return ad; }
    public List<Ilce> getIlceler() { return ilceler; }
    public void setIlceler(List<Ilce> yeniIlceler) {
        this.ilceler = yeniIlceler;
    }
}