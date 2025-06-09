#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592653589793
#define MAX_ITER 1000
#define TOLERANCE 1e-6

// Struktur untuk menyimpan parameter aliran
typedef struct {
    double radius;       // Jari-jari pipa (m)
    double length;       // Panjang pipa (m)
    double viscosity;    // Viskositas dinamik (Pa.s)
    double density;      // Densitas fluida (kg/m^3)
    double pressure_drop; // Penurunan tekanan (Pa)
    int n_points;        // Jumlah titik grid
} FlowParams;

// Fungsi untuk menghitung profil kecepatan laminar
void calculate_laminar_flow(FlowParams params, double* velocity) {
    double dr = params.radius / (params.n_points - 1);
    double factor = params.pressure_drop / (4 * params.viscosity * params.length);
    
    for (int i = 0; i < params.n_points; i++) {
        double r = i * dr;
        velocity[i] = factor * (params.radius * params.radius - r * r);
    }
}

// Fungsi untuk menghitung bilangan Reynolds
double calculate_reynolds(double velocity, FlowParams params) {
    return (params.density * velocity * 2 * params.radius) / params.viscosity;
}

// Fungsi untuk menghitung faktor gesekan Darcy (aliran turbulen)
double calculate_darcy_friction(double Re) {
    // Persamaan Colebrook-White (perkiraan)
    if (Re < 2300) {
        return 64.0 / Re;  // Aliran laminar
    } else {
        // Perkiraan untuk aliran turbulen (Haaland equation)
        double roughness = 0.000015; // Kekasaran relatif (untuk pipa halus)
        return 1.0 / pow(-1.8 * log10(pow(roughness/3.7, 1.11) + 6.9/Re), 2);
    }
}

// Fungsi untuk menghitung profil kecepatan turbulen
void calculate_turbulent_flow(FlowParams params, double* velocity) {
    double dr = params.radius / (params.n_points - 1);
    double u_star = sqrt(params.pressure_drop * params.radius / (2 * params.density * params.length));
    double kappa = 0.41;  // Konstanta von Kármán
    double B = 5.5;       // Konstanta log-law
    
    for (int i = 0; i < params.n_points; i++) {
        double r = params.radius - i * dr;
        if (r < 1e-6) r = 1e-6;  // Hindari division by zero
        
        // Hukum dinding logaritmik
        double y_plus = r * u_star * params.density / params.viscosity;
        velocity[i] = u_star * (1/kappa * log(y_plus) + B);
    }
}

// Fungsi untuk menghitung debit aliran
double calculate_flow_rate(double* velocity, FlowParams params) {
    double dr = params.radius / (params.n_points - 1);
    double flow_rate = 0.0;
    
    // Integrasi numerik dengan metode trapezoidal
    for (int i = 1; i < params.n_points; i++) {
        double r1 = (i-1) * dr;
        double r2 = i * dr;
        flow_rate += 0.5 * (velocity[i-1] * r1 + velocity[i] * r2) * (r2 - r1);
    }
    
    return 2 * PI * flow_rate;
}

int main() {
    FlowParams params;
    params.radius = 0.05;      // 5 cm
    params.length = 10.0;      // 10 m
    params.viscosity = 0.001;  // Air pada 20°C
    params.density = 1000.0;   // Air
    params.pressure_drop = 1000.0; // 1 kPa
    params.n_points = 100;
    
    double velocity[params.n_points];
    
    // Hitung aliran laminar
    calculate_laminar_flow(params, velocity);
    double flow_rate_laminar = calculate_flow_rate(velocity, params);
    double Re_laminar = calculate_reynolds(velocity[0], params);
    
    printf("=== HASIL ALIRAN LAMINAR ===\n");
    printf("Debit aliran: %.6f m^3/s\n", flow_rate_laminar);
    printf("Bilangan Reynolds: %.2f\n", Re_laminar);
    printf("Profil kecepatan (5 titik contoh):\n");
    for (int i = 0; i < 5; i++) {
        printf("r=%.4f m: u=%.4f m/s\n", 
               i * params.radius/4, velocity[i*(params.n_points-1)/4]);
    }
    
    // Hitung aliran turbulen (dengan tekanan lebih tinggi)
    params.pressure_drop = 10000.0; // 10 kPa
    calculate_turbulent_flow(params, velocity);
    double flow_rate_turbulent = calculate_flow_rate(velocity, params);
    double Re_turbulent = calculate_reynolds(velocity[0], params);
    
    printf("\n=== HASIL ALIRAN TURBULEN ===\n");
    printf("Debit aliran: %.6f m^3/s\n", flow_rate_turbulent);
    printf("Bilangan Reynolds: %.2f\n", Re_turbulent);
    printf("Profil kecepatan (5 titik contoh):\n");
    for (int i = 0; i < 5; i++) {
        printf("r=%.4f m: u=%.4f m/s\n", 
               i * params.radius/4, velocity[i*(params.n_points-1)/4]);
    }
    
    return 0;
}