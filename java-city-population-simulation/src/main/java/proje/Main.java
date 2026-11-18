/**
*
* @author Doğukan Samet SEVİNDİK-dogukan.sevindik@ogr.sakarya.edu.tr
* @since 18.04.2026
* <p>
* Main sınıfı projenin-programın giriş noktası kullanıcıdan alınan başlangıç verilerini alıp simülasyonu başlatarak oyun sınıfını yöneten kısım.
* </p>
*/
package proje;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Oyun oyun = new Oyun();
        System.out.print("Oyunun çalışacağı tur sayısını giriniz: ");
        int turSayisi = scanner.nextInt();
        scanner.nextLine(); 

        System.out.println("Sayıları aralarında birer boşluk bırakarak giriniz:");
        String sayilarSatiri = scanner.nextLine();
        String[] sayilar = sayilarSatiri.trim().split("\\s+");

        oyun.sehirleriOlustur(sayilar);

        System.out.println("\n--- Başlangıç Durumu ---");
        oyun.durumlariYazdir();

        for (int t = 1; t <= turSayisi; t++) {
            try {
                Thread.sleep(2000); // Turları takibi için 2 saniye
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            
            clearConsole();
            oyun.turOynat();
            System.out.println("--- " + t + ". Tur Sonu ---");
            oyun.durumlariYazdir();
        }

        System.out.println("\nOyun bitti! Detayını görmek istediğiniz şehrin satır ve sütununu giriniz (0'dan başlar).");
        System.out.print("Satır: ");
        int satir = scanner.nextInt();
        System.out.print("Sütun: ");
        int sutun = scanner.nextInt();

        System.out.println("\n--- Şehir Detayları ---");
        oyun.detayYazdir(satir, sutun);

        System.out.println("\nÇıkmak için herhangi bir sayı/tuş giriniz...");
        scanner.next();
        scanner.close();
    }

    // Konsolu temizleme metodu
    public static void clearConsole() {
        try {
            String os = System.getProperty("os.name");
            if (os.contains("Windows")) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            } else {
                System.out.print("\033[H\033[2J");
                System.out.flush();
            }
        } catch (Exception e) {
            // temizleme calismazsa
            for(int i = 0; i < 30; i++) {
                System.out.println();
            }
        }
    }
}