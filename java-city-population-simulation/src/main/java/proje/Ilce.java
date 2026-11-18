/**
*
* @author Doğukan Samet SEVİNDİK-dogukan.sevindik@ogr.sakarya.edu.tr
* @since 11.04.2026
* <p>
* Şehir ve mahalleler arasında köprü görevi görecek ilçeler için oluşturulan sınıf bünyesindeki mahalleleri listeleyip yerel yönetim birimi olarak nüfus verisini üst birime iletir.
* </p>
*/
package proje;

import java.util.ArrayList;
import java.util.List;
import com.github.javafaker.Faker;
public class Ilce {
	private String ad;
    private List<Mahalle> mahalleler;

    public Ilce(String ad) {
        this.ad = ad;
        this.mahalleler = new ArrayList<>();
    }
    public void mahalleEkle(Mahalle m) {
        mahalleler.add(m);
    }
    public int nufus() {
        int toplam = 0;
        for (Mahalle m : mahalleler) {
            toplam += m.nufus();
        }
        return toplam;
    }
    public void yaslariArtir() {
        for (Mahalle m : mahalleler) {
            m.yaslariArtir();
        }
    }
    public void mahalleleriBuyut(int katsayi, Faker faker) {
        for (Mahalle m : mahalleler) {
            m.buyu(katsayi, faker);
        }
    }
    public String getAd() { return ad; }
    public List<Mahalle> getMahalleler() { return mahalleler; }
}