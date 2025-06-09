# **Analisis Aliran Fluida dalam Pipa Menggunakan Metode Beda Hingga**
```
Muhammad Bryan Farras
2306230975
```
## **Deskripsi**

Program ini melakukan analisis aliran fluida dalam pipa dengan menggunakan metode numerik **beda hingga**. Program ini menghitung kecepatan aliran untuk dua jenis aliran:

* **Aliran Laminar:** Aliran dengan kecepatan rendah, di mana fluida mengalir secara teratur dalam lapisan-lapisan.
* **Aliran Turbulen:** Aliran dengan kecepatan tinggi yang menyebabkan pembentukan turbulensi dalam fluida.

Program ini menghitung profil kecepatan, bilangan Reynolds, dan debit aliran untuk kedua jenis aliran tersebut dengan menggunakan parameter fluida dan geometrik pipa.

## **Fitur**

1. **Perhitungan Profil Kecepatan Laminar:**
   Menghitung distribusi kecepatan pada aliran laminar menggunakan persamaan sederhana berdasarkan hukum Hagen-Poiseuille.

2. **Perhitungan Profil Kecepatan Turbulen:**
   Menghitung distribusi kecepatan pada aliran turbulen menggunakan hukum dinding logaritmik von Kármán.

3. **Menghitung Bilangan Reynolds:**
   Menentukan jenis aliran (laminar atau turbulen) berdasarkan bilangan Reynolds.

4. **Debit Aliran:**
   Menghitung debit aliran menggunakan metode integrasi numerik dengan metode trapezoidal.

5. **Output:**

   * Debit aliran untuk kedua jenis aliran (laminar dan turbulen).
   * Bilangan Reynolds.
   * Profil kecepatan untuk 5 titik contoh.

## **Input Parameter**

Parameter aliran yang digunakan dalam program ini dapat dimodifikasi di dalam kode program. Berikut adalah parameter yang digunakan:

* **radius:** Jari-jari pipa (dalam meter)
* **length:** Panjang pipa (dalam meter)
* **viscosity:** Viskositas fluida (dalam Pa.s)
* **density:** Densitas fluida (dalam kg/m³)
* **pressure_drop:** Penurunan tekanan sepanjang pipa (dalam Pa)
* **n\_points:** Jumlah titik grid untuk perhitungan numerik

### **Hasil Aliran Turbulen:**

* Debit aliran
* Bilangan Reynolds
* Profil kecepatan pada 5 titik contoh

## **Desain Algoritma**

Program ini menggunakan metode numerik beda hingga untuk mendiskritisasi persamaan aliran fluida dalam pipa. Algoritma melibatkan langkah-langkah berikut:

1. Mendiskritisasi pipa menjadi beberapa segmen radial.
2. Menyelesaikan persamaan kecepatan untuk aliran laminar dan turbulen menggunakan perhitungan numerik.
3. Menghitung bilangan Reynolds untuk menentukan jenis aliran.
4. Menghitung debit aliran menggunakan metode trapezoidal.
