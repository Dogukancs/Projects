/**
*
* @author Doğukan Samet SEVİNDİK-dogukan.sevindik@ogr.sakarya.edu.tr
* @since 13.04.2026
* <p>
* Simülasyonun temel yapı taşı olan bu sınıf Java faker ile üretilmiş benzersiz ID ,isim soyisim , yaş gibi kişisel verilerin bulunduğu kısım.
*/
package proje;

public class Kisi {
private static int idCounter = 1; // Tüm oyunda benzersiz ID için statik sayaç
	    private int id;
	    private String isimSoyisim;
	    private int yas;

	    public Kisi(String isimSoyisim, int yas) {
	        this.id = idCounter++;
	        this.isimSoyisim = isimSoyisim;
	        this.yas = yas;
	    }
	    public void yasArtir() {
	        this.yas++;
	    }
	    public int getId() { return id; }
	    public String getIsimSoyisim() { return isimSoyisim; }
	    public int getYas() { return yas; }
	    @Override
	    public String toString() {
	        return id + " - " + isimSoyisim + " - " + yas;
	    }
	}